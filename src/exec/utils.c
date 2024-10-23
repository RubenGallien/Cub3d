/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:42:34 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/23 17:24:23 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int	found_distance(int x1, int y1, int x2, int y2)
{
	if (x1 == x2 && y1 == y2)
		return (10 * 50);
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	unsigned char	*dst;

	dst = img->pixels + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

double	to_radiant(double	number)
{
	return (number * (M_PI / 180));
}

int	to_degrees(double	number)
{
	return (number * (180 / M_PI));
}