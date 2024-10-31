/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:12:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/14 13:23:53 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_game *game)
{
	int	y_torch_start;
	int	x_torch_start;

	x_torch_start = S_W / 4;
	y_torch_start = S_H - (64 * 8);
	if (game->mlx_win)
	{
		move_player(game);
		fill_rays_infos(game);
		draw_gameplan(game);
		if (game->torch)
			apply_darker(game);
		minimap(game);
		draw_torch(game, x_torch_start, y_torch_start);
		printf("PDX: %f, PDY: %f, Angle: %f\n", game->player->pdx, game->player->pdy, game->player->angle);
		mlx_put_image_to_window(game->mlx, game->mlx_win, game->world.img, 0, 0);
	}
	// game->tick = (game->tick + 1) % ((150000 / 2) / SPEED);
	return (0);
}
