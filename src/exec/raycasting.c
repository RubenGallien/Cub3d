/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:12:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/07 20:53:52 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_game *game, int start_x, int start_y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
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
	while (i < MM_TILE_Y - (game->player->pos_y % 50))
	{
		j = 0;
		while (j < MM_TILE_X - (game->player->pos_x % 50))
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

	y = 0;
	while (y < MM_S_X)
	{
		x = 0;
		while (x < MM_S_Y)
		{
			// printf("start_x = %d, start_y = %d\n", start_x, start_y);
			// printf("x = %d, y = %d\n", x, y);
			// printf("x: %d\n", (start_x + x) / 50);
			// printf("y: %d\n", (start_y + y) / 50);
			if ((start_y + y) / 50 < 0 || (start_x + x) / 50 < 0 || (start_y + y) / 50 > game->y - 1 || (start_x + x) / 50 > game->x - 1)
				my_mlx_pixel_put(&game->world, (S_W - MM_S_X) + x, y, 0xA9A9A9);
			else if ((start_x + x) % 50 == 0 || (start_y + y) % 50 == 0)
				my_mlx_pixel_put(&game->world, (S_W - MM_S_X) + x, y, 0x000000);
			else if (game->map[(start_y + y) / 50][(start_x + x) / 50] == '1')
				my_mlx_pixel_put(&game->world, (S_W - MM_S_X) + x, y, 0x0000FF);
			else if (game->map[(start_y + y) / 50][(start_x + x) / 50] == '0' || game->map[(start_y + y) / 50][(start_x + x) / 50] == 'P')
				my_mlx_pixel_put(&game->world, (S_W - MM_S_X) + x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}

}

void minimap(t_game *game)
{
	int	start_x;
	int	start_y;

	start_x = (game->player->pos_x) - 120;
	start_y = (game->player->pos_y) - 120;
	draw_minimap(game, start_x, start_y);
	draw_player(game, (S_W - MM_S_X) + (MM_S_X / 2) - 5, (MM_S_Y / 2) - 5, 0xFF0000);
}

int	game_loop(t_game *game)
{
	double x;
	int		i;

	i = 0;
	x = 0.00;
	if (game->mlx_win)
	{
			move_player(game);
			minimap(game);
			mlx_put_image_to_window(game->mlx, game->mlx_win, game->world.img, 0, 0);
			while (i < 5000000)
			{
				x += sqrt(i);
				i++;
			}
	}
	return (x);
}
