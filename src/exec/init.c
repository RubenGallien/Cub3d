/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:14:12 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/07 17:52:52 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game, t_player *player, t_ray *ray, char **map)
{
	int	i;
	int	j;

	game->map = map;
	i = 0;
	while (game->map && game->map[i])
	{
		j = 0;
		while (game->map && game->map[i][j])
			j++;
		game->x = j;
		i++;
	}
	game->y = i;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, S_W, S_H, "Welcome to Cub3D");
	game->player = player;
	game->ray = ray;
	game->world.img = mlx_new_image(game->mlx, S_W, S_H);
	game->world.pixels = (unsigned char *)mlx_get_data_addr\
	(game->world.img, &game->world.bits_per_pixel, \
	&game->world.line_length, &game->world.endian);
}

void	init_player(t_player *player, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map && map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] && map[i][j] == 'P')
			{
				player->pos_x = j * 50 + 20;
				player->pos_y = i * 50 + 20;
				player->left = 0;
				player->right = 0;
				player->down = 0;
				player->up = 0;
				return;
			}
		}
	}
}
