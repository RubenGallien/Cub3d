/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:39:37 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/04 11:02:01 by rgallien         ###   ########.fr       */
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
#define S_W 480
#define S_H 360

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
	int pos_x;
	int pos_y;
	float angle;
	float fov_half;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	char		**map;
	t_player	*player;
	t_ray		*ray;
}			t_game;

// init
void	init_player(t_player *player, char **map);
void	init_ray(t_ray *ray);
void	init_game(t_game *game, t_player *player, t_ray *ray, char **map);

// events
int		on_keypress(int keysym, t_game *game);

// raycasting
int		game_loop(t_game *game);

// utils
double	to_radiant(unsigned long	number);

#endif
