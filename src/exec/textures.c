/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 03:25:57 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/21 13:28:21 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_f_c(unsigned int color, t_rgb *rgb, int torch, int y)
{
	double	perc;

	if (torch)
		perc = (double)y / S_H - 0.550;
	else
		perc = 0.01;
	if (perc < 0)
		perc = 0;
	rgb->r = ((color >> 16) & 0xFF) / 255.0 * perc;
	rgb->g = ((color >> 8) & 0xFF) / 255.0 * perc;
	rgb->b = (color & 0xFF) / 255.0 * perc;
}

int	choose_col_floor_ceiling(t_ray ray, t_img floor, int y, int torch)
{
	unsigned int	color;
	int				ty;
	int				tx;
	t_rgb			rgb;

	(void)torch;
	(void)y;
	tx = ((int)ray.tx % 64) & 63;
	ty = ((int)ray.ty % 64) & 63;
	color = ((int *)floor.pixels)[(ty * floor.width + tx)];
	color_f_c(color, &rgb, torch, y);
	color = (((int)(rgb.r * 255) & 0xFF) << 16) + (((int)(rgb.g * 255) \
	& 0xFF) << 8) + ((int)(rgb.b * 255) & 0xFF);
	return (color);
}

int	choose_color(t_ray *ray, t_game *game, int y)
{
	int				i;
	int				j;
	t_rgb			rgb;
	t_img			wall;

	j = 0;
	if (ray->off_y > 0.0)
		j = ray->ty;
	else
		j = y / (ray->wall_height / 64);
	i = ray->offset;
	if (ray->door)
		wall = game->textures.door;
	else
		wall = game->textures.wall[ray->f_wall];
	ray->color = ((int *)wall.pixels)[j * wall.width + i];
	rgb.r = ((ray->color >> 16) & 0xFF) / 255.0 * ray->perc;
	rgb.g = ((ray->color >> 8) & 0xFF) / 255.0 * ray->perc;
	rgb.b = (ray->color & 0xFF) / 255.0 * ray->perc;
	ray->color = (((int)(rgb.r * 255) & 0xFF) << 16) + (((int)(rgb.g * 255) \
	& 0xFF) << 8) + ((int)(rgb.b * 255) & 0xFF);
	return (ray->color);
}

void	h_textures(t_game *game, int i)
{
	game->ray[i].rx = game->ray[i].rx_tmp;
	game->ray[i].door = game->ray[i].h_door;
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
