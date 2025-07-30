/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:11:48 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 11:11:48 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sprite_compute_rect(t_sprite_segment *seg, double tx,
				double ty)
{
	seg->scr_x = (int)((WIDTH / 2) * (1 + tx / ty));
	seg->size = abs((int)(HEIGHT / ty));
	seg->y0 = ft_max(-seg->size / 2 + HEIGHT / 2, 0);
	seg->y1 = ft_min(seg->size / 2 + HEIGHT / 2, HEIGHT - 1);
}

static void	sprite_compute_xbounds(int scr_x, int size, int *x0, int *x1)
{
	*x0 = ft_max(-size / 2 + scr_x, 0);
	*x1 = ft_min(size / 2 + scr_x, WIDTH - 1);
}

/* ─── draw one vertical column of a sprite ─────────────────────────────── */
static void	draw_sprite_column(t_cub *c, t_sprite_segment *seg,
				int stripe)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	d;
	int	color;

	tex_x = (stripe - (-seg->size / 2 + seg->scr_x))
		* seg->tex->w / seg->size;
	y = seg->y0;
	while (y <= seg->y1)
	{
		d = y * 256 - HEIGHT * 128 + seg->size * 128;
		tex_y = (d * seg->tex->h) / (seg->size * 256);
		color = *(int *)(seg->tex->addr
				+ tex_y * seg->tex->line_len
				+ tex_x * (seg->tex->bpp / 8));
		if (color & 0x00FFFFFF)
			put_pixel(c, stripe, y, color);
		y++;
	}
}

/* ─── scan across sprite width, depth‐test each column ─────────────────── */
static void	draw_sprite_segment(t_cub *c, t_sprite_segment *seg)
{
	int	stripe;
	int	end;

	stripe = ft_max(-seg->size / 2 + seg->scr_x, 0);
	end = ft_min(seg->size / 2 + seg->scr_x, WIDTH - 1);
	while (stripe <= end)
	{
		if (seg->ty < c->zbuf[stripe])
			draw_sprite_column(c, seg, stripe);
		stripe++;
	}
}

void	draw_one_sprite(t_cub *c, t_sprite *s)
{
	double				tx;
	double				ty;
	t_sprite_segment	seg;
	int					x0;
	int					x1;

	if (!sprite_transform(c, s, &tx, &ty))
		return ;
	seg.tex = &c->spr.frame[s->frame_idx];
	seg.ty = ty;
	sprite_compute_rect(&seg, tx, ty);
	sprite_compute_xbounds(seg.scr_x, seg.size, &x0, &x1);
	draw_sprite_segment(c, &seg);
}
