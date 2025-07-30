/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:02:33 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 11:18:19 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

# define VALID_CHARS " 01NSEWDT"
# define DOOR_CLOSED 'D'
# define DOOR_OPEN '0'
# define SPRITE_CHAR 'T'
# define WIDTH 1920
# define HEIGHT 1080
// Unused variable collision_radius
# define COLLISION_RADIUS 1000
# define MINIMAP_SCALE 12
# define SPRITE_FRAMES 4
# define SPRITE_DURATION 0.2
# define DOOR_MM_COL 0x006600
# define KEY_E 101
# define SPRITE_FPS 8
# define MAX_SPR_FR 16
/* Linux parameters*/
# define MOVE_SPEED 0.03
# define ROT_SPEED 0.025
# define MOUSE_SENS 0.001
/* Windows parameters*/
// # define MOVE_SPEED 0.1
// # define ROT_SPEED 0.07
// # define MOUSE_SENS 0.0001

typedef struct s_door
{
	int				x;
	int				y;
	bool			open;
	struct s_door	*next;
}					t_door;

typedef struct s_vec
{
	double			x;
	double			y;
}					t_vec;

typedef struct s_img
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				w;
	int				h;
}					t_img;

typedef struct s_sprite_tex
{
	t_img			frame[MAX_SPR_FR];
	int				count;
}					t_sprite_tex;

typedef struct s_sprite
{
	double			x;
	double			y;
	int				frame_idx;
	struct s_sprite	*next;
}					t_sprite;

typedef struct s_keys
{
	bool			w;
	bool			s;
	bool			a;
	bool			d;
	bool			l;
	bool			r;
}					t_keys;

typedef struct s_tex
{
	t_img			img;
}					t_tex;

typedef struct s_player
{
	t_vec			pos;
	t_vec			dir;
	t_vec			plane;
}					t_player;

typedef struct s_map
{
	char			**grid;
	int				w;
	int				h;
}					t_map;

typedef struct s_cub
{
	char			**raw_lines;
	char			*err;
	void			*mlx;
	void			*win;
	int				floor_col;
	int				ceil_col;
	int				mouse_prev_x;
	int				sprite_count;
	t_door			*doors;
	t_img			frame;
	t_tex			tex[4];
	t_player		pl;
	t_map			map;
	t_keys			k;
	t_sprite_tex	spr;
	t_sprite		*sprites;
	double			spr_time;
	double			zbuf[WIDTH];
}					t_cub;

typedef struct s_elem_ctx
{
	t_cub	*c;
	char	**lines;
	int		*i;
	bool	*floor_seen;
	bool	*ceil_seen;
}	t_elem_ctx;

typedef struct s_sprite_segment
{
	t_img	*tex;
	int		size;
	int		y0;
	int		y1;
	int		scr_x;
	double	ty;
}				t_sprite_segment;

typedef struct s_dda
{
	t_vec			ray;
	t_vec			delta;
	t_vec			step;
	t_vec			side;
	int				map_x;
	int				map_y;
	int				side_hit;
	double			perp_dist;
	int				line_h;
	int				draw_s;
	int				draw_e;
	int				tex_id;
	int				tex_x;
}					t_dda;

bool				load_textures(t_cub *cub);
bool				parse_file(t_cub *cub, char *path);
bool				valid_cell(char ch);
bool				map_validator(t_cub *cub);
bool				check_required_elements(t_cub *c);
bool				is_cub_file(const char *path);
bool				has_xpm_ext(char *s);
bool				set_player(t_cub *c, int x, int y, char ch);
bool				handle_color_line(t_cub *c, char *line, bool *floor_seen,
						bool *ceil_seen);
bool				setup_mouse(t_cub *c);
bool				door_add(t_cub *c, int x, int y);
bool				cell_is_blocked(t_cub *c, int x, int y);
bool				parse_sprite_line(t_cub *c, char *line);
bool				sprite_add(t_cub *c, int x, int y);
bool				load_sprite_frames(t_cub *c);
bool				parse_wall_texture(t_cub *c, char *line, int *out_id);
bool				process_map_row(t_cub *c, char *row, int y);
bool				parse_colors(t_cub *c, char **lines, int *i);
bool				sprite_transform(t_cub *c, t_sprite *s, double *tx,
						double *ty);

char				*ft_file_to_str(char *path);

int					draw_frame(t_cub *cub);
int					on_keydown(int key, t_cub *cub);
int					on_close(t_cub *cub);
int					on_keydown(int key, t_cub *c);
int					on_keyup(int key, t_cub *c);
int					on_mouse_move(int x, int y, t_cub *c);
int					ft_min(int a, int b);

long				get_time_ms(void);

void				cast_column(t_cub *cub, int x);
void				free_and_exit(t_cub *cub, int status, char *msg);
void				init_dda(t_cub *c, t_dda *d, int x);
void				free_map(char **arr);
void				fill_spaces_with_walls(char **grid, int h, int w);
void				skip_empty_lines(char **lines, int *i);
void				move_player(t_cub *c, t_vec step);
void				rotate(t_player *p, double a);
void				cleanup_cub(t_cub *cub);
void				draw_minimap(t_cub *c);
void				door_toggle(t_cub *c);
void				draw_mm_open(t_cub *c, int gx, int gy);
void				draw_mm_closed(t_cub *c, int gx, int gy);
void				put_pixel(t_cub *c, int x, int y, int color);
void				draw_square(t_cub *c, int cx, int cy, int color);
void				sprite_tick(t_cub *c);
void				draw_sprites(t_cub *c);
void				compute_draw_limits(t_dda *d);
void				compute_texture_mapping(t_cub *c, t_dda *d);
void				draw_one_sprite(t_cub *c, t_sprite *s);

#endif
