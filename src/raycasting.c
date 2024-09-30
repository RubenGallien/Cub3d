/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:12:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/30 18:17:26 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_game *game)
{
	int	first_inter_y;
	int	first_inter_x;
	static int i = 0;

	if (game->mlx_win && i == 0)
	{
		// find first horizontal intersection
		printf("position de depart\n(%d, %d)\n", game->player->pos_x, game->player->pos_y);
		mlx_pixel_put(game->mlx, game->mlx_win, 640, 360, 0xFF0000);
		first_inter_y = (floor(game->player->pos_y / 64) * (64) - 1);
		first_inter_x = game->player->pos_x + ((game->player->pos_y - first_inter_y) / tan(FOV * PI / 180));
		i = 1;
	}
	return (0);
}