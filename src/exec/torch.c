/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:51:15 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/30 19:27:47 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void	apply_darker(t_game *game)
{
	int		i;
	int		j;
	t_rgb	rgb;
	unsigned int color;
	unsigned char	*dst;

	i = 0;
	while (i < game->world.width)
	{
		j = 0;
		while (j < game->world.height)
		{
			rgb.r = ((((int *)game->world.pixels)[j * game->world.width + i] >> 16) & 0xFF) / 255.0;
			rgb.g = ((((int *)game->world.pixels)[j * game->world.width + i] >> 8) & 0xFF) / 255.0;
			rgb.b = ((((int *)game->world.pixels)[j * game->world.width + i]) & 0xFF) / 255.0;
			rgb.r /= 5;
			rgb.g /= 5;
			rgb.b /= 5;
			color = (((int)(rgb.r * 255) & 0xFF) << 16) + (((int)(rgb.g * 255) & 0xFF) << 8) + ((int)(rgb.b * 255) & 0xFF);
			dst = game->world.pixels + (j * game->world.line_length + i \
			* (game->world.bits_per_pixel / 8));
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
}

void	draw_torch(t_game *game, int x, int y)
{
	int				i;
	int				j;
	unsigned char	*dst;
	unsigned int	color;

	i = 0;
	while (i < game->textures.torch[game->torch].width * 8)
	{
		j = -1;
		while (++j < game->textures.torch[game->torch].height * 8)
		{
			color = ((int *)game->textures.torch[game->torch].pixels)[(j / 8) * game->textures.torch[game->torch].width + (i / 8)];
			if (color == 0xFF000000)
				continue ;
			dst = game->world.pixels + ((y + j) * game->world.line_length + (x + i) \
			* (game->world.bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
		i++;
	}
}
