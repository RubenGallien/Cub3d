	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:41:07 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/27 21:58:11 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int choose_color(t_ray ray, t_img wall, int y, float line_h, float ty)
{
	unsigned int	color;
	int				i;
	int				j;

	j = 0;
	if (ray.wall_height > S_H)
	{
		j = ty;
		i = ray.offset;
	}
	else
	{
		j = y / (line_h / 64);
		i = ray.offset;
	}
	color = ((int *)wall.pixels)[j * wall.width + i];
	return (color);
}

void	choose_textures(t_game *game, int i)
{
	if (game->ray[i].distance_h <= game->ray[i].distance_v)
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


int	set_data_assets(t_game *game, char *_path, t_img *textures)
{
	textures->img = mlx_xpm_file_to_image(game->mlx, _path, &textures->width, \
	&textures->height);
	textures->pixels = (unsigned char *)mlx_get_data_addr(textures->img, \
	&textures->bits_per_pixel, &textures->line_length, &textures->endian);
	return (1);
}

void	init_textures(t_game *game)
{
	int		i;
	char	*torch[] = {TORCH_ON, TORCH_OFF};

	i = -1;
	while (++i < 4)
		set_data_assets(game, game->info.texture[i], &game->textures.wall[i]);
	i = -1;
	while (++i < 2)
		set_data_assets(game, torch[i], &game->textures.torch[i]);
}
