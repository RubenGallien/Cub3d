/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:51:15 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/22 23:10:29 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_torch(t_game *game)
{
	int		i;
	char	*torch[2];

	torch[0] = TORCH_OFF;
	torch[1] = TORCH_ON;
	i = -1;
	while (++i < 2)
		game->textures.torch[i].img = NULL;
	i = -1;
	while (++i < 2)
		set_data_assets(game, torch[i], &game->textures.torch[i]);
}

void	convert_rgb(t_rgb *rgb, t_game *game, int percentage, int incr[2])
{
	rgb->r = ((((int *)game->world.pixels)[incr[1] * \
	game->world.width + incr[0]] >> 16) & 0xFF) / 255.0;
	rgb->g = ((((int *)game->world.pixels)[incr[1] * \
	game->world.width + incr[0]] >> 8) & 0xFF) / 255.0;
	rgb->b = ((((int *)game->world.pixels)[incr[1] * \
	game->world.width + incr[0]]) & 0xFF) / 255.0;
	rgb->r /= percentage;
	rgb->g /= percentage;
	rgb->b /= percentage;
}

void	apply_darker(t_game *game, int percentage)
{
	int				incr[2];
	t_rgb			rgb;
	unsigned int	color;
	unsigned char	*dst;

	incr[0] = 0;
	while (incr[0] < game->world.width)
	{
		incr[1] = 0;
		while (incr[1] < game->world.height)
		{
			convert_rgb(&rgb, game, percentage, incr);
			color = (((int)(rgb.r * 255) & 0xFF) << 16) + (((int)(rgb.g * 255) \
			& 0xFF) << 8) + ((int)(rgb.b * 255) & 0xFF);
			dst = game->world.pixels + (incr[1] * game->world.line_length + \
			incr[0] * (game->world.bits_per_pixel / 8));
			*(unsigned int *)dst = color;
			incr[1]++;
		}
		incr[0]++;
	}
}

void	draw_torch(t_game *game, int x, int y)
{
	int				i;
	int				j;
	unsigned char	*dst;
	unsigned int	color;

	i = 0;
	while (i < game->textures.torch[game->torch].width * 12)
	{
		j = -1;
		while (++j < game->textures.torch[game->torch].height * 12)
		{
			color = ((int *)game->textures.torch[game->torch].pixels)[(j / 12) \
			* game->textures.torch[game->torch].width + (i / 12)];
			if (color == 0xFF000000)
				continue ;
			dst = game->world.pixels + ((y + j) * game->world.line_length + (\
			x + i) * (game->world.bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
		i++;
	}
}
