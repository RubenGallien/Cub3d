/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:50:25 by lvicino           #+#    #+#             */
/*   Updated: 2024/11/29 15:45:39 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game)
{
	if (game->player->left_r == 1)
		game->player->angle += 2;
	else if (game->player->right_r == 1)
		game->player->angle -= 2;
	if (game->player->right_r == 1 || game->player->left_r == 1)
	{
		game->player->angle = (int)game->player->angle % 360;
		if (game->player->angle < 0)
			game->player->angle += 360;
		game->player->pdx = cos(to_radiant(game->player->angle));
		game->player->pdy = sin(to_radiant(game->player->angle));
	}
	move_up(game);
	move_down(game);
	move_left(game);
	move_right(game);
}

int	mouse_ctrl(int x, int y, t_game *game)
{
	int	delta;

	(void)y;
	if (!game->lock)
		return (0);
	if (game->player->right_r == 1 || game->player->left_r == 1)
		return (0);
	delta = x - 960;
	if (delta)
	{
		game->player->angle -= delta / 8;
		game->player->angle = (int)game->player->angle % 360;
		if (game->player->angle < 0)
			game->player->angle += 360;
		game->player->pdx = cos(to_radiant(game->player->angle));
		game->player->pdy = sin(to_radiant(game->player->angle));
	}
	return (0);
}
