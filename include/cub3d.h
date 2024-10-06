/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:39:37 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/06 23:33:44 by rgallien         ###   ########.fr       */
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

#define FOV	60
#define PI	3.14159265359
#define S_W 1024
#define S_H 512

#define MM_S_X 250
#define MM_S_Y 250
#define MM_TILE_X (MM_S_X / 5)
#define MM_TILE_Y (MM_S_Y / 5)

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
	double ray_cos;
	double ray_sin;
	float wall_h;
	int w_half;
	int h_half;
	float x;
	float y;
	float inc_angle;
	float precision;
}				t_ray;

typedef struct s_player
{
	float pos_x;
	float pos_y;
	float angle;
	float fov_half;
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
	t_ray		*ray;
	// t_map		info;
}			t_game;

// init
void	init_player(t_player *player, char **map);
void	init_ray(t_ray *ray);
void	init_game(t_game *game, t_player *player, t_ray *ray, char **map);

// events
int		on_keypress(int keysym, t_game *game);

// raycasting
int		game_loop(t_game *game);
void minimap(t_game *game);

// utils
double	to_radiant(unsigned long	number);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif
