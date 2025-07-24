/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:25:19 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/23 17:25:19 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double  sprite_dist(t_cub *c, t_sprite *s)
{
	double dx;
	double dy;

	dx = c->pl.pos.x - s->x;
	dy = c->pl.pos.y - s->y;
	return (dx * dx + dy * dy);
}

/*
 * init_sprites: scan map for '2' and build sprite array
 */
void    init_sprites(t_cub *c)
{
	int     y;
	int     x;
	int     count;
	int     idx;

	/* first pass: count them */
	y = 0;
	count = 0;
	while (y < c->map.h)
	{
		x = 0;
		while (x < c->map.w)
		{
			if (c->map.grid[y][x] == '2')
				count++;
			x++;
		}
		y++;
	}
	c->sprite_count = count;
	c->sprites = malloc(sizeof(t_sprite) * count);
	if (c->sprites == NULL)
		return ;
	/* second pass: store their coords */
	y = 0;
	idx = 0;
	while (y < c->map.h)
	{
		x = 0;
		while (x < c->map.w)
		{
			if (c->map.grid[y][x] == '2')
			{
				c->sprites[idx].x = x + 0.5;
				c->sprites[idx].y = y + 0.5;
				c->sprites[idx].frame = 0;
				c->sprites[idx].timer = 0.0;
				idx++;
			}
			x++;
		}
		y++;
	}
}

/*
 * update_sprites: advance each sprite's animation by dt seconds
 * then sort by distance descending (simple insertion sort)
 */
void    update_sprites(t_cub *c, double dt)
{
	int         i;
	double      dur;
	t_sprite    tmp;
	int         j;

	i = 0;
	dur = SPRITE_DURATION;
	while (i < c->sprite_count)
	{
		c->sprites[i].timer += dt;
		if (c->sprites[i].timer >= dur)
		{
			c->sprites[i].timer -= dur;
			c->sprites[i].frame++;
			if (c->sprites[i].frame >= SPRITE_FRAMES)
				c->sprites[i].frame = 0;
		}
		i++;
	}
	/* insertion‐sort by descending distance */
	i = 1;
	while (i < c->sprite_count)
	{
		tmp = c->sprites[i];
		j = i - 1;
		while (j >= 0
			&& sprite_dist(c, &c->sprites[j]) < sprite_dist(c, &tmp))
		{
			c->sprites[j + 1] = c->sprites[j];
			j--;
		}
		c->sprites[j + 1] = tmp;
		i++;
	}
}

/*
 * render_sprites: project each sprite onto screen and draw its current frame
 */
void    render_sprites(t_cub *c)
{
	int         i;
	t_sprite    *s;
	double      spr_x;
	double      spr_y;
	double      inv_det;
	double      tr_x;
	double      tr_y;
	int         spr_scr_x;
	int         spr_h;
	int         draw_start_y;
	int         draw_end_y;
	int         stripe;

	i = 0;
	while (i < c->sprite_count)
	{
		s = &c->sprites[i];
		/* translate to camera space */
		spr_x = s->x - c->pl.pos.x;
		spr_y = s->y - c->pl.pos.y;
		inv_det = 1.0 / (c->pl.plane.x * c->pl.dir.y
					   - c->pl.dir.x * c->pl.plane.y);
		tr_x = inv_det * (c->pl.dir.y * spr_x - c->pl.dir.x * spr_y);
		tr_y = inv_det *(-c->pl.plane.y * spr_x + c->pl.plane.x * spr_y);
		/* screen x */
		spr_scr_x = (int)((WIDTH / 2) * (1 + tr_x / tr_y));
		/* sprite size */
		spr_h = abs((int)(HEIGHT / tr_y));
		/* vertical draw limits */
		draw_start_y = -spr_h / 2 + HEIGHT / 2;
		draw_end_y = spr_h / 2 + HEIGHT / 2;
		/* draw the vertical stripes of the sprite */
		stripe = spr_scr_x - spr_h / 2;
		while (stripe < spr_scr_x + spr_h / 2)
		{
			/* for each stripe, sample texture from
			   c->sprite_textures[s->frame] at correct u,v */
			/* then if tr_y > 0 and stripe in-screen and depth < zbuffer[stripe]:
			   draw_pixel(stripe, y, color) */
			stripe++;
		}
		i++;
	}
}