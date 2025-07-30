/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:25:19 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 21:16:43 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ───────────────────────────── add one instance ───────────────────────── */
bool	sprite_add(t_cub *c, int x, int y)
{
	t_sprite	*s;

	s = malloc(sizeof(*s));
	if (!s)
		return (false);
	s->x = x + 0.5;
	s->y = y + 0.5;
	s->frame_idx = 0;
	s->next = c->sprites;
	c->sprites = s;
	return (true);
}

/* ───────────────────────────── tick animation ─────────────────────────── */
void	sprite_tick(t_cub *c)
{
	double		now;
	t_sprite	*s;

	now = get_time_ms() / 1000.0;
	if (now - c->spr_time < 1.0 / SPRITE_FPS)
		return ;
	c->spr_time = now;
	s = c->sprites;
	while (s)
	{
		s->frame_idx++;
		if (s->frame_idx >= c->spr.count)
			s->frame_idx = 0;
		s = s->next;
	}
}

/* ─────────────────────── draw all sprites (unsorted) ─────────────────── */
void	draw_sprites(t_cub *c)
{
	t_sprite	*s;

	s = c->sprites;
	while (s)
	{
		draw_one_sprite(c, s);
		s = s->next;
	}
}

bool	load_sprite_frames(t_cub *c)
{
	int		i;
	char	*p;

	if (c->spr.count <= 0)
		return (true);
	if (c->spr.count > MAX_SPR_FR)
		return (c->err = "Too many sprite frames.", false);
	i = 0;
	while (i < c->spr.count)
	{
		p = (char *)c->spr.frame[i].ptr;
		c->spr.frame[i].ptr = mlx_xpm_file_to_image(c->mlx, p,
				&c->spr.frame[i].w, &c->spr.frame[i].h);
		if (!c->spr.frame[i].ptr)
			return (false);
		c->spr.frame[i].addr = mlx_get_data_addr(c->spr.frame[i].ptr,
				&c->spr.frame[i].bpp, &c->spr.frame[i].line_len,
				&c->spr.frame[i].endian);
		free(p);
		i++;
	}
	return (true);
}
