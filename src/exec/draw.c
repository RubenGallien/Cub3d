/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:07:16 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/05 03:21:19 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
void	draw_walls(double dist_t, int start, t_game *game, t_ray ray)
{
	int		x;
	int		y;

	x = 0;
	ray.wall_height = (WALL_SIZE * S_H) / dist_t;
	ray.off_y = 0.0;
	if (ray.wall_height > S_H)
	{
		ray.off_y = (ray.wall_height - S_H) / 2;
		ray.wall_height = S_H;
	}
	while (x < (int)game->width_per_cell)
	{
		y = 0;
		ray.ty_step = 64.0 / ((WALL_SIZE * S_H) / dist_t);
		ray.ty = ray.off_y * ray.ty_step;
		while (y < S_H)
		{
			if (y < (S_H - (int)ray.wall_height) / 2)
				my_mlx_pixel_put(&game->world, x + start, y, \
				game->info.colour[1]);
			else if (y >= (S_H - (S_H - (int)ray.wall_height) / 2))
				my_mlx_pixel_put(&game->world, x + start, y, \
				game->info.colour[0]);
			else
				my_mlx_pixel_put(&game->world, x + start, y, \
				choose_color(ray, game->textures.wall[ray.f_wall], \
				y - ((S_H - (int)ray.wall_height) / 2)));
			y++;
			ray.ty += ray.ty_step;
		}
		x++;
	}
}
*/

void	draw_ceiling(double dist_t, int start, t_game *game, t_ray ray)
{
	int		x;
	int		y;

	ray.wall_height = (WALL_SIZE * S_H) / dist_t;
	if (ray.wall_height > S_H)
		ray.wall_height = S_H;
	x = -1;
	while (++x < (int)game->width_per_cell)
	{
		y = -1;
		while (++y < S_H)
		{
			if (y < (S_H - (int)ray.wall_height) / 2)
				my_mlx_pixel_put(&game->world, x + start, \
				y, game->info.colour[1]);
		}
	}
}

void	draw_floor(double dist_t, int start, t_game *game, t_ray ray)
{
	int		x;
	int		y;

	ray.wall_height = (WALL_SIZE * S_H) / dist_t;
	if (ray.wall_height > S_H)
		ray.wall_height = S_H;
	x = -1;
	while (++x < (int)game->width_per_cell)
	{
		y = -1;
		while (++y < S_H)
		{
			// ray.dy = y - (S_H / 2.0);
			if (y >= (S_H - (S_H - (int)ray.wall_height) / 2))
			{
				// ray.tx = game->player->pos_x / 2 + cos(game->ray->ra) * dist_t * 64 / ray.dy;
				// ray.ty = game->player->pos_y / 2 - sin(game->ray->ra) * dist_t * 64 / ray.dy;
				my_mlx_pixel_put(&game->world, x + start, y, game->info.colour[0]);

			}
		}
	}
}

void	draw_wall_aux(double dist_t, t_ray *ray)
{
	ray->wall_height = (WALL_SIZE * S_H) / dist_t;
	ray->off_y = 0.0;
	if (ray->wall_height > S_H)
	{
		ray->off_y = (ray->wall_height - S_H) / 2;
		ray->wall_height = S_H;
	}
}

void	draw_wall(double dist_t, int start, t_game *game, t_ray ray)
{
	int		x;
	int		y;

	draw_wall_aux(dist_t, &ray);
	x = -1;
	while (++x < (int)game->width_per_cell)
	{
		ray.ty_step = 64.0 / ((WALL_SIZE * S_H) / dist_t);
		ray.ty = ray.off_y * ray.ty_step;
		y = -1;
		while (++y < S_H)
		{
			if (y >= (S_H - (int)ray.wall_height) / 2 && \
			y <= (S_H + (int)ray.wall_height) / 2)
				my_mlx_pixel_put(&game->world, x + start, y, \
				choose_color(ray, game->textures.wall[ray.f_wall], \
				y - ((S_H - (int)ray.wall_height) / 2), game->torch));
			ray.ty += ray.ty_step;
		}
	}
}

void	draw_gameplan(t_game *game)
{
	int		start;
	int		i;
	double	ca_tmp;
	double	ca;

	i = -1;
	start = 0;
	game->width_per_cell = S_W / (FOV * RES);
	while (++i < FOV * RES)
	{
		ca = to_radiant(game->player->angle) - game->ray[i].ra;
		normalize_angle(&ca);
		ca_tmp = game->ray[i].wall_height;
		ca_tmp *= cos(ca);
		draw_wall(ca_tmp, start, game, game->ray[i]);
		draw_floor(ca_tmp, start, game, game->ray[i]);
		draw_ceiling(ca_tmp, start, game, game->ray[i]);
		start += S_W / (FOV * RES);
	}
}
