/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 03:25:57 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/03 16:25:24 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	choose_color(t_ray ray, t_img wall, int y)
{
	unsigned int	color;
	int				i;
	int				j;

	j = 0;
	if (ray.off_y > 0.0)
		j = ray.ty;
	else
		j = y / (ray.wall_height / 64);
	i = ray.offset;
	color = ((int *)wall.pixels)[j * wall.width + i];
	return (color);
}

void	h_textures(t_game *game, int i)
{
	game->ray[i].rx = game->ray[i].rx_tmp;
	if (game->ray[i].ry > game->player->pos_y)
	{
		game->ray[i].offset = 63 - (int)game->ray[i].rx % 64;
		game->ray[i].f_wall = 3;
	}
	else if (game->ray[i].ry == game->player->pos_y)
	{
		if (game->ray[i].ra > PI && game->ray[i].ra < PI * 2)
		{
			game->ray[i].offset = 63 - (int)game->ray[i].rx % 64;
			game->ray[i].f_wall = 3;
		}
		else
		{
			game->ray[i].f_wall = 2;
			game->ray[i].offset = (int)game->ray[i].rx % 64;
		}
	}
	else
	{
		game->ray[i].f_wall = 2;
		game->ray[i].offset = (int)game->ray[i].rx % 64;
	}
}

void	choose_textures(t_game *game, int i)
{
	if (game->ray[i].distance_h <= game->ray[i].distance_v)
		h_textures(game, i);
	else
	{
		if (game->ray[i].rx > game->player->pos_x)
		{
			game->ray[i].offset = (int)game->ray[i].ry % 64;
			game->ray[i].f_wall = 1;
		}
		else
		{
			game->ray[i].offset = 63 - (int)game->ray[i].ry % 64;
			game->ray[i].f_wall = 0;
		}
	}
}
