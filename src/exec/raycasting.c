/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:12:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/06 23:46:42 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_game *game, int start_x, int start_y, int color)
{
	int	i;
	int	j;
	int	save;

	i = 0;
	save = color;
	while (i < MM_TILE_Y)
	{
		j = 0;
		while (j < MM_TILE_X)
		{
			if (i == 0 || j == 0)
				color = 0x000000;
			else
				color = save;
			my_mlx_pixel_put(&game->world, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
}

void minimap(t_game *game)
{
	int	start_x;
	int	start_y;
	int	map_x;
	int	map_y;
	int	i;
	int	j;

	printf("(%f,%f)\n", game->player->pos_x, game->player->pos_y);
	start_x = game->player->pos_x - 2;
	start_y = game->player->pos_y - 2;

	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;

	if (start_x > 5)
		start_x = 5;
	if (start_y > 5)
		start_y = 5;
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			map_x = start_x + j;
			map_y = start_y + i;
			if (game->map[map_y][map_x] == '1')
				draw_wall(game, S_W - (MM_S_X) + (j * MM_TILE_X), i * MM_TILE_Y, 0x0000FF);
			else if (game->map[map_y][map_x] == 'P')
			{
				draw_wall(game, S_W - (MM_S_X) + (j * MM_TILE_X), i * MM_TILE_Y, 0xFFFF00);
			}
			else
				draw_wall(game, S_W - (MM_S_X) + (j * MM_TILE_X), i * MM_TILE_Y, 0x808080);
			j++;
		}
		i++;
	}
}

int	game_loop(t_game *game)
{
	if (game->mlx_win)
	{
		minimap(game);
		mlx_put_image_to_window(game->mlx, game->mlx_win, game->world.img, 0, 0);
	}
	return (0);
}
