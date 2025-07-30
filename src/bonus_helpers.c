/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:34:11 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 10:34:11 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * put_pixel: draw one pixel into the frame image buffer
 */
void	put_pixel(t_cub *c, int x, int y, int color)
{
	char	*dst;
	int		bpp;
	int		line_len;

	bpp = c->frame.bpp;
	line_len = c->frame.line_len;
	dst = c->frame.addr + (y * line_len + x * (bpp / 8));
	*(unsigned int *)dst = color;
}
