/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    converter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 22:19:23 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/09 22:20:19 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	to_degrees(double number)
{
	return (number * (180 / PI));
}

double	to_radiant(double number)
{
	return (number * (PI / 180));
}
