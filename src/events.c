/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:22:30 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/22 22:37:31 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_player *p, double a)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir.x;
	p->dir.x = p->dir.x * cos(a) - p->dir.y * sin(a);
	p->dir.y = old_dir_x * sin(a) + p->dir.y * cos(a);
	old_plane_x = p->plane.x;
	p->plane.x = p->plane.x * cos(a) - p->plane.y * sin(a);
	p->plane.y = old_plane_x * sin(a) + p->plane.y * cos(a);
}

void	move_player(t_cub *c, t_vec step)
{
	if (c->map.grid[(int)c->pl.pos.y][(int)(c->pl.pos.x + step.x)] != '1')
		c->pl.pos.x += step.x;
	if (c->map.grid[(int)(c->pl.pos.y + step.y)][(int)c->pl.pos.x] != '1')
		c->pl.pos.y += step.y;
}

int	on_keydown(int key, t_cub *c)
{
	if (key == KEY_W)
		c->k.w = true;
	else if (key == KEY_S)
		c->k.s = true;
	else if (key == KEY_A)
		c->k.a = true;
	else if (key == KEY_D)
		c->k.d = true;
	else if (key == KEY_LEFT)
		c->k.l = true;
	else if (key == KEY_RIGHT)
		c->k.r = true;
	else if (key == KEY_ESC)
		on_close(c);
	return (0);
}

int	on_keyup(int key, t_cub *c)
{
	if (key == KEY_W)
		c->k.w = false;
	else if (key == KEY_S)
		c->k.s = false;
	else if (key == KEY_A)
		c->k.a = false;
	else if (key == KEY_D)
		c->k.d = false;
	else if (key == KEY_LEFT)
		c->k.l = false;
	else if (key == KEY_RIGHT)
		c->k.r = false;
	return (0);
}

int	on_close(t_cub *c)
{
	free_and_exit(c, 0, NULL);
	return (0);
}
