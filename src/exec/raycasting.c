/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:12:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/11 16:51:43 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	raycasting(t_game *game)
// {

// }

int	game_loop(t_game *game)
{
	double x;
	int		i;

	i = 0;
	x = 0.00;
	if (game->mlx_win)
	{
			move_player(game);
			// raycasting(game);
			minimap(game);
			mlx_put_image_to_window(game->mlx, game->mlx_win, game->world.img, 0, 0);
			while (i < 8000000)
			{
				x += sqrt(i);
				i++;
			}
	}
	return (x);
}
