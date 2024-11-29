/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:12:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/14 13:23:53 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_pause(t_img asset, t_img *img, t_game *game)
{
	int				i;
	int				j;
	unsigned char	*dst;
	unsigned int	color;

	i = 0;
	while (i < asset.width)
	{
		j = -1;
		while (++j < asset.height)
		{
			color = ((int *)asset.pixels)[j * asset.width + i];
			if (color == 0xFF000000)
				continue ;
			dst = img->pixels + (j * img->line_length + i \
			* (img->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->world.img, 0, 0);
	return (1);
}

int	game_loop(t_game *game)
{
	int	y_torch_start;
	int	x_torch_start;

	x_torch_start = S_W / 8;
	y_torch_start = S_H - (64 * 12);
	mlx_mouse_get_pos(game->mlx, game->mlx_win, &game->mouse.x, &game->mouse.y);
	if (!game->tick && game->mlx_win && game->lock)
	{
		move_player(game);
		mlx_mouse_move(game->mlx, game->mlx_win, S_W / 2, S_H / 2);
		(fill_rays_infos(game), draw_gameplan(game), make_spider(game));
		minimap(game);
		if (game->torch)
			draw_torch(game, x_torch_start, y_torch_start);
		mlx_put_image_to_window(game->mlx, game->mlx_win, \
		game->world.img, 0, 0);
		game->animation = (game->animation + 1) % 10;
	}
	else if (!game->lock && game->mlx_win)
		draw_pause(game->textures.pause, &game->world, game);
	game->tick = (game->tick + 1) % (15000 / SPEED);
	return (0);
}
