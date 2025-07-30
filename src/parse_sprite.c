/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:32:43 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 21:15:16 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ───────────────────── parse “SPR <n> <p0> <p1> …” line ───────────────── */
bool	parse_sprite_line(t_cub *c, char *line)
{
	char	**sp;
	int		want;
	int		i;

	if (ft_strncmp(line, "SPR ", 4))
		return (false);
	sp = ft_split(line + 4, ' ');
	if (!sp)
		return (c->err = "Alloc.", false);
	want = ft_atoi(sp[0]);
	if (!sp || want <= 0 || want > MAX_SPR_FR)
		return (free_map(sp), c->err = "Bad SPR header", false);
	c->spr.count = want;
	i = 0;
	while (i < want && sp[i + 1])
	{
		c->spr.frame[i].ptr = ft_strdup(sp[i + 1]);
		if (!c->spr.frame[i].ptr)
			return (free_map(sp), c->err = "Alloc.", false);
		i++;
	}
	if (i != want)
		return (free_map(sp), c->err = "SPR missing frames.", false);
	return (free_map(sp), true);
}
