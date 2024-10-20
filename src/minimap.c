/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:18:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/19 03:31:34 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_lines(t_game *game)
{
	t_ray ray;
	int	i;

	i = 0;
	ray.ra = to_radiant(game->player->angle + 30.00);
	if (ray.ra < 0)
		ray.ra += 2 * PI;
	if (ray.ra > 2 * PI)
		ray.ra -= 2 * PI;
	ray.r = -1;
	ray.rx = 0;
	ray.ry = 0;
	ray.xo = 0;
	ray.yo = 0;
	while (++ray.r < 59)
	{
		// horizontal line
		printf("\nHorizontal : \n\n");
		ray.dof = 0;
		ray.atan = -1 / tan(ray.ra);
		printf("tan = %f\n", ray.atan);
		if (ray.ra < PI)
		{
			printf("up : \n");
			ray.ry = (((int)game->player->pos_y / 50) * 50) - 1;
			printf("ry = %f\n", ray.ry);
			ray.rx = (ray.ry - (int)game->player->pos_y) * ray.atan + (int)game->player->pos_x;
			printf("rx = %f\n", ray.rx);
			ray.yo = -50;
			printf("yo = %f\n", ray.yo);
			ray.xo = ray.yo * ray.atan;
			printf("xo = %f\n", ray.xo);
		}
		if (ray.ra > PI)
		{
			printf("down : \n");
			ray.ry = (((int)game->player->pos_y / 50) * 50) + 50;
			printf("ry = %f\n", ray.ry);
			ray.rx = (ray.ry - (int)game->player->pos_y) * ray.atan + (int)game->player->pos_x;
			printf("rx = %f\n", ray.rx);
			ray.yo = 50;
			printf("yo = %f\n", ray.yo);
			ray.xo = ray.yo * ray.atan;
			printf("xo = %f\n", ray.xo);
		}
		if (ray.ra == 0 || ray.ra == PI)
		{
			ray.rx = (int)game->player->pos_x;
			ray.ry = (int)game->player->pos_y;
			ray.dof = MM_SIZE;
		}
		while (ray.dof < MM_SIZE)
		{
			i++;
			ray.mx = ray.rx / 50;
			ray.my = ray.ry / 50;
			if (ray.mx >= 0 && ray.my >= 0 && ray.mx < 10 && ray.my < 10 && game->map[ray.my][ray.mx] == '1')
				ray.dof = MM_SIZE;
			else
			{
				ray.rx += ray.xo;
				ray.ry += ray.yo;
				ray.dof += 1;
			}
		}
		int	distance;
		distance = found_distance((int)game->player->pos_x, (int)game->player->pos_y, ray.rx, ray.ry);
		// vertical lines
		printf("\nVertical : \n\n");
		ray.dof = 0;
		ray.ntan = -tan(ray.ra);
		if (ray.ra > P2 && ray.ra < P3)
		{
			printf("left : \n");
			ray.rx = (((int)game->player->pos_x / 50) * 50) - 1;
			printf("rx = %f\n", ray.rx);
			ray.ry = (ray.rx - (int)game->player->pos_x) * ray.ntan + (int)game->player->pos_y;
			printf("ry = %f\n", ray.ry);
			ray.xo = -50;
			printf("xo = %f\n", ray.xo);
			ray.yo = ray.xo * ray.ntan;
			printf("yo = %f\n", ray.yo);
		}
		if (ray.ra < P2 || ray.ra > P3)
		{
			printf("right : \n");
			ray.rx = (((int)game->player->pos_x / 50) * 50) + 50;
			printf("rx = %f\n", ray.rx);
			ray.ry = (ray.rx - (int)game->player->pos_x) * ray.ntan + (int)game->player->pos_y;
			printf("ry = %f\n", ray.ry);
			ray.xo = 50;
			printf("xo = %f\n", ray.xo);
			ray.yo = ray.xo * ray.ntan;
			printf("yo = %f\n", ray.yo);
		}
		if (ray.ra == 0 || ray.ra == PI)
		{
			ray.rx = (int)game->player->pos_x;
			ray.ry = (int)game->player->pos_y;
			ray.dof = MM_SIZE;
		}
		while (ray.dof < MM_SIZE)
		{
			i++;
			ray.mx = ray.rx / 50;
			ray.my = ray.ry / 50;
			if (ray.mx >= 0 && ray.my >= 0 && ray.mx < 10 && ray.my < 10 && game->map[ray.my][ray.mx] == '1')
				ray.dof = MM_SIZE;
			else
			{
				ray.rx += ray.xo;
				ray.ry += ray.yo;
				ray.dof += 1;
			}
		}
		int	distance2;
		distance2 = found_distance((int)game->player->pos_x, (int)game->player->pos_y, ray.rx, ray.ry);
		printf("distance h = %d\n", distance);
		printf("distance v = %d\n", distance2);
		int	f_dist;
		if (distance <= distance2)
			f_dist = distance;
		else
			f_dist = distance2;
		printf("d_dist = %d\n", f_dist);
		printf("%f\n", game->player->angle);
		printf("%f\n", ray.ra);
		int	u = -1;
		int start_x = (S_W - MM_S_X) + (MM_S_X / 2) - MM_SIZE;
		int start_y = (MM_S_Y / 2) - MM_SIZE;
		double xx = cos(ray.ra);
		double yy = sin(ray.ra);
		while (++u < f_dist && u < 124)
			my_mlx_pixel_put(&game->world, (start_x + 5 + (u * xx)), start_y + 5 - (u * yy), 0x00FF00);
		ray.ra -= ONE_DEGREE;
	}
}

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
