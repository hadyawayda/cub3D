/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:54:32 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 10:54:32 by hawayda          ###   ########.fr       */
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

/* compute just the vertical line on screen */
void	compute_draw_limits(t_dda *d)
{
	d->line_h = (int)(HEIGHT / d->perp_dist);
	d->draw_s = HEIGHT / 2 - d->line_h / 2;
	if (d->draw_s < 0)
		d->draw_s = 0;
	d->draw_e = d->draw_s + d->line_h - 1;
	if (d->draw_e >= HEIGHT)
		d->draw_e = HEIGHT - 1;
}

void	compute_texture_mapping(t_cub *c, t_dda *d)
{
	int		tex_w;
	double	wall_x;

	d->tex_id = wall_tex_id(d->side_hit, d->step);
	if (d->tex_id < 0 || d->tex_id >= 4)
		d->tex_id = 0;
	if (d->side_hit == 0)
		wall_x = c->pl.pos.y + d->perp_dist * d->ray.y;
	else
		wall_x = c->pl.pos.x + d->perp_dist * d->ray.x;
	wall_x = wall_x - floor(wall_x);
	tex_w = c->tex[d->tex_id].img.w;
	d->tex_x = (int)(wall_x * tex_w);
	if (d->side_hit == 0 && d->ray.x > 0)
		d->tex_x = tex_w - d->tex_x - 1;
	if (d->side_hit == 1 && d->ray.y < 0)
		d->tex_x = tex_w - d->tex_x - 1;
	if (d->tex_x < 0)
		d->tex_x = 0;
	else if (d->tex_x >= tex_w)
		d->tex_x = tex_w - 1;
}
