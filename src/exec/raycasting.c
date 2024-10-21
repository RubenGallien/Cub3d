/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:27:49 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/21 18:17:07 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_walls(double dist_t, int start, t_game *game, int color)
{
		float line_h;
		int	width;
		int	x;
		int	y;

		x = 0;
		line_h = 32 * S_W / dist_t;
		if (line_h > S_H)
			line_h = S_H;
		width = S_W / FOV;
		while (x < width)
		{
			y = 0;
			while (y < S_H)
			{
				if (y < (S_H - (int)line_h) / 2 || y > (S_H - (S_H - (int)line_h) / 2))
					my_mlx_pixel_put(&game->world, x + start, y, 0x000000);
				else
					my_mlx_pixel_put(&game->world, x + start, y, color);
				y++;
			}
			x++;
		}
}

void	draw_lines(t_game *game)
{
	t_ray ray;
	double dist_t;
	int	start = 0;

	dist_t = 0;
	ray.ra = to_radiant(game->player->angle + 30.00);
	ray.r = -1;
	ray.rx = 0;
	ray.ry = 0;
	ray.xo = 0;
	ray.yo = 0;
	while (++ray.r < 60)
	{
		if (ray.ra < 0)
			ray.ra += 2 * PI;
		if (ray.ra > 2 * PI)
			ray.ra -= 2 * PI;
		// horizontal line
		ray.dof = 0;
		ray.atan = -1 / tan(ray.ra);
		if (ray.ra < PI)
		{
			// haut
			ray.ry = (((int)game->player->pos_y / 50) * 50) - 1;
			ray.rx = (ray.ry - (int)game->player->pos_y) * ray.atan + (int)game->player->pos_x;
			ray.yo = -50;
			ray.xo = ray.yo * ray.atan;
		}
		if (ray.ra > PI)
		{
			// bas
			ray.ry = (((int)game->player->pos_y / 50) * 50) + 50;
			ray.rx = (ray.ry - (int)game->player->pos_y) * ray.atan + (int)game->player->pos_x;
			ray.yo = 50;
			ray.xo = ray.yo * ray.atan;
		}
		if (ray.ra == 0 || ray.ra == PI)
		{
			ray.rx = (int)game->player->pos_x;
			ray.ry = (int)game->player->pos_y;
			ray.dof = MM_SIZE;
		}
		while (ray.dof < MM_SIZE)
		{
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
		ray.dof = 0;
		ray.ntan = -tan(ray.ra);
		if (ray.ra > P2 && ray.ra < P3)
		{
			// left
			ray.rx = (((int)game->player->pos_x / 50) * 50) - 1;
			ray.ry = (ray.rx - (int)game->player->pos_x) * ray.ntan + (int)game->player->pos_y;
			ray.xo = -50;
			ray.yo = ray.xo * ray.ntan;
		}
		if (ray.ra < P2 || ray.ra > P3)
		{
			// right
			ray.rx = (((int)game->player->pos_x / 50) * 50) + 50;
			ray.ry = (ray.rx - (int)game->player->pos_x) * ray.ntan + (int)game->player->pos_y;
			ray.xo = 50;
			ray.yo = ray.xo * ray.ntan;
		}
		if (ray.ra == 0 || ray.ra == PI)
		{
			ray.rx = (int)game->player->pos_x;
			ray.ry = (int)game->player->pos_y;
			ray.dof = MM_SIZE;
		}
		while (ray.dof < MM_SIZE)
		{
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
		int	color;
		distance2 = found_distance((int)game->player->pos_x, (int)game->player->pos_y, ray.rx, ray.ry);
		int	f_dist;
		if (distance <= distance2)
		{
			f_dist = distance;
			dist_t = distance;
			color = 0x800020;
		}
		else
		{
			dist_t = distance2;
			f_dist = distance2;
			color = 0xFF0000;
		}
		int	u = -1;
		int start_x = (S_W - MM_S_X) + (MM_S_X / 2) - MM_SIZE;
		int start_y = (MM_S_Y / 2) - MM_SIZE;
		double xx = cos(ray.ra);
		double yy = sin(ray.ra);
		while (++u < f_dist && u < 124)
			my_mlx_pixel_put(&game->world, (start_x + 5 + (u * xx)), start_y + 5 - (u * yy), 0x00FF00);
		draw_walls(dist_t, start, game, color);
		start += S_W / FOV;
		ray.ra -= ONE_DEGREE;
	}
}
