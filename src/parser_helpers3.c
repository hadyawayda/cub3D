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
