/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spider_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:50:55 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/18 23:06:37 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_spider(t_spider *curr, t_game *game, int start_x, int start_y)
{
	int				x;
	int				y;
	unsigned int	color;

	x = -1;
	while (++x < curr->proj_sprite_w)
	{
		y = -1;
		while (++y < curr->proj_sprite_h)
		{
			color = ((int *)game->textures.spider.pixels)[(int)(y / (curr->proj_sprite_h / 64)) * \
			game->textures.spider.width + (int)(x / (curr->proj_sprite_h / 64))];
			if (start_x + x < 0 || start_x + x >= S_W || start_y + y < 0 \
			|| start_y + y >= S_H || color == 0xFF000000)
				continue;
			if (game->ray[start_x + x].save_dist < curr->distance)
				continue;
			my_mlx_pixel_put(&game->world, start_x + x, start_y + y, color);
		}
	}
}

void	recup_spider_infos(t_spider *curr, t_game *game)
{
	curr->hx = curr->x - game->player->pos_x;
	curr->hy = curr->y - game->player->pos_y;
	curr->distance = found_distance(curr->x, curr->y, \
	game->player->pos_x, game->player->pos_y);
	curr->p = (double)to_degrees(atan2(-curr->hy, curr->hx));
	if (curr->p > 360)
		curr->p -= 360;
	if (curr->p < 0)
		curr->p += 360;
	curr->q = game->player->angle + (FOV / 2) - curr->p;
	if (game->player->angle >= 270 && game->player->angle <= 360 \
	&& curr->p >= 0 && curr->p <= 90)
		curr->q -= 360;
	if (game->player->angle >= 0 && game->player->angle <= 90 \
	&& curr->p >= 270 && curr->p <= 360)
		curr->q += 360;
	curr->sp_screen_x = curr->q * (S_W / (FOV));
	curr->sp_screen_y = (S_H / 2) - 50;
	curr->proj_sprite_h = (game->proj * 64 / curr->distance) / 2;
	curr->proj_sprite_w = curr->proj_sprite_h;
}
