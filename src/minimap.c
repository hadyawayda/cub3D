/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:57:53 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 10:34:27 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * draw_square: fill a MINIMAP_SCALE×MINIMAP_SCALE block at (cx,cy)
 */
void	draw_square(t_cub *c, int cx, int cy, int color)
{
	int	sx;
	int	sy;
	int	px;
	int	py;

	sy = 0;
	while (sy < MINIMAP_SCALE)
	{
		sx = 0;
		while (sx < MINIMAP_SCALE)
		{
			px = cx * MINIMAP_SCALE + sx;
			py = cy * MINIMAP_SCALE + sy;
			put_pixel(c, px, py, color);
			sx++;
		}
		sy++;
	}
}

/* ─── 2.  scan the door list once and paint icons ─────────────────────── */
static void	draw_minimap_doors(t_cub *c)
{
	t_door	*d;

	d = c->doors;
	while (d)
	{
		if (d->open)
			draw_mm_open(c, d->x, d->y);
		else
			draw_mm_closed(c, d->x, d->y);
		d = d->next;
	}
}

/*
 * draw_minimap_tiles: draw the map cells as squares
 */
static void	draw_minimap_tiles(t_cub *c)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < c->map.h)
	{
		x = 0;
		while (x < c->map.w)
		{
			if (c->map.grid[y][x] == '1')
				color = 0x808080;
			else
				color = 0x202020;
			draw_square(c, x, y, color);
			x++;
		}
		y++;
	}
}

/*
 * draw_minimap_player: draw the player indicator on the minimap
 */
static void	draw_minimap_player(t_cub *c)
{
	int	px;
	int	py;
	int	x;
	int	y;

	px = (int)(c->pl.pos.x * MINIMAP_SCALE) - 2;
	py = (int)(c->pl.pos.y * MINIMAP_SCALE) - 2;
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			put_pixel(c, px + x, py + y, 0xFF0000);
			x++;
		}
		y++;
	}
}

/*
 * draw_minimap: draw both the map and the player
 */
void	draw_minimap(t_cub *c)
{
	draw_minimap_tiles(c);
	draw_minimap_doors(c);
	draw_minimap_player(c);
}
