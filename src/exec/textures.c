/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 03:25:57 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/06 13:34:41 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	apply_filter(unsigned int color, t_rgb *rgb, int torch, double wall)
{
	double	perc;
	double	max_height;

	max_height = S_H;
	if (torch)
		perc = wall / max_height;
	else
		perc = wall / (max_height * (max_height / (wall / 8)));
	rgb->r = ((color >> 16) & 0xFF) / 255.0;
	rgb->g = ((color >> 8) & 0xFF) / 255.0;
	rgb->b = (color & 0xFF) / 255.0;
	rgb->r *= perc;
	rgb->g *= perc;
	rgb->b *= perc;
}

int	choose_color_floor(t_ray ray, t_img floor, int y, int torch)
{
	unsigned int	color;

	(void)torch;
	(void)y;
	int	ty;
	int	tx;

	tx = ((int)ray.tx % 64) & 63;
	ty = ((int)ray.ty % 64) & 63;
	color = ((int *)floor.pixels)[(ty * floor.width + tx)];
	return (color);
}

int	choose_color(t_ray ray, t_img wall, int y, int torch)
{
	unsigned int	color;
	int				i;
	int				j;
	t_rgb			rgb;

	j = 0;
	(void)rgb;
	(void)torch;
	if (ray.off_y > 0.0)
		j = ray.ty;
	else
		j = y / (ray.wall_height / 64);
	i = ray.offset;
	color = ((int *)wall.pixels)[j * wall.width + i];
	// apply_filter(color, &rgb, torch, ray.wall_height);
	// color = (((int)(rgb.r * 255) & 0xFF) << 16) + (((int)(rgb.g * 255) \
	// 		& 0xFF) << 8) + ((int)(rgb.b * 255) & 0xFF);
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
