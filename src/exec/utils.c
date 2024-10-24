/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:42:34 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/24 17:38:25 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double	found_distance(int x1, int y1, int x2, int y2)
{
	double	dist1;
	double	dist2;
	double	dist3;

	if (x1 == x2 && y1 == y2)
		return (10 * 50);
	dist1 = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
	dist2 = sqrt((((x2 + 1) - x1) * ((x2 + 1) - x1)) + ((y2 - y1) * (y2 - y1)));
	dist3 = sqrt((((x2 - 1) - x1) * ((x2 - 1) - x1)) + ((y2 - y1) * (y2 - y1)));
	if (dist2 < dist1 && dist2 < dist3)
		return (dist2);
	else if (dist3 < dist2 && dist3 < dist1)
		return (dist3);
	else
		return (dist1);
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