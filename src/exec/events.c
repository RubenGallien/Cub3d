/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:13:17 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/21 14:14:34 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_game *game)
{
	if (game->player->up == 1 && game->map \
	[(int)game->player->pos_y / 64] \
	[(int)(game->player->pos_x + (5 * game->player->pdx)) / 64] != '1' && \
	game->map \
	[(int)game->player->pos_y / 64] \
	[(int)(game->player->pos_x + (5 * game->player->pdx)) / 64] != 'D')
		game->player->pos_x += cos(to_radiant(game->player->angle)) * 4;
	if (game->player->up == 1 && game->map \
	[(int)(game->player->pos_y - (5 * game->player->pdy)) / 64] \
	[(int)game->player->pos_x / 64] != '1' && \
	game->map \
	[(int)(game->player->pos_y - (5 * game->player->pdy)) / 64] \
	[(int)game->player->pos_x / 64] != 'D')
		game->player->pos_y -= sin(to_radiant(game->player->angle)) * 4;
}

void	move_down(t_game *game)
{
	if (game->player->down == 1 && game->map \
	[(int)game->player->pos_y / 64] \
	[(int)(game->player->pos_x - 5 * game->player->pdx) / 64] != '1' && \
	game->map \
	[(int)game->player->pos_y / 64] \
	[(int)(game->player->pos_x - 5 * game->player->pdx) / 64] != 'D')
		game->player->pos_x -= cos(to_radiant(game->player->angle)) * 4;
	if (game->player->down == 1 && game->map \
	[(int)(game->player->pos_y + 5 * game->player->pdy) / 64] \
	[(int)game->player->pos_x / 64] != '1' && \
	game->map \
	[(int)(game->player->pos_y + 5 * game->player->pdy) / 64] \
	[(int)game->player->pos_x / 64] != 'D')
		game->player->pos_y += sin(to_radiant(game->player->angle)) * 4;
}

void	move_left(t_game *game)
{
	if (game->player->left == 1 && game->map \
	[(int)game->player->pos_y / 64][((int)(game->player->pos_x + \
	cos(to_radiant(game->player->angle + 90)) * 5) / 64)] != '1' && \
	game->map[(int)game->player->pos_y / 64][((int)(game->player->pos_x + \
	cos(to_radiant(game->player->angle + 90)) * 5) / 64)] != 'D')
		game->player->pos_x += cos(to_radiant(game->player->angle + 90)) * 2;
	if (game->player->left == 1 && game->map[(int)(game->player->pos_y - \
	sin(to_radiant(game->player->angle + 90)) * 5) / 64] \
	[(int)game->player->pos_x / 64] != '1' && \
	game->map[(int)(game->player->pos_y - \
	sin(to_radiant(game->player->angle + 90)) * 5) / 64] \
	[(int)game->player->pos_x / 64] != 'D')
		game->player->pos_y -= sin(to_radiant(game->player->angle + 90)) * 2;
}

void	move_right(t_game *game)
{
	if (game->player->right == 1 && game->map \
	[(int)game->player->pos_y / 64][((int)(game->player->pos_x - \
	cos(to_radiant(game->player->angle + 90)) * 5) / 64)] != '1' && \
	game->map[(int)game->player->pos_y / 64] \
	[((int)(game->player->pos_x - \
	cos(to_radiant(game->player->angle + 90)) * 5) / 64)] != 'D')
		game->player->pos_x -= cos(to_radiant(game->player->angle + 90)) * 2;
	if (game->player->right == 1 && game->map[(int)(game->player->pos_y + \
	sin(to_radiant(game->player->angle + 90)) * 5) / 64] \
	[(int)(game->player->pos_x / 64)] != '1' && \
	game->map[(int)(game->player->pos_y + \
	sin(to_radiant(game->player->angle + 90)) * 5) / 64] \
	[(int)(game->player->pos_x / 64)] != 'D')
		game->player->pos_y += sin(to_radiant(game->player->angle + 90)) * 2;
}
