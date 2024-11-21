/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:15:29 by lvicino           #+#    #+#             */
/*   Updated: 2024/11/21 16:23:43 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_door(t_game *game)
{
	int	i;

	i = 0;
	while (++i <= 100)
	{
		if (game->map \
		[(int)(game->player->pos_y - (i * game->player->pdy)) / 64] \
		[(int)(game->player->pos_x + (i * game->player->pdx)) / 64] == 'd')
		{
			game->map \
			[(int)(game->player->pos_y - (i * game->player->pdy)) / 64] \
			[(int)(game->player->pos_x + (i * game->player->pdx)) / 64] = 'D';
			return (0);
		}
		else if (game->map \
		[(int)(game->player->pos_y - (i * game->player->pdy)) / 64] \
		[(int)(game->player->pos_x + (i * game->player->pdx)) / 64] == 'D')
		{
			game->map \
			[(int)(game->player->pos_y - (i * game->player->pdy)) / 64] \
			[(int)(game->player->pos_x + (i * game->player->pdx)) / 64] = 'd';
			return (0);
		}
	}
	return (0);
}
