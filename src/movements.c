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

/*
 * is_wall_at: returns true if map cell (mx, my) is a wall or out of bounds.
 */
static bool	is_wall_at(int mx, int my, t_map *map)
{
	if (my < 0 || my >= map->h
		|| mx < 0 || mx >= map->w
		|| map->grid[my][mx] == '1')
		return (true);
	return (false);
}
