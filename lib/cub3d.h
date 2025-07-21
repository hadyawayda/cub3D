/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:02:33 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/21 10:33:13 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH  1280
# define HEIGHT  720

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include "../minilibx-linux/mlx.h"
# include "libft.h"

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_tex
{
	t_img	img;
}	t_tex;

typedef struct s_player
{
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		w;
	int		h;
}	t_map;

typedef struct s_cub
{
	char		**raw_lines;
	char		*err;
	void		*mlx;
	void		*win;
	t_img		frame;
	t_tex		tex[4];
	int			floor_col;
	int			ceil_col;
	t_player	pl;
	t_map		map;
}	t_cub;

typedef struct s_dda
{
	t_vec	ray;
	t_vec	delta;
	t_vec	step;
	t_vec	side;
	int		map_x;
	int		map_y;
	int		side_hit;
	double	perp_dist;
	int		line_h;
	int		draw_s;
	int		draw_e;
	int		tex_id;
	int		tex_x;
}	t_dda;

bool	load_textures(t_cub *cub);
bool	parse_file(t_cub *cub, char *path);
bool	valid_cell(char ch);
bool	map_validator(t_cub *cub);

char	*ft_file_to_str(char *path);

int		draw_frame(t_cub *cub);
int		on_keydown(int key, t_cub *cub);
int		on_close(t_cub *cub);

void	cast_column(t_cub *cub, int x);
void	free_and_exit(t_cub *cub, int status, char *msg);
void	init_dda(t_cub *c, t_dda *d, int x);
void	perform_dda(t_cub *c, t_dda *d);
void	draw_column(t_cub *c, t_dda *d, int x);
void	free_map(char **arr);

#endif
