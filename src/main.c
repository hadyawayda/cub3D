/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:38:11 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/22 22:36:38 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	load_tex(t_cub *c, t_tex *t, char *path)
{
	t->img.ptr = mlx_xpm_file_to_image(c->mlx, path, &t->img.w, &t->img.h);
	if (!t->img.ptr)
		return (false);
	t->img.addr = mlx_get_data_addr(t->img.ptr, &t->img.bpp, &t->img.line_len,
			&t->img.endian);
	return (true);
}

bool	load_textures(t_cub *c)
{
	int		i;
	char	*path;

	i = -1;
	while (++i < 4)
	{
		path = (char *)c->tex[i].img.ptr;
		if (!load_tex(c, &c->tex[i], path))
			return (false);
		free(path);
	}
	return (true);
}

bool	initialize_assets(t_cub *cub)
{
	cub->mouse_prev_x = -1;
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (false);
	if (!load_textures(cub))
		return (false);
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3D");
	cub->frame.ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->frame.addr = mlx_get_data_addr(cub->frame.ptr, &cub->frame.bpp,
			&cub->frame.line_len, &cub->frame.endian);
	if (!setup_mouse(cub))
		return (false);
	return (true);
}

/*
** Zero out cub, set default colors, parse + validate.
** Returns true on success, or prints the appropriate
** error and returns false on failure.
*/
static bool	setup_and_validate(t_cub *cub, char *path)
{
	ft_bzero(cub, sizeof(*cub));
	cub->floor_col = -1;
	cub->ceil_col = -1;
	if (!parse_file(cub, path) || !map_validator(cub))
	{
		if (cub->err)
		{
			ft_putstr_fd("Error!\n", 2);
			ft_putendl_fd(cub->err, 2);
		}
		else
			ft_putendl_fd("Error!\nInvalid map file.", 2);
		return (cleanup_cub(cub), false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (ft_putendl_fd("Error\nUsage: ./cub3D <map.cub>", 2), 1);
	if (!is_cub_file(argv[1]))
		return (ft_putendl_fd("Error\nInvalid file type.", 2), 1);
	if (!setup_and_validate(&cub, argv[1]))
		return (1);
	if (!initialize_assets(&cub))
		return (1);
	mlx_loop_hook(cub.mlx, draw_frame, &cub);
	mlx_hook(cub.win, 2, 1L << 0, on_keydown, &cub);
	mlx_hook(cub.win, 3, 1L << 1, on_keyup, &cub);
	mlx_hook(cub.win, 6, 1L << 6, on_mouse_move, &cub);
	mlx_hook(cub.win, 17, 1L << 17, on_close, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
