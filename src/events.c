/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:22:30 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/16 20:22:30 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MOVE_SPEED 0.05
#define ROT_SPEED  0.04

static void	rotate(t_player *p, double a)
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

static void	move_player(t_cub *c, t_vec step)
{
	if (c->map.grid[(int)c->pl.pos.y][(int)(c->pl.pos.x + step.x)] != '1')
		c->pl.pos.x += step.x;
	if (c->map.grid[(int)(c->pl.pos.y + step.y)][(int)c->pl.pos.x] != '1')
		c->pl.pos.y += step.y;
}

/* --- MiniLibX hooks ------------------------------------------- */

int	on_keydown(int key, t_cub *c)
{
	if (key == 65307)
		return (on_close(c));
	if (key == 119)
		move_player(c, (t_vec){c->pl.dir.x * MOVE_SPEED,
				c->pl.dir.y * MOVE_SPEED});
	else if (key == 115)
		move_player(c, (t_vec){-c->pl.dir.x * MOVE_SPEED,
				-c->pl.dir.y * MOVE_SPEED});
	else if (key == 97)
		move_player(c, (t_vec){c->pl.dir.y * MOVE_SPEED,
				-c->pl.dir.x * MOVE_SPEED});
	else if (key == 100)
		move_player(c, (t_vec){-c->pl.dir.y * MOVE_SPEED,
				c->pl.dir.x * MOVE_SPEED});
	else if (key == 65361)
		rotate(&c->pl, -ROT_SPEED);
	else if (key == 65363)
		rotate(&c->pl, ROT_SPEED);
	return (0);
}

int	on_close(t_cub *c)
{
	free_and_exit(c, 0, NULL);
	return (0);
}
