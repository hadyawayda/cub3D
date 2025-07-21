/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:25:16 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/21 10:25:16 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define VALID_CHARS " 01NSEW"

/* ────────────────────────────────────────────────────────────────────────── */
/* return the char at (y,x) – or a space when x is outside the line          */
static char	safe_cell(const t_map *m, int y, int x)
{
	if (y < 0 || y >= m->h)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(m->grid[y]))
		return (' ');
	return (m->grid[y][x]);
}

/* ────────────────────────────────────────────────────────────────────────── */
static bool	is_open(char c)
{
	return (c == '0' || ft_strchr("NSEW", c));
}

/* check that every open tile is fully surrounded by non-void neighbours     */
static bool	check_walls(const t_map *m)
{
	int	y;
	int	x;
	int	row_len;

	y = -1;
	while (++y < m->h)
	{
		x = -1;
		row_len = (int)ft_strlen(m->grid[y]);
		while (m->grid[y][++x])
		{
			if (!is_open(m->grid[y][x]))
				continue ;
			if (y == 0 || x == 0 || y == m->h - 1 || x == row_len - 1)
				return (false);
			if (safe_cell(m, y, x - 1) == ' ' || safe_cell(m, y, x + 1) == ' '
				|| safe_cell(m, y - 1, x) == ' '
				|| safe_cell(m, y + 1, x) == ' ')
				return (false);
		}
	}
	return (true);
}

/* ────────────────────────────────────────────────────────────────────────── */
/* public entry – returns false on the first rule violation                  */
bool	map_validator(t_cub *cub)
{
	const t_map	*m;
	int			y;
	int			x;
	int			player;

	cub->err = NULL;
	m = &cub->map;
	if (m->h < 3 || m->w < 3)
		return (cub->err = "Map too small.", false);
	player = 0;
	y = -1;
	while (++y < m->h)
	{
		x = -1;
		while (m->grid[y][++x])
		{
			if (!ft_strchr(VALID_CHARS, m->grid[y][x]))
				return (cub->err = "Invalid character.", false);
			if (ft_strchr("NSEW", m->grid[y][x]) && ++player > 1)
				return (cub->err = "Multiple playerss", false);
		}
	}
	if (player != 1)
		return (cub->err = "No player found.", false);
	if (!check_walls(m))
		return (cub->err = "Map not closed.", false);
	return (true);
}
