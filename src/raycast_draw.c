/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:42:09 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 11:56:27 by nhaber           ###   ########.fr       */
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

void	compute_tex(t_cub *c, t_dda *d)
{
	double	wall_x;
	int		tex_width;

	d->line_h = (int)(HEIGHT / d->perp_dist);
	d->draw_s = HEIGHT / 2 - d->line_h / 2;
	if (d->draw_s < 0)
		d->draw_s = 0;
	d->draw_e = d->draw_s + d->line_h - 1;
	if (d->draw_e >= HEIGHT)
		d->draw_e = HEIGHT - 1;
	d->tex_id = wall_tex_id(d->side_hit, d->step);
	if (d->tex_id < 0 || d->tex_id >= 4)
	{
		d->tex_id = 0;
	}
	if (d->side_hit == 0)
		wall_x = c->pl.pos.y + d->perp_dist * d->ray.y;
	else
		wall_x = c->pl.pos.x + d->perp_dist * d->ray.x;
	wall_x -= floor(wall_x);
	tex_width = c->tex[d->tex_id].img.w;
	d->tex_x = (int)(wall_x * tex_width);
	if ((d->side_hit == 0 && d->ray.x > 0) || (d->side_hit == 1
			&& d->ray.y < 0))
		d->tex_x = tex_width - d->tex_x - 1;
	if (d->tex_x < 0)
		d->tex_x = 0;
	else if (d->tex_x >= tex_width)
		d->tex_x = tex_width - 1;
}

static void	draw_tex_column(t_cub *c, t_dda *d, int x)
{
	int		y;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;

	// Height of the wall line
	step = 1.0 * c->tex[d->tex_id].img.h / d->line_h;
	tex_pos = (d->draw_s - HEIGHT / 2 + d->line_h / 2) * step;

	y = d->draw_s;
	while (y <= d->draw_e)
	{
		tex_y = (int)tex_pos & (c->tex[d->tex_id].img.h - 1); // mask if power of 2
		tex_pos += step;

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
	c->zbuf[x] = d.perp_dist;
}
