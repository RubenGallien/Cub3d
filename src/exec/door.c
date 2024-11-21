/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:15:29 by lvicino           #+#    #+#             */
/*   Updated: 2024/11/21 14:43:13 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_door(t_game *game)
{
	if (game->map[(int)game->player->pos_y / 64][(int)(game->player->pos_x + \
	(5 * game->player->pdx)) / 64] == 'd' && game->map[(int)game->player->pos_y \
	/ 64][(int)game->player->pos_x / 64] != 'd')
		game->map[(int)game->player->pos_y / 64][(int)(game->player->pos_x + \
		(5 * game->player->pdx)) / 64] = 'D';
	if (game->map[(int)game->player->pos_y / 64][(int)(game->player->pos_x + \
	(5 * game->player->pdx)) / 64] == 'D' && game->map[(int)game->player->pos_y \
	/ 64][(int)game->player->pos_x / 64] != 'D')
		game->map[(int)game->player->pos_y / 64][(int)(game->player->pos_x + \
		(5 * game->player->pdx)) / 64] = 'd';
	return (0);
}