/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:40:24 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/17 00:40:24 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_delta_step(t_cub *c, t_dda *d)
{
	if (d->ray.x == 0)
		d->delta.x = 1e30;
	else
		d->delta.x = fabs(1.0 / d->ray.x);
	if (d->ray.y == 0)
		d->delta.y = 1e30;
	else
		d->delta.y = fabs(1.0 / d->ray.y);
	if (d->ray.x < 0)
		d->step.x = -1;
	else
		d->step.x = 1;
	if (d->ray.y < 0)
		d->step.y = -1;
	else
		d->step.y = 1;
	if (d->ray.x < 0)
		d->side.x = (c->pl.pos.x - d->map_x) * d->delta.x;
	else
		d->side.x = (d->map_x + 1.0 - c->pl.pos.x) * d->delta.x;
	if (d->ray.y < 0)
		d->side.y = (c->pl.pos.y - d->map_y) * d->delta.y;
	else
		d->side.y = (d->map_y + 1.0 - c->pl.pos.y) * d->delta.y;
}

static void	run_dda(t_cub *c, t_dda *d)
{
	while (1)
	{
		if (d->side.x < d->side.y)
		{
			d->side.x += d->delta.x;
			d->map_x += d->step.x;
			d->side_hit = 0;
		}
		else
		{
			d->side.y += d->delta.y;
			d->map_y += d->step.y;
			d->side_hit = 1;
		}
		if (c->map.grid[d->map_y][d->map_x] == '1')
			break ;
	}
	if (d->side_hit == 0)
		d->perp_dist = d->side.x - d->delta.x;
	else
		d->perp_dist = d->side.y - d->delta.y;
}

void	init_dda(t_cub *c, t_dda *d, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	d->ray.x = c->pl.dir.x + c->pl.plane.x * camera_x;
	d->ray.y = c->pl.dir.y + c->pl.plane.y * camera_x;
	d->map_x = (int)c->pl.pos.x;
	d->map_y = (int)c->pl.pos.y;
	set_delta_step(c, d);
	run_dda(c, d);
}
