/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:41:47 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/17 02:31:50 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map)
{
	size_t i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	free_and_exit(t_cub *c, int status, char *msg)
{
	int	i;

	if (msg)
		ft_putendl_fd(msg, 2);
	if (c->frame.ptr)
		mlx_destroy_image(c->mlx, c->frame.ptr);
	i = -1;
	while (++i < 4)
		if (c->tex[i].img.ptr)
			mlx_destroy_image(c->mlx, c->tex[i].img.ptr);
	if (c->win)
		mlx_destroy_window(c->mlx, c->win);
	free_map(c->raw_lines);
	exit(status);
}
