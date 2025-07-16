/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:41:17 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/16 19:41:17 by hawayda          ###   ########.fr       */
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

void	cast_column(t_cub *c, int x)
{
	double	camera;
	t_vec	ray;
	t_vec	side;
	t_vec	delta;
	t_vec	step;
	int		map[2];
	int		side_hit;

	camera = 2 * x / (double)WIDTH - 1;
	ray = (t_vec){c->pl.dir.x + c->pl.plane.x * camera,
		c->pl.dir.y + c->pl.plane.y * camera};
	delta = (t_vec){fabs(1 / ray.x), fabs(1 / ray.y)};
	map[0] = (int)c->pl.pos.x;
	map[1] = (int)c->pl.pos.y;
	step.x = ray.x < 0 ? -1 : 1;
	step.y = ray.y < 0 ? -1 : 1;
	side.x = (ray.x < 0)
		? (c->pl.pos.x - map[0]) * delta.x
		: (map[0] + 1.0 - c->pl.pos.x) * delta.x;
	side.y = (ray.y < 0)
		? (c->pl.pos.y - map[1]) * delta.y
		: (map[1] + 1.0 - c->pl.pos.y) * delta.y;
	while (true)
	{
		if (side.x < side.y && (side_hit = 0) == 0)
		{
			side.x += delta.x;
			map[0] += (int)step.x;
		}
		else
		{
			side.y += delta.y;
			map[1] += (int)step.y;
			side_hit = 1;
		}
		if (c->map.grid[map[1]][map[0]] == '1')
			break ;
	}
	double	dist = (side_hit == 0)
		? (side.x - delta.x)
		: (side.y - delta.y);
	int	line_h = (int)(HEIGHT / dist);
	int	draw_s = -line_h / 2 + HEIGHT / 2;
	int	draw_e = line_h / 2 + HEIGHT / 2;
	if (draw_s < 0) draw_s = 0;
	if (draw_e >= HEIGHT) draw_e = HEIGHT - 1;
	int	tex_id = wall_tex_id(side_hit, step);
	double	wall_x = (side_hit == 0)
		? c->pl.pos.y + dist * ray.y
		: c->pl.pos.x + dist * ray.x;
	wall_x -= floor(wall_x);
	int	tex_x = (int)(wall_x * c->tex[tex_id].img.w);
	if ((side_hit == 0 && ray.x > 0) || (side_hit == 1 && ray.y < 0))
		tex_x = c->tex[tex_id].img.w - tex_x - 1;
	int	y = draw_s;
	while (y < draw_e)
	{
		int	d = y * 256 - HEIGHT * 128 + line_h * 128;
		int	tex_y = (d * c->tex[tex_id].img.h) / line_h / 256;
		int	color = *(int *)(c->tex[tex_id].img.addr
				+ (tex_y * c->tex[tex_id].img.line_len
				+ tex_x * (c->tex[tex_id].img.bpp / 8)));
		*(int *)(c->frame.addr + (y * c->frame.line_len
				+ x * (c->frame.bpp / 8))) = color;
		y++;
	}
}
