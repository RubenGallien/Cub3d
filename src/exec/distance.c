/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:41:58 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/28 11:17:49 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	incr_pos(t_game *game, int b, double save_x, double save_y)
{
	if (b == 0)
	{
		game->player->pos_x = \
		save_x + cos(to_radiant(game->player->angle + 90)) * 1;
		game->player->pos_y = \
		save_y - sin(to_radiant(game->player->angle + 90)) * 1;
	}
	else if (b == 1)
	{
		game->player->pos_x = save_x;
		game->player->pos_y = save_y;
	}
	else if (b == 2)
	{
		game->player->pos_x = \
		save_x - cos(to_radiant(game->player->angle + 90)) * 1;
		game->player->pos_y = \
		save_y + sin(to_radiant(game->player->angle + 90)) * 1;
	}
}

void	straight_dist(t_game *game, char sense, int i)
{
	if (sense == 'h')
	{
		if (to_degrees(game->ray[i].ra) == 359 || to_degrees(game->ray[i].ra) == 179)
		{
			game->ray[i].rx = game->player->pos_x;
			game->ray[i].ry = game->player->pos_y;
			game->ray[i].dof = game->info.ln_max;
		}
	}
	if (sense == 'v')
	{
		if (to_degrees(game->ray[i].ra) == 89 || to_degrees(game->ray[i].ra) == 269)
		{
			game->ray[i].rx = game->player->pos_x;
			game->ray[i].ry = game->player->pos_y;
			game->ray[i].dof = game->info.ln_max;
		}
	}
}

void	extra_h(t_game *game, int i)
{
	if (game->ray[i].ra < PI)
	{
		game->ray[i].ry = (((int)game->player->pos_y  / 50) * 50) - 0.0001;
		game->ray[i].rx = (game->ray[i].ry - (int)game->player->pos_y) * \
		game->ray[i].atan + (int)game->player->pos_x;
		game->ray[i].yo = -50;
		game->ray[i].xo = game->ray[i].yo * game->ray[i].atan;
	// 	if (i == 0)
	// 	{
	// 		printf("rx = %f\n", game->ray[i].rx);
	// 		printf("ry = %f\n", game->ray[i].ry);
	// 		printf("xo = %f\n", game->ray[i].xo);
	// 		printf("yo = %f\n", game->ray[i].yo);
	// 	}
	}
	if (game->ray[i].ra > PI)
	{
		game->ray[i].ry = (((int)game->player->pos_y  / 50) * 50) + 50;
		game->ray[i].rx = (game->ray[i].ry - (int)game->player->pos_y) * \
		game->ray[i].atan + (int)game->player->pos_x;
		game->ray[i].yo = 50;
		game->ray[i].xo = game->ray[i].yo * game->ray[i].atan;
	}
}
void	extra_v(t_game *game, int i)
{
	if (game->ray[i].ra > P2 && game->ray[i].ra < P3)
	{
		game->ray[i].rx = (((int)game->player->pos_x  / 50) * 50) - 0.0001;
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
}
