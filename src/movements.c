/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:35:17 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/22 22:40:45 by hawayda          ###   ########.fr       */
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

// int	on_mouse_move(int x, int y, t_cub *c)
// {
// 	double	delta;

// 	(void)y;
// 	if (c->mouse_prev_x == -1)
// 		c->mouse_prev_x = x;
// 	if (x != c->mouse_prev_x)
// 	{
// 		delta = (x - c->mouse_prev_x) * MOUSE_SENS;
// 		rotate(&c->pl, delta);
// 		c->mouse_prev_x = x;
// 	}
// 	return (0);
// }
