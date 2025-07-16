/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:35:25 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/17 00:35:25 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_cub *c, int x, t_vec *ray_dir, double *camera_x)
{
	*camera_x = 2.0 * x / (double)WIDTH - 1.0;
	ray_dir->x = c->pl.dir.x + c->pl.plane.x * (*camera_x);
	ray_dir->y = c->pl.dir.y + c->pl.plane.y * (*camera_x);
}

void	perform_dda(t_cub *c, t_dda *d)
{
	while (1)
	{
		if (d->side.x < d->side.y)
		{
			d->side.x += d->delta.x;
			d->map_x += (int)d->step.x;
			d->side_hit = 0;
		}
		else
		{
			d->side.y += d->delta.y;
			d->map_y += (int)d->step.y;
			d->side_hit = 1;
		}
		if (c->map.grid[d->map_y][d->map_x] == '1')
			break ;
	}
}

void	draw_tex_column(t_cub *c, t_dda *d, int x)
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
