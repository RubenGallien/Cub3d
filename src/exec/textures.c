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

void	choose_textures(t_game *game, int i)
{
	if (game->ray[i].distance_h < game->ray[i].distance_v)
	{
		if (game->ray[i].ry > game->player->pos_y)
			game->ray[i].f_wall = 3;
		else
			game->ray[i].f_wall = 2;
		game->ray[i].offset = (int)game->ray[i].rx % 50;
	}
	else
	{
		if (game->ray[i].rx > game->player->pos_x)
			game->ray[i].f_wall = 1;
		else
			game->ray[i].f_wall = 0;
		game->ray[i].offset = (int)game->ray[i].ry % 50;
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
	char	*wall[] = {WALL_E, WALL_W, WALL_S, WALL_N};

	i = -1;
	while (++i < 4)
		set_data_assets(game, wall[i], &game->textures.wall[i]);
}