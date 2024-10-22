/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:27:49 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/22 19:17:33 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	draw_walls(double dist_t, int start, t_game *game, int color)
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
void	draw_gameplan(t_game *game)
{
	int	start;
	int	i;

	i = -1;
	start = 0;
	while (++i < 60)
	{
		draw_walls(game->ray[i].wall_height, start, game, game->ray[i].color);
		start += S_W / FOV;
	}
}

void	draw_lines(t_game *game)
{
	t_ray ray;
	double dist_t;
	int	start = 0;

	dist_t = 0;
	ray.ra = to_radiant(game->player->angle + 30.00);
	ray.rx = 0;
	ray.r = 0;
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

int	distance_until_wall(t_game *game, int i)
{
	while (game->ray[i].dof < MM_SIZE)
	{
		game->ray[i].mx = game->ray[i].rx / 50;
		game->ray[i].my = game->ray[i].ry / 50;
		if (game->ray[i].mx >= 0 && game->ray[i].my >= 0 \
		&& game->ray[i].mx < 10 && game->ray[i].my < 10 && \
		game->map[game->ray[i].my][game->ray[i].mx] == '1')
			game->ray[i].dof = MM_SIZE;
		else
		{
			game->ray[i].rx += game->ray[i].xo;
			game->ray[i].ry += game->ray[i].yo;
			game->ray[i].dof += 1;
		}
	}
	return (found_distance((int)game->player->pos_x, (int)game->player->pos_y,
	game->ray[i].rx, game->ray[i].ry));
}

int	check_inter_h(t_game *game, int i)
{
	game->ray[i].dof = 0;
	game->ray[i].atan = -1 / tan(game->ray[i].ra);
	if (game->ray[i].ra < PI)
	{
		game->ray[i].ry = (((int)game->player->pos_y  / 50) * 50) - 1;
		game->ray[i].rx = (game->ray[i].ry - (int)game->player->pos_y) * \
		game->ray[i].atan + (int)game->player->pos_x;
		game->ray[i].yo = -50;
		game->ray[i].xo = game->ray[i].yo * game->ray[i].atan;
	}
	if (game->ray[i].ra > PI)
	{
		game->ray[i].ry = (((int)game->player->pos_y  / 50) * 50) + 50;
		game->ray[i].rx = (game->ray[i].ry - (int)game->player->pos_y) * \
		game->ray[i].atan + (int)game->player->pos_x;
		game->ray[i].yo = 50;
		game->ray[i].xo = game->ray[i].yo * game->ray[i].atan;
	}
	if (game->ray[i].ra == 0 || game->ray[i].ra == PI)
	{
		game->ray[i].rx = (int)game->player->pos_x;
		game->ray[i].ry = (int)game->player->pos_y;
		game->ray[i].dof = MM_SIZE;
	}
	return (distance_until_wall(game, i));
}

int	check_inter_v(t_game *game, int i)
{
	game->ray[i].dof = 0;
	game->ray[i].ntan = -tan(game->ray[i].ra);
	if (game->ray[i].ra > P2 && game->ray[i].ra < P3)
	{
		game->ray[i].rx = (((int)game->player->pos_x  / 50) * 50) - 1;
		game->ray[i].ry = (game->ray[i].rx - (int)game->player->pos_x) * \
		game->ray[i].ntan + (int)game->player->pos_y;
		game->ray[i].xo = -50;
		game->ray[i].yo = game->ray[i].xo * game->ray[i].ntan;
	}
	if (game->ray[i].ra < P2 || game->ray[i].ra < P3)
	{
		game->ray[i].rx = (((int)game->player->pos_x  / 50) * 50) + 50;
		game->ray[i].ry = (game->ray[i].rx - (int)game->player->pos_x) * \
		game->ray[i].ntan + (int)game->player->pos_y;
		game->ray[i].xo = 50;
		game->ray[i].yo = game->ray[i].xo * game->ray[i].ntan;
	}
	if (game->ray[i].ra == 0 || game->ray[i].ra == PI)
	{
		game->ray[i].rx = (int)game->player->pos_x;
		game->ray[i].ry = (int)game->player->pos_y;
		game->ray[i].dof = MM_SIZE;
	}
	return (distance_until_wall(game, i));
}

void	fill_rays_infos(t_game *game)
{
	int	i;
	double ra;

	i = -1;
	ra = to_radiant(game->player->angle + 30);
	while (++i < 60)
	{
		game->ray[i].ra = ra;
		if (game->ray[i].ra < 0)
			game->ray[i].ra += 2 * PI;
		if (game->ray[i].ra > 2 * PI)
			game->ray[i].ra -= 2 * PI;
		game->ray[i].distance_h = check_inter_h(game, i);
		game->ray[i].distance_v = check_inter_v(game, i);
		if (game->ray[i].distance_h <= game->ray[i].distance_v)
			game->ray[i].wall_height = game->ray[i].distance_h;
		else
			game->ray[i].wall_height = game->ray[i].distance_v;
		if (game->ray[i].distance_h <= game->ray[i].distance_v)
			game->ray[i].color = 0x800020;
		else
			game->ray[i].color = 0xFF0000;
		ra -= ONE_DEGREE;
	}
}
