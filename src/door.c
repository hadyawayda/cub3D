/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:19:04 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 11:58:13 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	door_add(t_cub *c, int x, int y)
{
	t_door	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (false);
	new->x = x;
	new->y = y;
	new->open = false;
	new->next = c->doors;
	c->doors = new;
	return (true);
}

void	door_toggle(t_cub *c)
{
	t_door	*d;
	double	dx;
	double	dy;
	double	dist;

	d = c->doors;
	while (d)
	{
		dx = d->x + 0.5 - c->pl.pos.x;
		dy = d->y + 0.5 - c->pl.pos.y;
		dist = sqrt(dx * dx + dy * dy);
		if (dist < 1.2)
		{
			d->open = !d->open;
			if (d->open)
				c->map.grid[d->y][d->x] = DOOR_OPEN;
			else
				c->map.grid[d->y][d->x] = DOOR_CLOSED;
			return ;
		}
		d = d->next;
	}
}

void	draw_mm_closed(t_cub *c, int gx, int gy)
{
	draw_square(c, gx, gy, DOOR_MM_COL);
}

void	draw_mm_open(t_cub *c, int gx, int gy)
{
	int	px;
	int	py;
	int	s;
	int	i;

	px = gx * MINIMAP_SCALE;
	py = gy * MINIMAP_SCALE;
	s = MINIMAP_SCALE - 1;
	i = 0;
	while (i <= s)
	{
		put_pixel(c, px + i, py, DOOR_MM_COL);
		put_pixel(c, px + i, py + s, DOOR_MM_COL);
		put_pixel(c, px, py + i, DOOR_MM_COL);
		put_pixel(c, px + s, py + i, DOOR_MM_COL);
		i++;
	}
}
