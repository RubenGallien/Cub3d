/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:13:17 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/12 17:40:09 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	up_and_down(t_game *game)
{
	if (game->player->up == 1 && game->map\
	[(int)game->player->pos_y / 64]\
	[(int)(game->player->pos_x + (5 * game->player->pdx)) / 64] != '1')
		game->player->pos_x += cos(to_radiant(game->player->angle)) * 4;
	if (game->player->up == 1 && game->map\
	[(int)(game->player->pos_y - (5 * game->player->pdy)) / 64]\
	[(int)game->player->pos_x / 64] != '1')
		game->player->pos_y -= sin(to_radiant(game->player->angle)) * 4;

	if (game->player->down == 1 && game->map\
	[(int)game->player->pos_y / 64] \
	[(int)(game->player->pos_x - 5 * game->player->pdx) / 64] != '1')
		game->player->pos_x -= cos(to_radiant(game->player->angle)) * 4;

	if (game->player->down == 1 && game->map\
	[(int)(game->player->pos_y + 5 * game->player->pdy) / 64]\
	[(int)game->player->pos_x / 64] != '1')
		game->player->pos_y += sin(to_radiant(game->player->angle)) * 4;
}

void	left_and_right(t_game *game)
{
	if (game->player->left == 1 && \
	game->map[(int)game->player->pos_y / 64][((int)(game->player->pos_x + \
	cos(to_radiant(game->player->angle + 90)) * 5) / 64)] != '1')
		game->player->pos_x += cos(to_radiant(game->player->angle + 90)) * 2;
	if (game->player->left == 1 && game->map[(int)(game->player->pos_y - \
	sin(to_radiant(game->player->angle + 90)) * 5) / 64] \
	[(int)game->player->pos_x / 64] != '1')
		game->player->pos_y -= sin(to_radiant(game->player->angle + 90)) * 2;
	if (game->player->right == 1 && game->map[(int)game->player->pos_y / 64] \
	[((int)(game->player->pos_x - \
	cos(to_radiant(game->player->angle + 90)) * 5) / 64)] != '1')
		game->player->pos_x -= cos(to_radiant(game->player->angle + 90)) * 2;
	if (game->player->right == 1 && game->map[(int)(game->player->pos_y + \
	sin(to_radiant(game->player->angle + 90)) * 5) / 64] \
	[(int)(game->player->pos_x / 64)] != '1')
		game->player->pos_y += sin(to_radiant(game->player->angle + 90)) * 2;
}

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
	up_and_down(game);
	left_and_right(game);
}

void	mouse_ctrl(t_game *game)
{
	int	delta;

	if (game->player->right_r == 1 || game->player->left_r == 1)
		return ;
	delta = game->mouse.x - 960;
	if (delta)
	{
		game->player->angle -= 180 * ((double)delta / 240);
		game->player->angle = (int)game->player->angle % 360;
		if (game->player->angle < 0)
			game->player->angle += 360;
		game->player->pdx = cos(to_radiant(game->player->angle));
		game->player->pdy = sin(to_radiant(game->player->angle));
	}
}
