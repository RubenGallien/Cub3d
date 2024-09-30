/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:14:12 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/30 18:14:30 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player, char **map)
{
	int	i;
	int	j;
	int	pos_y;
	int	pos_x;

	pos_y = 32;
	i = -1;
	while (map && map[++i])
	{
		pos_x = 32;
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] && map[i][j] == 'P')
			{
				player->pos_x = pos_x;
				player->pos_y = pos_y;
				return;
			}
			pos_x = pos_x + 64;
		}
		pos_y = pos_y + 64;
	}
}