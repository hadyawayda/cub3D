/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:39:14 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 12:03:05 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Replace every space in the map-rectangle [0..h-1][0..w-1] with '1'
 * so that gaps in ragged lines become walls.
 */
void	fill_spaces_with_walls(char **grid, int h, int w)
{
	int	y;
	int	x;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (grid[y][x] == ' ')
				grid[y][x] = '1';
			x++;
		}
		y++;
	}
}

/* Returns true if ‘path’ ends in “.cub” */
bool	is_cub_file(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4)
		return (false);
	return (ft_strncmp(path + len - 4, ".cub", 4) == 0);
}

/*
**  Try to parse one texture line.  If 'line' begins with NO/SO/WE/EA + space,
**  dup the path, validate .xpm extension and duplicates, store into c->tex[id].
**  On success returns true and writes the numeric id; on non‐texture line
**  returns false; on error sets c->err and returns false as well.
*/
/* 1. handle a wall-texture line: “NO|SO|WE|EA <path>”         */
/*    returns true on success, false otherwise.                */
bool	parse_wall_texture(t_cub *c, char *line, int *out_id)
{
	int		id;
	char	*path;

	if (!ft_strncmp(line, "NO ", 3))
		id = 0;
	else if (!ft_strncmp(line, "SO ", 3))
		id = 1;
	else if (!ft_strncmp(line, "WE ", 3))
		id = 2;
	else if (!ft_strncmp(line, "EA ", 3))
		id = 3;
	else
		return (false);
	if (c->tex[id].img.ptr)
		return (c->err = "Duplicate texture identifier", false);
	path = ft_strdup(line + 3);
	if (!path)
		return (c->err = "Allocation failure", false);
	if (!has_xpm_ext(path))
		return (free(path), c->err = "Texture not .xpm", false);
	c->tex[id].img.ptr = path;
	*out_id = id;
	return (true);
}
