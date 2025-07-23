/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:41:31 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/22 19:33:05 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	apply_movement(t_cub *c)
{
	t_vec	delta;

	delta = (t_vec){0, 0};
	if (c->k.w)
		delta = (t_vec){c->pl.dir.x * MOVE_SPEED, c->pl.dir.y * MOVE_SPEED};
	if (c->k.s)
		delta = (t_vec){-c->pl.dir.x * MOVE_SPEED, -c->pl.dir.y * MOVE_SPEED};
	if (c->k.a)
		delta = (t_vec){c->pl.dir.y * MOVE_SPEED, -c->pl.dir.x * MOVE_SPEED};
	if (c->k.d)
		delta = (t_vec){-c->pl.dir.y * MOVE_SPEED, c->pl.dir.x * MOVE_SPEED};
	move_player(c, delta);
}

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

	handle_inputs(c);
	draw_ceiling_floor(c);
	x = -1;
	while (++x < WIDTH)
		cast_column(c, x);
	mlx_put_image_to_window(c->mlx, c->win, c->frame.ptr, 0, 0);
	return (0);
}
