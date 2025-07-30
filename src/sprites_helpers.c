/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:59:29 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 10:59:29 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	sprite_transform(t_cub *c, t_sprite *s, double *tx, double *ty)
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
