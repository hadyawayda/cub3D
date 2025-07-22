/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:02:33 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/22 22:42:50 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1920
# define HEIGHT 1080
# define MOVE_SPEED 0.03
# define ROT_SPEED 0.025
# define MOUSE_SENS 0.001
# define MOUSE_CX (WIDTH / 2)
# define MOUSE_CY (HEIGHT / 2)

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_vec
{
	double		x;
	double		y;
}				t_vec;

/* cub3d.h */

typedef struct s_keys
{
	bool		w;
	bool		s;
	bool		a;
	bool		d;
	bool		l;
	bool		r;
}				t_keys;

// typedef struct s_cub
// {
// 	/* …existing fields… */
// 	t_keys	keys;
// }	t_cub;

typedef struct s_img
{
	void		*ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			w;
	int			h;
}				t_img;

typedef struct s_tex
{
	t_img		img;
}				t_tex;

typedef struct s_player
{
	t_vec		pos;
	t_vec		dir;
	t_vec		plane;
}				t_player;

typedef struct s_map
{
	char		**grid;
	int			w;
	int			h;
}				t_map;

typedef struct s_cub
{
	char		**raw_lines;
	char		*err;
	void		*mlx;
	void		*win;
	int			floor_col;
	int			ceil_col;
	int			mouse_prev_x;
	t_img		frame;
	t_tex		tex[4];
	t_player	pl;
	t_map		map;
	t_keys		k;
}				t_cub;

typedef struct s_dda
{
	t_vec		ray;
	t_vec		delta;
	t_vec		step;
	t_vec		side;
	int			map_x;
	int			map_y;
	int			side_hit;
	double		perp_dist;
	int			line_h;
	int			draw_s;
	int			draw_e;
	int			tex_id;
	int			tex_x;
}				t_dda;

bool			load_textures(t_cub *cub);
bool			parse_file(t_cub *cub, char *path);
bool			valid_cell(char ch);
bool			map_validator(t_cub *cub);
bool			check_required_elements(t_cub *c);
bool			is_cub_file(const char *path);
bool			parse_textures(t_cub *c, char **lines, int *i);
bool			has_xpm_ext(char *s);
bool			set_player(t_cub *c, int x, int y, char ch);
bool			handle_color_line(t_cub *c, char *line, bool *floor_seen,
					bool *ceil_seen);
bool			setup_mouse(t_cub *c);

char			*ft_file_to_str(char *path);

int				draw_frame(t_cub *cub);
int				on_keydown(int key, t_cub *cub);
int				on_close(t_cub *cub);
int				on_keydown(int key, t_cub *c);
int				on_keyup(int key, t_cub *c);
int				on_mouse_move(int x, int y, t_cub *c);

void			cast_column(t_cub *cub, int x);
void			free_and_exit(t_cub *cub, int status, char *msg);
void			init_dda(t_cub *c, t_dda *d, int x);
void			perform_dda(t_cub *c, t_dda *d);
void			draw_column(t_cub *c, t_dda *d, int x);
void			free_map(char **arr);
void			fill_spaces_with_walls(char **grid, int h, int w);
void			skip_empty_lines(char **lines, int *i);
void			move_player(t_cub *c, t_vec step);
void			rotate(t_player *p, double a);

#endif
