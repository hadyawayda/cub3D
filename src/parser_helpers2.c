/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:46:26 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/22 22:37:57 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**  Return true if 's' ends in ".xpm"
*/
bool	has_xpm_ext(char *s)
{
	size_t	len;

	if (!s)
		return (false);
	len = ft_strlen(s);
	if (len < 5)
		return (false);
	return (ft_strcmp(s + len - 4, ".xpm") == 0);
}

/*
**  Skip over any empty lines (elements can be separated by blank lines).
*/
void	skip_empty_lines(char **lines, int *i)
{
	while (lines[*i] && lines[*i][0] == '\0')
		(*i)++;
}

bool	set_player(t_cub *c, int x, int y, char ch)
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

/* parse one F / C line, update flags, store rgb --------------------------- */
bool	handle_color_line(t_cub *c, char *line, bool *floor_seen,
		bool *ceil_seen)
{
	if (!ft_strncmp(line, "F ", 2))
	{
		if (*floor_seen)
			return (c->err = "Duplicate floor color", false);
		if (!store_rgb(line + 2, &c->floor_col))
			return (false);
		*floor_seen = true;
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		if (*ceil_seen)
			return (c->err = "Duplicate ceiling color", false);
		if (!store_rgb(line + 2, &c->ceil_col))
			return (false);
		*ceil_seen = true;
	}
	else
		return (false);
	return (true);
}
