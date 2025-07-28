/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:39:14 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/28 16:11:48 by hawayda          ###   ########.fr       */
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
**  Try to parse one texture line.  If 'line' begins with NO/SO/WE/EA + space,
**  dup the path, validate .xpm extension and duplicates, store into c->tex[id].
**  On success returns true and writes the numeric id; on non‐texture line
**  returns false; on error sets c->err and returns false as well.
*/
static bool	parse_texture_line(t_cub *c, char *line, int *out_id)
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

/*
**  Loop through exactly four texture lines at &lines[*i].  For each one:
**    - parse_texture_line (dup + .xpm check)
**    - then open()/close() that path to verify it exists
**  On any failure we free the dup’d path, set c->err and return false.
*/
bool	parse_textures(t_cub *c, char **lines, int *i)
{
	int	id;
	int	fd;
	int	count;

	count = 0;
	while (lines[*i] && *lines[*i])
	{
		if (!parse_texture_line(c, lines[*i], &id))
			break ;
		fd = open(c->tex[id].img.ptr, O_RDONLY);
		if (fd < 0)
			return (free(c->tex[id].img.ptr),
				c->err = "Texture file not found", false);
		close(fd);
		count++;
		(*i)++;
	}
	if (count != 4)
		return (c->err = "Missing texture element", false);
	return (true);
}
