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

	x_torch_start = S_W / 8;
	y_torch_start = S_H - (64 * 12);
	mlx_mouse_get_pos(game->mlx, game->mlx_win, &game->mouse.x, &game->mouse.y);
	if (!game->tick && game->mlx_win)
	{
		mouse_ctrl(game);
		move_player(game);
		mlx_mouse_move(game->mlx, game->mlx_win, S_W / 2, S_H / 2);
		fill_rays_infos(game);
		draw_gameplan(game);
		make_spider(game);
		minimap(game);
		if (game->torch)
			draw_torch(game, x_torch_start, y_torch_start);
		mlx_put_image_to_window(game->mlx, game->mlx_win, \
		game->world.img, 0, 0);
	}
	game->tick = (game->tick + 1) % (15000 / SPEED);
	return (0);
}
