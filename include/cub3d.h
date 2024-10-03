/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:39:37 by rgallien          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/30 18:14:56 by rgallien         ###   ########.fr       */
=======
/*   Updated: 2024/10/02 14:58:34 by lvicino          ###   ########.fr       */
>>>>>>> origin/lvicino
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
typedef struct s_rcast
{
	int i;
}				t_rcast;

typedef struct s_player
{
	int pos_x;
	int pos_y;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	char		**map;
	t_player	*player;
}			t_game;

// init
void	init_player(t_player *player, char **map);

// events
int		on_keypress(int keysym, t_game *game);

// raycasting
int		game_loop(t_game *game);

#endif
