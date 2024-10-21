/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:18:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/21 14:59:43 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_game *game, int start_x, int start_y, int color)
{
	int	i;
	int	j;

	i = 0;
	for (int u = 0; u < 15; u++)
		my_mlx_pixel_put(&game->world, start_x+ (u * game->player->pdx), start_y - (u * game->player->pdy), 0xFF00FF);
	while (i < 1)
	{
		j = 0;
		while (j < 1)
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
	while (i < MM_TILE_Y - ((int)game->player->pos_y % MM_TILE_Y))
	{
		j = 0;
		while (j < MM_TILE_X - ((int)game->player->pos_x % MM_TILE_X))
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
	int	radius = 125; // Rayon du cercle

	// Coordonnées du centre du cercle
	int	center_x = MM_S_X / 2;
	int	center_y = MM_S_Y / 2;

	y = -1;
	while (++y < MM_S_Y) // Parcours des pixels en hauteur
	{
		x = -1;
		while (++x < MM_S_X) // Parcours des pixels en largeur
		{
			// Calcul de la distance au centre du cercle
			if ((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y) <= radius * radius)
			{
				// Vérification des limites de la map et dessin des pixels selon la logique des tuiles
				if (start_x + x < 0 || start_y + y < 0 || (start_y + y) / MM_TILE_Y < 0 || \
				(start_x + x) / MM_TILE_X < 0 || (start_y + y) / MM_TILE_Y > game->y - 1 || (start_x + x) / MM_TILE_X > game->x - 1 || !game->map[(start_y + y) / MM_TILE_Y][(start_x + x) / MM_TILE_X])
					my_mlx_pixel_put(&game->world, (S_W - MM_S_X) + x, y, 0x000000); // Hors limite ou mur
				else if ((start_x + x) % MM_TILE_X == 0 || (start_y + y) % MM_TILE_Y == 0)
					my_mlx_pixel_put(&game->world, (S_W - MM_S_X) + x, y, 0x000000); // Ligne de la grille
				else if (game->map[(start_y + y) / MM_TILE_Y][(start_x + x) / MM_TILE_X] == '1')
					my_mlx_pixel_put(&game->world, (S_W - MM_S_X) + x, y, 0x0000FF); // Mur
				else if (game->map[(start_y + y) / MM_TILE_Y][(start_x + x) / MM_TILE_X] == '0' \
				|| game->map[(start_y + y) / MM_TILE_Y][(start_x + x) / MM_TILE_X] == 'N' || \
				game->map[(start_y + y) / MM_TILE_Y][(start_x + x) / MM_TILE_X] == 'S' || \
				game->map[(start_y + y) / MM_TILE_Y][(start_x + x) / MM_TILE_X] == 'W' || \
				game->map[(start_y + y) / MM_TILE_Y][(start_x + x) / MM_TILE_X] == 'E')
					my_mlx_pixel_put(&game->world, (S_W - MM_S_X) + x, y, 0x9e9494); // Sol ou direction
			}
		}
	}
}

void minimap(t_game *game)
{
	int	start_x;
	int	start_y;

	start_x = (game->player->pos_x) - 125;
	start_y = (game->player->pos_y) - 125;
	draw_minimap(game, start_x, start_y);
	draw_lines(game);
	// draw_player(game, (S_W - MM_S_X) + ((MM_S_X / 2) - 5), ((MM_S_Y / 2) - 5), 0xFF0000);
	draw_player(game, (S_W - MM_S_X) + (MM_S_X / 2), (MM_S_Y / 2), 0xFF0000);
}
