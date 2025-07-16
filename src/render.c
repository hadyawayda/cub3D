/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:41:31 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/17 00:01:05 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ceiling_floor(t_cub *c)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
			*(int *)(c->frame.addr + y * c->frame.line_len
					+ x * (c->frame.bpp / 8)) = c->ceil_col;
	}
	while (y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			*(int *)(c->frame.addr + y * c->frame.line_len
					+ x * (c->frame.bpp / 8)) = c->floor_col;
		y++;
	}
}

int	draw_frame(t_cub *c)
{
	int	x;

	draw_ceiling_floor(c);
	x = -1;
	while (++x < WIDTH)
		cast_column(c, x);
	mlx_put_image_to_window(c->mlx, c->win, c->frame.ptr, 0, 0);
	return (0);
}
