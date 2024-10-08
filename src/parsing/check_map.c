/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:14:47 by lvicino           #+#    #+#             */
/*   Updated: 2024/10/07 14:39:11 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_closed()
{
	return (1);
}

int	check_components()
{
	return (1);
}

int	check_map(t_game *game)
{
	(void)game;
	if (!check_components() || !is_closed())
		return (0);
	return (1);
}
