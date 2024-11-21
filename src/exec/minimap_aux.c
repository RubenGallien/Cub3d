/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:17:24 by lvicino           #+#    #+#             */
/*   Updated: 2024/11/21 15:34:51 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_obj(t_game *game, t_minimap *m)
{
	int	tile_x;
	int	tile_y;

	tile_x = MM_S_X / MM_SIZE;
	tile_y = MM_S_Y / MM_SIZE;
	if (game->map[(m->start_y + m->y) / tile_y] \
	[(m->start_x + m->x) / tile_x] == 'A')
		my_mlx_pixel_put(&game->world, (S_W - MM_S_X - 10) \
		+ m->x, m->y + 10, 0xaba9a2);
	else if (game->map[(m->start_y + m->y) / tile_y] \
	[(m->start_x + m->x) / tile_x] == 'D' || \
	game->map[(m->start_y + m->y) / tile_y] \
	[(m->start_x + m->x) / tile_x] == 'd')
		my_mlx_pixel_put(&game->world, (S_W - MM_S_X - 10) \
		+ m->x, m->y + 10, 0x83848a);
}
