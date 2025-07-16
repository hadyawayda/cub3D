/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:42:09 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/17 00:42:09 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	wall_tex_id(int side, t_vec step)
{
	if (side == 0 && step.x > 0)
		return (0);
	if (side == 0)
		return (1);
	if (side == 1 && step.y > 0)
		return (2);
	return (3);
}

static void	compute_tex(t_cub *c, t_dda *d)
{
	double	wall_x;

	d->line_h = (int)(HEIGHT / d->perp_dist);
	d->draw_s = HEIGHT / 2 - d->line_h / 2;
	if (d->draw_s < 0)
		d->draw_s = 0;
	d->draw_e = d->draw_s + d->line_h - 1;
	if (d->draw_e >= HEIGHT)
		d->draw_e = HEIGHT - 1;
	d->tex_id = wall_tex_id(d->side_hit, d->step);
	if (d->side_hit == 0)
		wall_x = c->pl.pos.y + d->perp_dist * d->ray.y;
	else
		wall_x = c->pl.pos.x + d->perp_dist * d->ray.x;
	wall_x -= floor(wall_x);
	d->tex_x = (int)(wall_x * c->tex[d->tex_id].img.w);
	if ((d->side_hit == 0 && d->ray.x > 0)
		|| (d->side_hit == 1 && d->ray.y < 0))
		d->tex_x = c->tex[d->tex_id].img.w - d->tex_x - 1;
}

static void	draw_tex_column(t_cub *c, t_dda *d, int x)
{
	int	y;
	int	dy;
	int	tex_y;
	int	color;

	y = d->draw_s;
	while (y <= d->draw_e)
	{
		dy = y * 256 - HEIGHT * 128 + d->line_h * 128;
		tex_y = (dy * c->tex[d->tex_id].img.h) / d->line_h / 256;
		color = *(int *)(c->tex[d->tex_id].img.addr
				+ tex_y * c->tex[d->tex_id].img.line_len
				+ d->tex_x * (c->tex[d->tex_id].img.bpp / 8));
		*(int *)(c->frame.addr + y * c->frame.line_len
				+ x * (c->frame.bpp / 8)) = color;
		y++;
	}
}

void	cast_column(t_cub *c, int x)
{
	t_dda	d;

	init_dda(c, &d, x);
	compute_tex(c, &d);
	draw_tex_column(c, &d, x);
}
