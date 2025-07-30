/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:51:50 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 10:51:50 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	process_map_row(t_cub *c, char *row, int y)
{
	int		x;
	char	ch;

	x = 0;
	while (row[x])
	{
		ch = row[x];
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
		x++;
	}
	return (true);
}

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
