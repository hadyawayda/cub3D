/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:32:06 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 11:32:06 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	cell_is_wall(t_cub *c, int gx, int gy)
{
	t_door	*d;

	if (gy < 0 || gy >= c->map.h || gx < 0 || gx >= c->map.w)
		return (true);
	if (c->map.grid[gy][gx] == '1')
		return (true);
	if (c->map.grid[gy][gx] != DOOR_CLOSED)
		return (false);
	d = c->doors;
	while (d)
	{
		if (d->x == gx && d->y == gy)
			return (!d->open);
		d = d->next;
	}
	return (false);
}

/* return true if a circle of radius R centred at (x,y) touches a wall */
bool	hits_wall(t_cub *c, double x, double y)
{
	int	gx;
	int	gy;

	gx = (int)(x - COLLISION_RADIUS);
	gy = (int)(y - COLLISION_RADIUS);
	if (cell_is_wall(c, gx, gy))
		return (true);
	gx = (int)(x + COLLISION_RADIUS);
	gy = (int)(y - COLLISION_RADIUS);
	if (cell_is_wall(c, gx, gy))
		return (true);
	gx = (int)(x - COLLISION_RADIUS);
	gy = (int)(y + COLLISION_RADIUS);
	if (cell_is_wall(c, gx, gy))
		return (true);
	gx = (int)(x + COLLISION_RADIUS);
	gy = (int)(y + COLLISION_RADIUS);
	if (cell_is_wall(c, gx, gy))
		return (true);
	return (false);
}
