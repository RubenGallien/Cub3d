/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:39:37 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/19 12:06:10 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"

# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>

# include <stdio.h>
# include <time.h>
# include <sys/time.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>

# define WALL_SIZE 96
# define EPSILON 0.0001
# define ONE_DEGREE 0.0174533
# define FOV 60
# define SPEED 200
# define PI	3.14159265359
# define S_W 1920
# define S_H 1080
# define MM_S_X 320
# define MM_S_Y 320
# define MM_SIZE 5
# define RES 32

// assets
# define TORCH_ON "textures/utils/torch.xpm"
# define TORCH_OFF "textures/utils/torch_off.xpm"
# define FLOOR "textures/floor/deepslate.xpm"
# define CEILING "textures/ceiling/deepslate_top.xpm"
# define DOOR "textures/door/door.xpm"
# define SPIDER "textures/sprite/spider.xpm"

# include "parsing.h"

typedef struct s_minimap
{
	int	x;
	int	y;
	int	start_x;
	int	start_y;
	int	c_x;
	int	c_y;
	int	r;
}			t_minimap;

typedef struct s_spider
{
	double			x;
	double			y;
	double			hx;
	double			hy;
	double			distance;
	double			p;
	double			q;
	double			sp_screen_x;
	double			sp_screen_y;
	double			proj_sprite_h;
	double			proj_sprite_w;
	struct s_spider	*prev;
	struct s_spider	*next;
}				t_spider;

typedef struct s_rgb
{
	double	r;
	double	g;
	double	b;
}			t_rgb;

typedef struct s_img
{
	void			*img;
	unsigned char	*pixels;
	int				line_length;
	int				bits_per_pixel;
	int				endian;
	int				height;
	int				width;
}					t_img;

typedef struct s_asset
{
	t_img	wall[4];
	t_img	torch[2];
	t_img	ceiling;
	t_img	floor;
	t_img	door;
	t_img	spider;
}			t_asset;

typedef struct s_ray
{
	double					perc;
	unsigned int			color;
	int						mx;
	int						my;
	int						mp;
	int						dof;
	double					atan;
	double					ntan;
	double					rx;
	double					rx_tmp;
	double					ry;
	double					ra;
	double					xo;
	double					yo;
	double					distance_h;
	double					distance_v;
	double					wall_height;
	unsigned long			tmp;
	int						offset;
	double					off_y;
	double					ty_step;
	double					ty;
	double					tx;
	double					dy;
	int						f_wall;
	int						flag;
	double					proj;
	double					r;
	double					straight_line;
	double					beta;
	double					d;
	double					n;
}				t_ray;

typedef struct s_player
{
	double	pdx;
	double	pdy;
	double	pos_x;
	double	pos_y;
	int		angle;
	char	pos;
	int		left;
	int		left_r;
	int		up;
	int		down;
	int		right;
	int		right_r;
}				t_player;

typedef struct s_mouse
{
	int	x;
	int	y;
}		t_mouse;

typedef struct s_game
{
	int			x;
	int			y;
	void		*mlx;
	void		*mlx_win;
	char		**map;
	int			tick;
	int			torch;
	double		width_per_cell;
	double		proj;
	t_spider	*spider;
	t_asset		textures;
	t_img		world;
	t_player	*player;
	t_mouse		mouse;
	t_ray		ray[FOV * RES];
	t_map		info;
}			t_game;

// init
int			init_player(t_player *player, char **map);
void		init_game(t_game *game, t_player *player, char **map);
void		init_textures(t_game *game);
void		init_spider(t_game *game);
// events
int			on_keypress(int keysym, t_game *game);
int			on_keyrelease(int keysym, t_game *game);
void		move_player(t_game *game);
void		mouse_ctrl(t_game *game);
int			ft_exit(t_game *game);

// distance
void		choose_distance(t_game *game, int i);

// raycasting
int			game_loop(t_game *game);
void		draw_gameplan(t_game *game);
void		fill_rays_infos(t_game *game);
void		straight_dist(t_game *game, char sense, int i);
void		extra_h(t_game *game, int i);
void		extra_v(t_game *game, int i);
void		incr_pos(t_game *game, int b, double save_x, double save_y);
void		choose_textures(t_game *game, int i);
int			choose_color(t_ray *ray, t_game *game, int y);
int			choose_col_floor_ceiling(t_ray ray, t_img floor, int y, int torch);

// utils
double		to_radiant(double number);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
double		found_distance(double x1, double y1, double x2, double y2);
void		draw_torch(t_game *game, int x, int y);
void		apply_darker(t_game *game, int percentage);
void		normalize_angle(double *angle);
int			set_data_assets(t_game *game, char *_path, t_img *textures);

// minimap
void		minimap(t_game *game);

//convert
int			to_degrees(double number);

// spider
void		print_spider(t_game *game);
void		make_spider(t_game *game);
void		recup_spider_infos(t_spider *curr, t_game *game);
void	draw_spider(t_spider *curr, t_game *game, int start_x, int start_y);

#endif
