/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:25:19 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 02:24:33 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ───────────────────────── helper: load one XPM frame ──────────────────── */
static bool	load_frame(t_cub *c, int idx, char *path)
{
	t_img	*im;

	im = &c->spr.frame[idx];
	im->ptr = mlx_xpm_file_to_image(c->mlx, path, &im->w, &im->h);
	if (!im->ptr)
		return (c->err = "Sprite xpm load failed", false);
	im->addr = mlx_get_data_addr(im->ptr, &im->bpp, &im->line_len, &im->endian);
	return (true);
}

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

static bool	sprite_transform(t_cub *c, t_sprite *s, double *tx, double *ty)
{
	double	dx;
	double	dy;
	double	inv;

	dx = s->x - c->pl.pos.x;
	dy = s->y - c->pl.pos.y;
	inv = 1.0 / (c->pl.plane.x * c->pl.dir.y - c->pl.dir.x * c->pl.plane.y);
	*tx = inv * (c->pl.dir.y * dx - c->pl.dir.x * dy);
	*ty = inv * (-c->pl.plane.y * dx + c->pl.plane.x * dy);
	return (*ty > 0.01);
}

static void	sprite_compute_rect(double tx, double ty, int *scr_x, int *size,
		int *y0, int *y1)
{
	*scr_x = (int)((WIDTH / 2) * (1 + tx / ty));
	*size = abs((int)(HEIGHT / ty));
	*y0 = ft_max(-*size / 2 + HEIGHT / 2, 0);
	*y1 = ft_min(*size / 2 + HEIGHT / 2, HEIGHT - 1);
}

static void	sprite_compute_xbounds(int scr_x, int size, int *x0, int *x1)
{
	*x0 = ft_max(-size / 2 + scr_x, 0);
	*x1 = ft_min(size / 2 + scr_x, WIDTH - 1);
}

/* ─── draw one vertical column of a sprite ─────────────────────────────── */
static void	draw_sprite_column(t_cub *c, t_img *tex, int stripe, int size,
		int y0, int y1, int scr_x)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	d;
	int	color;

	tex_x = (stripe - (-size / 2 + scr_x)) * tex->w / size;
	y = y0;
	while (y <= y1)
	{
		d = y * 256 - HEIGHT * 128 + size * 128;
		tex_y = (d * tex->h) / (size * 256);
		color = *(int *)(tex->addr + tex_y * tex->line_len + tex_x * (tex->bpp
					/ 8));
		if (color & 0x00FFFFFF)
			put_pixel(c, stripe, y, color);
		y++;
	}
}

/* ─── scan across sprite width, depth‐test each column ─────────────────── */
static void	draw_sprite_segment(t_cub *c, t_img *tex, int size, int y0, int y1,
		int scr_x, double ty)
{
	int	stripe;
	int	end;

	stripe = ft_max(-size / 2 + scr_x, 0);
	end = ft_min(size / 2 + scr_x, WIDTH - 1);
	while (stripe <= end)
	{
		if (ty < c->zbuf[stripe])
			draw_sprite_column(c, tex, stripe, size, y0, y1, scr_x);
		stripe++;
	}
}

static void	draw_one_sprite(t_cub *c, t_sprite *s)
{
	double	tx;
	double	ty;
	int		scr_x;
	int		size;
	int		y0;
	int		y1;
	int		x0;
	int		x1;

	if (!sprite_transform(c, s, &tx, &ty))
		return ;
	sprite_compute_rect(tx, ty, &scr_x, &size, &y0, &y1);
	sprite_compute_xbounds(scr_x, size, &x0, &x1);
	draw_sprite_segment(c, &c->spr.frame[s->frame_idx], size, y0, y1, scr_x,
		ty);
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
		return (c->err = "Too many sprite frames", false);
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
