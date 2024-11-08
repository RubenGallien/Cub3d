/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:07:16 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/07 23:59:26 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor(double dist_t, int start, t_game *game, t_ray ray)
{
	int		x;
	int		y;
	double		proj;
	double		r;
	double		straight_line;
	double		beta;
	double		d;
	double		n;

	ray.wall_height = (WALL_SIZE * S_H) / dist_t;
	if (ray.wall_height > S_H)
		ray.wall_height = S_H;
	x = -1;
	proj = S_W / (2 * tan(to_radiant(FOV / 2)));
	beta = fabs(ray.ra - to_radiant(game->player->angle));
	while (++x < (int)game->width_per_cell)
	{
		y = ((S_H - (S_H - (int)ray.wall_height) / 2)) - 1;
		while (++y < S_H)
		{
			r = y - (S_H / 2.0);
			straight_line = (WALL_SIZE / 3) * proj / r;
			d = straight_line / cos(beta);
			ray.tx = game->player->pos_x + cos(ray.ra) * d;
			ray.ty = game->player->pos_y - sin(ray.ra) * d;
			my_mlx_pixel_put(&game->world, x + start, y, choose_color_floor_ceiling(ray, game->textures.floor, \
			y, game->torch));
			n = ray.ty - (S_H / 2);
			ray.ty = (S_H / 2) - n;
			my_mlx_pixel_put(&game->world, x + start, (S_H / 2) - (y - (S_H / 2)), choose_color_floor_ceiling(ray, game->textures.ceiling, \
			y, game->torch));
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
	int		min;
	int		max;

	draw_wall_aux(dist_t, &ray);
	min = (S_H - (int)ray.wall_height) / 2;
	max = (S_H + (int)ray.wall_height) / 2;
	x = -1;
	while (++x < (int)game->width_per_cell)
	{
		ray.ty_step = 64.0 / ((WALL_SIZE * S_H) / dist_t);
		ray.ty = ray.off_y * ray.ty_step;
		y =  min -1;
		while (++y < max)
		{
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
		// draw_ceiling(ca_tmp, start, game, game->ray[i]);
		start += S_W / (FOV * RES);
	}
}
