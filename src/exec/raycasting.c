/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:27:49 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/31 15:43:33 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_walls(double dist_t, int start, t_game *game, t_ray ray)
{
		float line_h;
		double	width;
		int	x;
		int	y;

		x = 0;
		line_h = WALL_SIZE * S_H / dist_t;
		ray.wall_height = line_h;
		if (line_h > S_H)
			line_h = S_H;
		width = S_W / (FOV * RES);
		while (x < (int)width)
		{
			y = 0;
			while (y < S_H)
			{
				if (y < (S_H - (int)line_h) / 2)
					my_mlx_pixel_put(&game->world, x + start, y, game->info.colour[1]);
				else if (y >= (S_H - (S_H - (int)line_h) / 2))
					my_mlx_pixel_put(&game->world, x + start, y, game->info.colour[0]);
				else
					my_mlx_pixel_put(&game->world, x + start, y, \
					choose_color(ray, game->textures.wall[ray.f_wall], \
					y - ((S_H - (int)line_h) / 2), line_h, x));
				y++;
			}
			x++;
		}
}

void	draw_gameplan(t_game *game)
{
	int	start;
	int	i;
	double ca_tmp;

	i = -1;
	start = 0;
	while (++i < FOV * RES)
	{
		double ca = to_radiant(game->player->angle) - game->ray[i].ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		ca_tmp = game->ray[i].wall_height;
		ca_tmp *= cos(ca);
		draw_walls(ca_tmp, start, game, game->ray[i]);
		start += S_W / (FOV * RES);
	}
}

void	distance_until_wall_v(t_game *game, int i)
{
	while (game->ray[i].dof < game->info.ln_max)
	{
		game->ray[i].mx = game->ray[i].rx / 64;
		game->ray[i].my = game->ray[i].ry / 64;
		if (game->ray[i].mx >= 0 && game->ray[i].my >= 0 \
		&& game->ray[i].mx < game->info.ln_x && game->ray[i].my < game->info.ln_y && \
		game->map[game->ray[i].my][game->ray[i].mx] == '1')
		{
			game->ray[i].dof = game->info.ln_max;
			game->ray[i].distance_v = found_distance(game->player->pos_x, game->player->pos_y, \
			game->ray[i].rx, game->ray[i].ry);
		}
		else
		{
			game->ray[i].rx += game->ray[i].xo;
			game->ray[i].ry += game->ray[i].yo;
			game->ray[i].dof += 1;
		}
	}
}

void	distance_until_wall_h(t_game *game, int i)
{
	while (game->ray[i].dof < game->info.ln_max)
	{
		game->ray[i].mx = game->ray[i].rx / 64;
		game->ray[i].my = game->ray[i].ry / 64;
		if (game->ray[i].mx >= 0 && game->ray[i].my >= 0 \
		&& game->ray[i].mx < game->info.ln_x && game->ray[i].my < game->info.ln_y && \
		game->map[game->ray[i].my][game->ray[i].mx] == '1')
		{
			game->ray[i].dof = game->info.ln_max;
			game->ray[i].distance_h = found_distance(game->player->pos_x, game->player->pos_y, \
			game->ray[i].rx, game->ray[i].ry);\
		}
		else
		{
			game->ray[i].rx += game->ray[i].xo;
			game->ray[i].ry += game->ray[i].yo;
			game->ray[i].dof += 1;
		}
	}
}

void	check_inter_h(t_game *game, int i)
{
	game->ray[i].dof = 0;
	game->ray[i].atan = -1 / tan(game->ray[i].ra);
	extra_h(game, i);
	straight_dist(game, 'h', i);
	distance_until_wall_h(game, i);
}

void	check_inter_v(t_game *game, int i)
{
	game->ray[i].rx_tmp =  game->ray[i].rx;
	game->ray[i].dof = 0;
	game->ray[i].ntan = -tan(game->ray[i].ra);
	extra_v(game, i);
	straight_dist(game, 'v', i);
	distance_until_wall_v(game, i);
}

void	fill_rays_infos(t_game *game)
{
	int		i;
	double	ra;

	i = -1;
	if (game->info.ln_x >= game->info.ln_y)
		game->info.ln_max = game->info.ln_x;
	else
		game->info.ln_max = game->info.ln_y;
	ra = to_radiant(game->player->angle + (FOV / 2));
	while (++i < FOV * RES)
	{
		game->ray[i].distance_h = 100000000;
		game->ray[i].distance_v = 100000000;
		game->ray[i].tmp = game->info.ln_max * 64;
		game->ray[i].ra = ra;
		if (game->ray[i].ra < 0)
			game->ray[i].ra += 2 * PI;
		if (game->ray[i].ra > 2 * PI)
			game->ray[i].ra -= 2 * PI;
		check_inter_h(game, i);
		check_inter_v(game, i);
		if (game->ray[i].distance_h <= game->ray[i].distance_v)
			game->ray[i].wall_height = game->ray[i].distance_h;
		if (game->ray[i].distance_v < game->ray[i].distance_h)
			game->ray[i].wall_height = game->ray[i].distance_v;
		choose_textures(game, i);
		ra -= ONE_DEGREE / RES;
	}
}
