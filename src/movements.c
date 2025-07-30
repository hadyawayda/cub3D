/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:22:00 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 11:22:02 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	setup_mouse(t_cub *c)
{
	const int	mouse_cx = WIDTH / 2;
	const int	mouse_cy = HEIGHT / 2;

	if (mlx_mouse_hide(c->mlx, c->win) < 0)
		return (false);
	mlx_mouse_move(c->mlx, c->win, mouse_cx, mouse_cy);
	c->mouse_prev_x = mouse_cx;
	return (true);
}

int	on_mouse_move(int x, int y, t_cub *c)
{
	const int	mouse_cx = WIDTH / 2;
	const int	mouse_cy = HEIGHT / 2;

	(void)y;
	if (x == mouse_cx)
		return (0);
	rotate(&c->pl, (x - mouse_cx) * MOUSE_SENS);
	mlx_mouse_move(c->mlx, c->win, mouse_cx, mouse_cy);
	return (0);
}

/* 1 ─ build vector from keyboard state (≤ 20 lines) */
static t_vec	get_input_vec(t_cub *c)
{
	t_vec	v;

	v.x = 0.0;
	v.y = 0.0;
	if (c->k.w)
	{
		v.x += c->pl.dir.x;
		v.y += c->pl.dir.y;
	}
	if (c->k.s)
	{
		v.x -= c->pl.dir.x;
		v.y -= c->pl.dir.y;
	}
	if (c->k.a)
	{
		v.x += c->pl.dir.y;
		v.y -= c->pl.dir.x;
	}
	if (c->k.d)
	{
		v.x -= c->pl.dir.y;
		v.y += c->pl.dir.x;
	}
	return (v);
}

/* 2 ─ normalise, scale, collide, move (≤ 20 lines) */
void	apply_movement(t_cub *c)
{
	t_vec	v;
	double	len;

	v = get_input_vec(c);
	len = sqrt(v.x * v.x + v.y * v.y);
	if (len > 0.0)
	{
		v.x = v.x / len * MOVE_SPEED;
		v.y = v.y / len * MOVE_SPEED;
		move_player(c, v);
	}
}
