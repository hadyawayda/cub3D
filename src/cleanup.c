/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:41:47 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/17 01:48:37 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_lines(char **arr)
{
	size_t i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
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
	free_lines(c->map.grid);
	exit(status);
}
