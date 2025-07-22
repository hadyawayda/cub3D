/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:39:14 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/22 00:27:44 by hawayda          ###   ########.fr       */
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

static bool	set_tex_path(t_cub *c, int idx, char *path, bool seen[4])
{
	if (seen[idx])
		return (c->err = "Duplicate texture identifier", false);
	c->tex[idx].img.ptr = ft_strdup(path);
	if (!c->tex[idx].img.ptr)
		return (c->err = "Allocation failure", false);
	seen[idx] = true;
	return (true);
}

/*
**  Parse only the four texture lines, in any order, no duplicates allowed.
**  Leaves *i pointing at the first non-texture line.
*/
bool	parse_textures(t_cub *c, char **lines, int *i)
{
	bool	seen[4];

	ft_bzero(seen, sizeof(seen));
	while (lines[*i] && *lines[*i] != '\0')
	{
		if (!ft_strncmp(lines[*i], "NO ", 3))
		{
			if (!set_tex_path(c, 0, lines[*i] + 3, seen))
				return (false);
		}
		else if (!ft_strncmp(lines[*i], "SO ", 3))
		{
			if (!set_tex_path(c, 1, lines[*i] + 3, seen))
				return (false);
		}
		else if (!ft_strncmp(lines[*i], "WE ", 3))
		{
			if (!set_tex_path(c, 2, lines[*i] + 3, seen))
				return (false);
		}
		else if (!ft_strncmp(lines[*i], "EA ", 3))
		{
			if (!set_tex_path(c, 3, lines[*i] + 3, seen))
				return (false);
		}
		else
			break ;
		(*i)++;
	}
	if (!seen[0] || !seen[1] || !seen[2] || !seen[3])
		return (c->err = "Missing texture identifier", false);
	return (true);
}
