/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:41:10 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/17 00:30:00 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	load_tex(t_cub *c, t_tex *t, char *path)
{
	t->img.ptr = mlx_xpm_file_to_image(c->mlx, path, &t->img.w, &t->img.h);
	if (!t->img.ptr)
		return (false);
	t->img.addr = mlx_get_data_addr(t->img.ptr, &t->img.bpp,
			&t->img.line_len, &t->img.endian);
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
