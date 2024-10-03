/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:12:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/04 00:56:36 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_game *game)
{
	static int end_loop = 0;
	float	ray_angle;
	int	count;
	int	wall;
	double	distance;

	ray_angle = game->player->angle - game->player->fov_half;
	if (game->mlx_win && end_loop == 0)
	{
		count = 0;
		while (count < S_W)
		{
			wall = 0;
			game->ray->x = game->player->pos_x;
			game->ray->y = game->player->pos_y;
			game->ray->ray_cos = cos(to_radiant(ray_angle)) / game->ray->precision;
			game->ray->ray_sin = sin(to_radiant(ray_angle)) / game->ray->precision;
			while (wall == 0)
			{
				game->ray->x += game->ray->ray_cos;
				game->ray->y += game->ray->ray_sin;
				if ((int)floor(game->ray->x) < 12 && game->map[(int)floor(game->ray->y)][(int)floor(game->ray->x)] == '1')
				{
					// printf("count = %d\nx = %f, y = %f\n",count, game->ray->x, game->ray->y);
					wall = 1;
				}
			}
			distance = sqrt(pow(game->player->pos_x - game->ray->x, 2) + pow(game->player->pos_y - game->ray->y, 2));
			distance = distance * cos(to_radiant(ray_angle - game->player->angle));
			game->ray->wall_h = floor(game->ray->h_half / distance);
			count++;
			int drawStart = game->ray->h_half - game->ray->wall_h / 2;
        	int drawEnd = game->ray->h_half + game->ray->wall_h / 2;
			if (drawStart < 0)
				drawStart = 0;
        	if (drawEnd >= S_H)
				drawEnd = S_H - 1;
			for (int y = drawStart; y < drawEnd; y++) {
            	mlx_pixel_put(game->mlx, game->mlx_win, count, y, 0xFF0000); // Red walls
			}
			ray_angle += game->ray->inc_angle;
		}
		end_loop++;
	}
	return (0);
}
