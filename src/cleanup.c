/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:41:47 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/28 16:27:17 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Frees the map grid and all its lines.
 * This is used to free the map after parsing or when cleaning up.
 */
void	free_map(char **map)
{
	size_t	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

/*
 * Frees everything allocated during parsing:
 *   - the raw_lines[] from ft_split()
 *   - if MLX isn’t up yet, the strdup’d texture paths
 */
static void	free_parser_resources(t_cub *cub)
{
	int	i;

	i = 0;
	if (cub->raw_lines)
	{
		free_map(cub->raw_lines);
		cub->raw_lines = NULL;
	}
	if (!cub->mlx)
	{
		while (i < 4)
		{
			if (cub->tex[i].img.ptr)
			{
				free(cub->tex[i].img.ptr);
				cub->tex[i].img.ptr = NULL;
			}
			i++;
		}
	}
}

/*
 * Tears down all the MLX resources:
 *   - destroy each texture image
 *   - destroy frame image
 *   - destroy window
 *   - destroy display + free(cub->mlx)
 */
static void	free_mlx_resources(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->tex[i].img.ptr)
		{
			mlx_destroy_image(cub->mlx, cub->tex[i].img.ptr);
			cub->tex[i].img.ptr = NULL;
		}
		i++;
	}
	if (cub->frame.ptr)
	{
		mlx_destroy_image(cub->mlx, cub->frame.ptr);
		cub->frame.ptr = NULL;
	}
	if (cub->win)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		cub->win = NULL;
	}
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	cub->mlx = NULL;
}

/*
 * Main entrypoint: always free parser resources;
 * then, if MLX was initialized, free the MLX ones too.
 */
void	cleanup_cub(t_cub *cub)
{
	free_parser_resources(cub);
	if (cub->mlx)
		free_mlx_resources(cub);
}

/*
 * Free all resources and exit with a message.
 * If msg is NULL, it just exits with the status code.
 */
void	free_and_exit(t_cub *cub, int status, char *msg)
{
	t_door	*tmp;
	int		i;

	while (cub->doors)
	{
		tmp = cub->doors->next;
		free(cub->doors);
		cub->doors = tmp;
	}
	if (msg)
		ft_putendl_fd(msg, 2);
	cleanup_cub(cub);
	exit(status);
}
