/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:42:09 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 11:56:27 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* the public entry point now just chains them */
void	compute_tex(t_cub *c, t_dda *d)
{
	compute_draw_limits(d);
	compute_texture_mapping(c, d);
}

static void	draw_tex_column(t_cub *c, t_dda *d, int x)
{
	int		y;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;

	step = 1.0 * c->tex[d->tex_id].img.h / d->line_h;
	tex_pos = (d->draw_s - HEIGHT / 2 + d->line_h / 2) * step;
	y = d->draw_s;
	while (y <= d->draw_e)
	{
		tex_y = (int)tex_pos & (c->tex[d->tex_id].img.h - 1);
		tex_pos += step;
		color = *(int *)(c->tex[d->tex_id].img.addr
				+ tex_y * c->tex[d->tex_id].img.line_len
				+ d->tex_x * (c->tex[d->tex_id].img.bpp / 8));
		*(int *)(c->frame.addr + y * c->frame.line_len
				+ x * (c->frame.bpp / 8)) = color;
		y++;
	}
}

void	cast_column(t_cub *c, int x)
{
	t_dda	d;

	init_dda(c, &d, x);
	compute_tex(c, &d);
	draw_tex_column(c, &d, x);
	c->zbuf[x] = d.perp_dist;
}
