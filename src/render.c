/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:41:31 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 14:02:41 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	apply_rotation(t_cub *c)
{
	if (c->k.l)
		rotate(&c->pl, -ROT_SPEED);
	if (c->k.r)
		rotate(&c->pl, ROT_SPEED);
}

/* call this once every frame *before* you draw */
void	handle_inputs(t_cub *c)
{
	apply_rotation(c);
	apply_movement(c);
}

static void	draw_ceiling_floor(t_cub *c)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
			*(int *)(c->frame.addr + y * c->frame.line_len + x * (c->frame.bpp
						/ 8)) = c->ceil_col;
	}
	while (y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			*(int *)(c->frame.addr + y * c->frame.line_len + x * (c->frame.bpp
						/ 8)) = c->floor_col;
		y++;
	}
}

int	draw_frame(t_cub *c)
{
	int	x;

	sprite_tick(c);
	handle_inputs(c);
	draw_ceiling_floor(c);
	x = -1;
	while (++x < WIDTH)
		cast_column(c, x);
	draw_sprites(c);
	draw_minimap(c);
	mlx_put_image_to_window(c->mlx, c->win, c->frame.ptr, 0, 0);
	return (0);
}
