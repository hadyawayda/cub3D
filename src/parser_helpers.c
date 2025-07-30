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
/* returns 0-3 on success, −1 when the line is NOT a wall-texture tag */
static int	get_tex_id(const char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (0);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (2);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (3);
	return (-1);
}

/* extract **exactly one** <path> token after the keyword ---------------- */
static char	*grab_texture_path(t_cub *c, const char *p)
{
	const char	*end;
	char		*path;

	while (*p == ' ')
		p++;
	if (*p == '\0')
		return (c->err = "Missing texture path", NULL);
	end = p;
	while (*end && *end != ' ')
		end++;
	while (*end == ' ')
		end++;
	if (*end != '\0')
		return (c->err = "Too many arguments for texture", NULL);
	path = ft_substr(p, 0, end - p);
	if (!path)
		return (c->err = "Allocation failure", NULL);
	if (!has_xpm_ext(path))
		return (free(path), c->err = "Texture not .xpm", NULL);
	return (path);
}

/* main entry: parse a wall-texture line ---------------------------------- */
bool	parse_wall_texture(t_cub *c, char *line, int *out_id)
{
	int		id;
	char	*path;

	id = get_tex_id(line);
	if (id == -1)
		return (false);
	if (c->tex[id].img.ptr)
		return (c->err = "Duplicate texture identifier", false);
	path = grab_texture_path(c, line + 3);
	if (!path)
		return (false);
	c->tex[id].img.ptr = path;
	*out_id = id;
	return (true);
}
