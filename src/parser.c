/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:40:54 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 10:52:08 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**  load_elements: first textures, then colors, skipping blanks between.
**  *i should point at the first map-line when this returns true.
*/
static bool	parse_elements_loop(t_elem_ctx *x)
{
	int	id;

	while (x->lines[*x->i] && x->lines[*x->i][0] != '\0')
	{
		if (parse_sprite_line(x->c, x->lines[*x->i]))
			(*x->i)++;
		else if (parse_wall_texture(x->c, x->lines[*x->i], &id))
			(*x->i)++;
		else if (x->c->err)
			return (false);
		else if (handle_color_line(x->c, x->lines[*x->i],
				x->floor_seen, x->ceil_seen))
			(*x->i)++;
		else if (x->c->err)
			return (false);
		else if (valid_cell(x->lines[*x->i][0]))
			break ;
		else
			return (x->c->err = "Unknown element line", false);
		skip_empty_lines(x->lines, x->i);
	}
	return (true);
}

bool	load_elements(t_cub *c, char **lines, int *i)
{
	bool		floor_seen;
	bool		ceil_seen;
	t_elem_ctx	ctx;

	floor_seen = false;
	ceil_seen = false;
	ctx = (t_elem_ctx){c, lines, i, &floor_seen, &ceil_seen};
	skip_empty_lines(lines, i);
	if (!parse_elements_loop(&ctx))
		return (false);
	if (lines[*i] && valid_cell(lines[*i][0])
		&& (!c->tex[0].img.ptr || !c->tex[1].img.ptr
		|| !c->tex[2].img.ptr || !c->tex[3].img.ptr))
		return (c->err = "Texture lines must appear above the map", false);
	if (!check_required_elements(c))
		return (c->err = "Missing element", false);
	if (!floor_seen || !ceil_seen)
		return (c->err = "Missing floor or ceiling color", false);
	return (true);
}

/* 2. walk every map row -------------------------------------------------- */
static bool	scan_map_rows(t_cub *c, char **lines, int start)
{
	int	y;
	int	len;

	y = 0;
	while (lines[start + y])
	{
		len = (int)ft_strlen(lines[start + y]);
		c->map.w = ft_max(c->map.w, len);
		if (!process_map_row(c, lines[start + y], y))
			return (false);
		y++;
	}
	return (true);
}

/* 3. top-level ----------------------------------------------------------- */
static bool	parse_map(t_cub *c, char **lines, int start)
{
	c->map.grid = &lines[start];
	c->map.h = 0;
	while (lines[start + c->map.h])
		c->map.h++;
	c->map.w = 0;
	if (!scan_map_rows(c, lines, start))
		return (false);
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
