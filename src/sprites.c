/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:25:19 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/29 18:10:07 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ───────────────────────── helper: load one XPM frame ──────────────────── */
static bool load_frame(t_cub *c, int idx, char *path)
{
    t_img *im = &c->spr.frame[idx];

    im->ptr = mlx_xpm_file_to_image(c->mlx, path, &im->w, &im->h);
    if (!im->ptr)
        return (c->err = "Sprite xpm load failed", false);
    im->addr = mlx_get_data_addr(im->ptr, &im->bpp,
                                 &im->line_len, &im->endian);
    return (true);
}

/* ───────────────────────────── add one instance ───────────────────────── */
bool	sprite_add(t_cub *c, int x, int y)
{
	t_sprite *s;

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
void sprite_tick(t_cub *c)
{
    double    now = get_time_ms() / 1000.0;
    t_sprite *s;

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

/* ───────────────── helper: draw one sprite w/ depth culling ───────────── */
static void draw_one_sprite(t_cub *c, t_sprite *s)
{
    t_img  *tex = &c->spr.frame[s->frame_idx];
    double  dx  = s->x - c->pl.pos.x;
    double  dy  = s->y - c->pl.pos.y;
    double  inv = 1.0 / (c->pl.plane.x * c->pl.dir.y
                       - c->pl.dir.x   * c->pl.plane.y);
    double  tx  = inv * ( c->pl.dir.y * dx - c->pl.dir.x * dy);
    double  ty  = inv * (-c->pl.plane.y * dx + c->pl.plane.x * dy);
    if (ty <= 0.01)
        return ;
    int scr_x   = (int)((WIDTH / 2) * (1 + tx / ty));
    int size    = abs((int)(HEIGHT / ty));
    int y0      = ft_max(-size / 2 + HEIGHT / 2, 0);
    int y1      = ft_min( size / 2 + HEIGHT / 2, HEIGHT - 1);
    int x0      = ft_max(-size / 2 + scr_x, 0);
    int x1      = ft_min( size / 2 + scr_x, WIDTH - 1);
    int stripe  = x0;

    while (stripe <= x1)
    {
        int tex_x = (stripe - (-size / 2 + scr_x)) * tex->w / size;
        if (ty < c->zbuf[stripe])
        {
            int y = y0;
            while (y <= y1)
            {
                int d      = y * 256 - HEIGHT * 128 + size * 128;
                int tex_y  = (d * tex->h) / (size * 256);
                int color  = *(int *)(tex->addr
                              + tex_y * tex->line_len
                              + tex_x * (tex->bpp / 8));
                if (color & 0x00FFFFFF)
                    put_pixel(c, stripe, y, color);
                y++;
            }
        }
        stripe++;
    }
}

/* ─────────────────────── draw all sprites (unsorted) ─────────────────── */
void draw_sprites(t_cub *c)
{
    t_sprite *s = c->sprites;

    while (s)
    {
        draw_one_sprite(c, s);
        s = s->next;
    }
}

bool    load_sprite_frames(t_cub *c)
{
    int   i;
    char *p;

    if (c->spr.count == 0)
        return (true);
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
