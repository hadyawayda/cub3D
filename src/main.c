/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:38:11 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/16 19:38:11 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nUsage: ./cub3D <map.cub>", 2);
		return (1);
	}
	if (!init_game(&cub, argv[1]))
		return (1);
	mlx_loop_hook(cub.mlx, draw_frame, &cub);
	mlx_hook(cub.win, 2, 1L << 0, on_keydown, &cub);
	mlx_hook(cub.win, 17, 1L << 17, on_close, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
