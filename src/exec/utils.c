/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:42:34 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/18 12:36:48 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_data_assets(t_game *game, char *_path, t_img *textures)
{
	textures->img = mlx_xpm_file_to_image(game->mlx, _path, &textures->width, \
	&textures->height);
	textures->pixels = (unsigned char *)mlx_get_data_addr(textures->img, \
	&textures->bits_per_pixel, &textures->line_length, &textures->endian);
	return (1);
}

void	normalize_angle(double *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
}

double	found_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	unsigned char	*dst;

	dst = img->pixels + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
