/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:35:17 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/28 16:44:27 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	setup_mouse(t_cub *c)
{
	if (mlx_mouse_hide(c->mlx, c->win) < 0)
		return (false);
	mlx_mouse_move(c->mlx, c->win, MOUSE_CX, MOUSE_CY);
	c->mouse_prev_x = MOUSE_CX;
	return (true);
}

int	on_mouse_move(int x, int y, t_cub *c)
{
	(void)y;
	if (x == MOUSE_CX)
		return (0);
	rotate(&c->pl, (x - MOUSE_CX) * MOUSE_SENS);
	mlx_mouse_move(c->mlx, c->win, MOUSE_CX, MOUSE_CY);
	return (0);
}

/*
 * is_wall_at: returns true if map cell (mx, my) is a wall or out of bounds.
 */
static bool	is_wall_at(int mx, int my, t_map *map)
{
	if (my < 0)
		return (true);
	if (my >= map->h)
		return (true);
	if (mx < 0)
		return (true);
	if (mx >= map->w)
		return (true);
	if (map->grid[my][mx] == '1')
		return (true);
	return (false);
}
