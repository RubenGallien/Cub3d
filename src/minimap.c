/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:18:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/11 13:18:40 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_game *game, int start_x, int start_y, int color)
{
	int	i;
	int	j;

	i = 0;
	for (int z = 0; z < 2; z++)
	{
		for (int u = 0; u < 15; u++)
			my_mlx_pixel_put(&game->world, start_x + 5 + (u * game->player->pdx), start_y + 5 - (u * game->player->pdy), 0x00FF00);
	}
	while (i < SIZE_P_Y)
	{
		j = 0;
		while (j < SIZE_P_X)
		{
			my_mlx_pixel_put(&game->world, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}

}

void	draw_wall(t_game *game, int start_x, int start_y, int color)
{
	int	i;
	int	j;
	int	save;

	i = 0;
	save = color;
	while (i < MM_TILE_Y - (game->player->pos_y % MM_TILE_Y))
	{
		j = 0;
		while (j < MM_TILE_X - (game->player->pos_x % MM_TILE_X))
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

void	draw_minimap(t_game *game, int start_x, int start_y)
{
	int	y;
	int	x;

	y = -1;
	while (++y < MM_S_X)
	{
		x = -1;
		while (++x < MM_S_Y)
		{
			if (start_x + x < 0 || start_y + y < 0 || (start_y + y) / MM_TILE_Y < 0 || \
			(start_x + x) / MM_TILE_X < 0 || (start_y + y) / MM_TILE_Y > game->y - 1 || (start_x + x) / MM_TILE_X > game->x - 1 || !game->map[(start_y + y) / MM_TILE_Y][(start_x + x) / MM_TILE_X])
				my_mlx_pixel_put(&game->world, (S_W - MM_S_X) + x, y, 0x000000);
			else if ((start_x + x) % MM_TILE_X == 0 || (start_y + y) % MM_TILE_Y == 0)
				my_mlx_pixel_put(&game->world, (S_W - MM_S_X) + x, y, 0x000000);
			else if (game->map[(start_y + y) / MM_TILE_Y][(start_x + x) / MM_TILE_X] == '1')
				my_mlx_pixel_put(&game->world, (S_W - MM_S_X) + x, y, 0x0000FF);
			else if (game->map[(start_y + y) / MM_TILE_Y][(start_x + x) / MM_TILE_X] == '0' \
			|| game->map[(start_y + y) / MM_TILE_Y][(start_x + x) / MM_TILE_X] == 'N' || \
			game->map[(start_y + y) / MM_TILE_Y][(start_x + x) / MM_TILE_X] == 'S' || \
			game->map[(start_y + y) / MM_TILE_Y][(start_x + x) / MM_TILE_X] == 'W' || \
			game->map[(start_y + y) / MM_TILE_Y][(start_x + x) / MM_TILE_X] == 'E')
				my_mlx_pixel_put(&game->world, (S_W - MM_S_X) + x, y, 0x9e9494);
		}
	}
}

void minimap(t_game *game)
{
	int	start_x;
	int	start_y;

	start_x = (game->player->pos_x) - 120;
	start_y = (game->player->pos_y) - 120;
	draw_minimap(game, start_x, start_y);
	draw_player(game, (S_W - MM_S_X) + (MM_S_X / 2) - MM_SIZE, (MM_S_Y / 2) - MM_SIZE, 0xFF0000);
}
