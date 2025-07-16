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
	void		*mlx;
	void		*win;
	t_img		frame;
	t_tex		tex[4];
	int			floor_col;
	int			ceil_col;
	t_player	pl;
	t_map		map;
}	t_cub;

bool	init_game(t_cub *cub, char *file);
bool	load_textures(t_cub *cub);
bool	parse_file(t_cub *cub, char *path);
bool	valid_cell(char ch);

char	*ft_file_to_str(char *path);

int		draw_frame(t_cub *cub);
int		on_keydown(int key, t_cub *cub);
int		on_close(t_cub *cub);

void	ft_split_free(char **arr);
void	cast_column(t_cub *cub, int x);
void	free_and_exit(t_cub *cub, int status, char *msg);

#endif
