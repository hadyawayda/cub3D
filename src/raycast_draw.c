/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:42:09 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 10:58:35 by hawayda          ###   ########.fr       */
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
	int	y;
	int	dy;
	int	tex_y;
	int	color;

	y = d->draw_s;
	while (y <= d->draw_e)
	{
		dy = y * 256 - HEIGHT * 128 + d->line_h * 128;
		tex_y = (dy * c->tex[d->tex_id].img.h) / d->line_h / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= c->tex[d->tex_id].img.h)
			tex_y = c->tex[d->tex_id].img.h - 1;
		color = *(int *)(c->tex[d->tex_id].img.addr + tex_y
				* c->tex[d->tex_id].img.line_len + d->tex_x
				* (c->tex[d->tex_id].img.bpp / 8));
		*(int *)(c->frame.addr + y * c->frame.line_len + x * (c->frame.bpp
					/ 8)) = color;
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
