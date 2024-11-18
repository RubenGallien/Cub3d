/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:27:49 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/18 16:30:20 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	distance_until_wall_v(t_game *game, int i)
{
	while (game->ray[i].dof < game->info.ln_max)
	{
		game->ray[i].mx = game->ray[i].rx / 64;
		game->ray[i].my = game->ray[i].ry / 64;
		if (game->ray[i].mx >= 0 && game->ray[i].my >= 0 \
		&& game->ray[i].mx < game->info.ln_x && game->ray[i].my \
		< game->info.ln_y && game->map[game->ray[i].my][game->ray[i].mx] == '1')
		{
			game->ray[i].dof = game->info.ln_max;
			game->ray[i].distance_v = found_distance(game->player->pos_x, \
			game->player->pos_y, game->ray[i].rx, game->ray[i].ry);
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
		&& game->ray[i].mx < game->info.ln_x && game->ray[i].my < \
		game->info.ln_y && game->map[game->ray[i].my][game->ray[i].mx] == '1')
		{
			game->ray[i].dof = game->info.ln_max;
			game->ray[i].distance_h = found_distance(game->player->pos_x, \
			game->player->pos_y, game->ray[i].rx, game->ray[i].ry);
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
	game->ray[i].rx_tmp = game->ray[i].rx;
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
		normalize_angle(&game->ray[i].ra);
		check_inter_h(game, i);
		check_inter_v(game, i);
		choose_distance(game, i);
		choose_textures(game, i);
		ra -= ONE_DEGREE / RES;
	}
}
