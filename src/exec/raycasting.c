/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:27:49 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/23 19:58:55 by rgallien         ###   ########.fr       */
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
				if ((!x || !y || x == width || y == (S_H - (int)line_h) / 2 || y == (S_H - (S_H - (int)line_h) / 2)) && \
				((y > (S_H - (int)line_h) / 2 && (y < (S_H - (S_H - (int)line_h) / 2)))))
					my_mlx_pixel_put(&game->world, x + start, y, 0x000000);
				else if (y < (S_H - (int)line_h) / 2)
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

	i = -1;
	start = 0;
	while (++i < FOV)
	{
		double ca = to_radiant(game->player->angle) - game->ray[i].ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		game->ray[i].wall_height *= cos(ca);
		draw_walls(game->ray[i].wall_height, start, game, game->ray[i].color);
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
	if (to_degrees(game->ray[i].ra) == 359 || to_degrees(game->ray[i].ra) == 179)
	{
		game->ray[i].rx = game->player->pos_x;
		game->ray[i].ry = game->player->pos_y;
		game->ray[i].dof = 10;
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
	if (game->ray[i].ra < P2 || game->ray[i].ra > P3)
	{
		game->ray[i].rx = (((int)game->player->pos_x  / 50) * 50) + 50;
		game->ray[i].ry = (game->ray[i].rx - (int)game->player->pos_x) * \
		game->ray[i].ntan + (int)game->player->pos_y;
		game->ray[i].xo = 50;
		game->ray[i].yo = game->ray[i].xo * game->ray[i].ntan;
	}
	if (to_degrees(game->ray[i].ra) == 89 || to_degrees(game->ray[i].ra) == 269)
	{
		game->ray[i].rx = game->player->pos_x;
		game->ray[i].ry = game->player->pos_y;
		game->ray[i].dof = 10;
	}
	return (distance_until_wall(game, i));
}

void	fill_rays_infos(t_game *game)
{
	int	i;
	double ra;

	i = -1;
	ra = to_radiant(game->player->angle + FOV / 2);
	while (++i < FOV)
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
		if (game->ray[i].distance_v < game->ray[i].distance_h)
			game->ray[i].wall_height = game->ray[i].distance_v;
		if (game->ray[i].distance_v <= game->ray[i].distance_h)
			game->ray[i].color = 0x940303;
		else
			game->ray[i].color = 0xFF0000;
		ra -= ONE_DEGREE;
	}
}
