/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:27:49 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/25 17:03:28 by rgallien         ###   ########.fr       */
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
		width = S_W / (FOV);
		while (x < width)
		{
			y = 0;
			while (y < S_H)
			{
				if (y < (S_H - (int)line_h) / 2)
					my_mlx_pixel_put(&game->world, x + start, y, 0x0000FF);
				else if (y > (S_H - (S_H - (int)line_h) / 2))
					my_mlx_pixel_put(&game->world, x + start, y, 0x00FF00);
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
	double ca_tmp;
	i = -1;
	start = 0;
	while (++i < FOV)
	{
		double ca = to_radiant(game->player->angle) - game->ray[i].ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		ca_tmp = game->ray[i].wall_height;
		ca_tmp *= cos(ca);
		draw_walls(ca_tmp, start, game, game->ray[i].color);
		start += S_W / (FOV);
	}
}

int	distance_until_wall(t_game *game, int i)
{
	while (game->ray[i].dof < 10)
	{
		game->ray[i].mx = game->ray[i].rx / 50;
		game->ray[i].my = game->ray[i].ry / 50;
		if (game->ray[i].mx >= 0 && game->ray[i].my >= 0 \
		&& game->ray[i].mx < 10 && game->ray[i].my < 10 && \
		game->map[game->ray[i].my][game->ray[i].mx] == '1')
			game->ray[i].dof = 10;
		else
		{
			game->ray[i].rx += game->ray[i].xo;
			game->ray[i].ry += game->ray[i].yo;
			game->ray[i].dof += 1;
		}
	}
	return (found_distance(game->player->pos_x, game->player->pos_y,
	game->ray[i].rx, game->ray[i].ry));
}

void	check_inter_h(t_game *game, int i)
{
	int	b;
	double	save_x;
	double	save_y;

	b = 0;
	save_x = game->player->pos_x;
	save_y = game->player->pos_y;
	while (++b < 2)
	{
		incr_pos(game, b, save_x, save_y);
		game->ray[i].dof = 0;
		game->ray[i].atan = -1 / tan(game->ray[i].ra);
		extra_h(game, i);
		// if (i == 1)
		// {
		// 	printf("atan  = %f\n", game->ray[i].atan);
		// 	printf("rx = %f\n", game->ray[i].ry);
		// 	printf("ry = %f\n", game->ray[i].ry);
		// 	printf("xo = %f\n", game->ray[i].xo);
		// 	printf("yo = %f\n", game->ray[i].yo);
		// 	printf("ra = %d\n", to_degrees(game->ray[i].ra));
		// }
		straight_dist(game, 'h', i);
		game->ray[i].distance_h = distance_until_wall(game, i);
		if (game->ray[i].distance_h < game->ray[i].tmp)
			game->ray[i].tmp = game->ray[i].distance_h;
	}
	game->player->pos_x = save_x;
	game->player->pos_y = save_y;
	game->ray[i].distance_h = game->ray[i].tmp;
}

void	check_inter_v(t_game *game, int i)
{
	int		b;
	double	save_x;
	double	save_y;

	b = 0;
	save_x = game->player->pos_x;
	save_y = game->player->pos_y;
	while (++b < 2)
	{
		incr_pos(game, b, save_x, save_y);
		game->ray[i].dof = 0;
		game->ray[i].ntan = -tan(game->ray[i].ra);
		extra_v(game, i);
		straight_dist(game, 'v', i);
		game->ray[i].distance_v = distance_until_wall(game, i);
		if (game->ray[i].distance_v < game->ray[i].tmp)
			game->ray[i].tmp = game->ray[i].distance_v;
	}
	game->player->pos_x = save_x;
	game->player->pos_y = save_y;
	game->ray[i].distance_v = game->ray[i].tmp;
}

void	fill_rays_infos(t_game *game)
{
	int	i;
	double ra;

	i = -1;
	ra = to_radiant(game->player->angle + FOV / 2);
	while (++i < FOV)
	{
		game->ray[i].tmp = 10 * 50;
		game->ray[i].ra = ra;
		if (game->ray[i].ra < 0)
			game->ray[i].ra += 2 * PI;
		if (game->ray[i].ra > 2 * PI)
			game->ray[i].ra -= 2 * PI;
		check_inter_h(game, i);
		check_inter_v(game, i);
		// if (i == 58)
		// {
		// 	printf("distance_h = %d\n", game->ray[i].distance_h);
		// 	printf("distance_v = %d\n", game->ray[i].distance_v);
		// }
		if (game->ray[i].distance_h <= game->ray[i].distance_v)
			game->ray[i].wall_height = game->ray[i].distance_h;
		if (game->ray[i].distance_v < game->ray[i].distance_h)
			game->ray[i].wall_height = game->ray[i].distance_v;
		if (game->ray[i].distance_h <= game->ray[i].distance_v)
			game->ray[i].color = 0xFF0000;
		else
			game->ray[i].color = 0x940303;
		ra -= ONE_DEGREE;
	}
}
