/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:39:37 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/21 17:44:32 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"

# include "parsing.h"

# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>

# include <time.h>
# include <sys/time.h>
# include <math.h>
# include <string.h>

#define EPSILON 0.0001
#define ONE_DEGREE 0.0174533
#define FOV	60
#define SPEED 100
#define PI	3.14159265359
#define P2	(PI / 2)
#define P3	(3 * PI / 2)
#define S_W 1920
#define S_H 1080

#define MM_S_X 250
#define MM_S_Y 250
#define MM_SIZE 5
#define MM_TILE_X (MM_S_X / MM_SIZE)
#define MM_TILE_Y (MM_S_Y / MM_SIZE)

#define SIZE_P_X (MM_TILE_X / 5)
#define SIZE_P_Y (MM_TILE_Y / 5)

typedef struct s_img
{
	void				*img;
	unsigned char		*pixels;
	int					line_length;
	int					bits_per_pixel;
	int					endian;
	int					height;
	int					width;
}						t_img;

typedef struct s_ray
{
	int	r;
	int	mx;
	int	my;
	int	mp;
	int	dof;
	double	atan;
	double	ntan;
	double	rx;
	double	ry;
	double	ra;
	double	xo;
	double	yo;
}				t_ray;

typedef struct s_player
{
	double	pdx;
	double	pdy;
	double pos_x;
	double pos_y;
	double angle;
	char pos;
	int left;
	int	left_r;
	int up;
	int down;
	int right;
	int	right_r;
}				t_player;

typedef struct s_game
{
	int			x;
	int			y;
	void		*mlx;
	void		*mlx_win;
	char		**map;
	t_img		world;
	t_player	*player;
	// t_ray		ray[FOV];
	// t_map		info;
}			t_game;

// init
void		init_player(t_player *player, char **map);
void		init_ray(t_ray *ray);
void		init_game(t_game *game, t_player *player, char **map);

// events
int			on_keypress(int keysym, t_game *game);
int			on_keyrelease(int keysym, t_game *game);
void		move_player(t_game *game);

// raycasting
int			game_loop(t_game *game);
void		draw_lines(t_game *game);

// utils
double		to_radiant(double	number);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
int	found_distance(int x1, int y1, int x2, int y2);

// minimap
void 		minimap(t_game *game);

#endif
