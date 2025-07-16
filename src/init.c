/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:40:44 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/16 23:57:25 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	init_game(t_cub *cub, char *file)
{
	ft_bzero(cub, sizeof(*cub));
	if (!parse_file(cub, file))
		return (false);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (false);
	if (!load_textures(cub))
		return (false);
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3D");
	cub->frame.ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->frame.addr = mlx_get_data_addr(cub->frame.ptr,
			&cub->frame.bpp, &cub->frame.line_len, &cub->frame.endian);
	return (true);
}
