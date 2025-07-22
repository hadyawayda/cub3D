/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:40:54 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/22 00:30:59 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	store_rgb(char *s, int *col)
{
	char	**sp;
	int		r;
	int		g;
	int		b;

	sp = ft_split(s, ',');
	if (!sp || !sp[0] || !sp[1] || !sp[2] || sp[3])
		return (free_map(sp), false);
	r = ft_atoi(sp[0]);
	g = ft_atoi(sp[1]);
	b = ft_atoi(sp[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_map(sp), false);
	*col = (r << 16) | (g << 8) | b;
	return (free_map(sp), true);
}

/*
**  Skip over any empty lines (elements can be separated by blank lines).
*/
static void	skip_empty_lines(char **lines, int *i)
{
	while (lines[*i] && lines[*i][0] == '\0')
		(*i)++;
}

/*
**  Parse F and C exactly once each.  Advances *i past them.
*/
static bool	parse_colors(t_cub *c, char **lines, int *i)
{
	bool	floor_seen;
	bool	ceil_seen;

	floor_seen = false;
	ceil_seen = false;
	while (lines[*i] && lines[*i][0] != '\0')
	{
		if (!ft_strncmp(lines[*i], "F ", 2))
		{
			if (floor_seen)
				return (c->err = "Duplicate floor color", false);
			if (!store_rgb(lines[*i] + 2, &c->floor_col))
				return (false);
			floor_seen = true;
		}
		else if (!ft_strncmp(lines[*i], "C ", 2))
		{
			if (ceil_seen)
				return (c->err = "Duplicate ceiling color", false);
			if (!store_rgb(lines[*i] + 2, &c->ceil_col))
				return (false);
			ceil_seen = true;
		}
		else
			break ;
		(*i)++;
	}
	if (!floor_seen || !ceil_seen)
		return (c->err = "Missing floor or ceiling color", false);
	return (true);
}

/*
**  load_elements: first textures, then colors, skipping blanks between.
**  *i should point at the first map-line when this returns true.
*/
bool	load_elements(t_cub *c, char **lines, int *i)
{
	skip_empty_lines(lines, i);
	if (!parse_textures(c, lines, i))
		return (false);
	skip_empty_lines(lines, i);
	if (!parse_colors(c, lines, i))
		return (false);
	skip_empty_lines(lines, i);
	return (check_required_elements(c));
}

static bool	set_player(t_cub *c, int x, int y, char ch)
{
	if (c->pl.pos.x != 0)
		return (false);
	c->pl.pos = (t_vec){x + 0.5, y + 0.5};
	if (ch == 'N')
		c->pl.dir = (t_vec){0, -1};
	else if (ch == 'S')
		c->pl.dir = (t_vec){0, 1};
	else if (ch == 'E')
		c->pl.dir = (t_vec){1, 0};
	else
		c->pl.dir = (t_vec){-1, 0};
	c->pl.plane = (t_vec){-0.66 * c->pl.dir.y, 0.66 * c->pl.dir.x};
	return (true);
}

static bool	parse_map(t_cub *c, char **lines, int start)
{
	int	y;
	int	x;

	c->map.grid = &lines[start];
	c->map.h = 0;
	while (lines[start + c->map.h])
		c->map.h++;
	c->map.w = 0;
	y = -1;
	while (lines[start + ++y])
	{
		c->map.w = ft_max(c->map.w, (int)ft_strlen(lines[start + y]));
		x = -1;
		while (lines[start + y][++x])
			if (!valid_cell(lines[start + y][x]) || (ft_strchr("NSEW",
						lines[start + y][x]) && !set_player(c, x, y, lines[start
						+ y][x])))
				return (false);
	}
	return (c->pl.pos.x != 0);
}

bool	parse_file(t_cub *cub, char *path)
{
	char	*file;
	int		i;

	file = ft_file_to_str(path);
	if (!file)
		return (free(file), false);
	cub->raw_lines = ft_split(file, '\n');
	free(file);
	if (!cub->raw_lines)
		return (false);
	i = 0;
	if (!load_elements(cub, cub->raw_lines, &i) || !cub->raw_lines[i])
		return (false);
	if (!parse_map(cub, cub->raw_lines, i))
		return (false);
	fill_spaces_with_walls(cub->map.grid, cub->map.h, cub->map.w);
	return (true);
}
