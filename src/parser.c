/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:40:54 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/29 17:40:10 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**  Parse F and C exactly once each.  Advances *i past them.
*/
bool	parse_colors(t_cub *c, char **lines, int *i)
{
	bool	floor_seen;
	bool	ceil_seen;

	floor_seen = false;
	ceil_seen = false;
	while (lines[*i] && lines[*i][0] != '\0')
	{
		if (!handle_color_line(c, lines[*i], &floor_seen, &ceil_seen))
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

static bool	parse_map(t_cub *c, char **lines, int start)
{
	int		y;
	int		x;
	char	ch;

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
		{
			ch = lines[start + y][x];
			if (!valid_cell(ch))
				return (false);
			if (ft_strchr("NSEW", ch))
			{
				if (!set_player(c, x, y, ch))
					return (false);
			}
			else if (ch == DOOR_CLOSED && !door_add(c, x, y))
				return (false);
			else if (ch == SPRITE_CHAR && !sprite_add(c, x, y))
				return (false);
		}
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
		return (cleanup_cub(cub), false);
	i = 0;
	if (!load_elements(cub, cub->raw_lines, &i) || !cub->raw_lines[i])
		return (cleanup_cub(cub), false);
	if (!parse_map(cub, cub->raw_lines, i))
		return (cleanup_cub(cub), false);
	fill_spaces_with_walls(cub->map.grid, cub->map.h, cub->map.w);
	return (true);
}
