/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:12:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/04 15:34:24 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void minimap(t_game *game)
{
	int	start_x;
	int	start_y;
	int end_y;

	start_y = 0;
	end_y = S_W / 4;
	printf("start_y = %d\n", start_y);
	printf("end = %d\n", end_y);
	while (start_y <= end_y)
	{
		start_x = S_W - (S_W / 4);
		while (start_x < S_W)
		{
			my_mlx_pixel_put(&game->world, start_x, start_y, 0x808080);
			start_x++;
		}
		start_y++;
	}
	printf("start_y at end = %d\n", start_y);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->world.img, 0, 0);

}

int	game_loop(t_game *game)
{
	float	ray_angle;
	int	count;
	int	wall;
	double	distance;

	ray_angle = game->player->angle - game->player->fov_half;
	if (game->mlx_win)
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
            	my_mlx_pixel_put(&game->world, count, y, 0xFF0000); // Red walls
			}
			ray_angle += game->ray->inc_angle;
		}
		minimap(game);
		mlx_put_image_to_window(game->mlx, game->mlx_win, game->world.img, 0, 0);
	}
	return (0);
}
