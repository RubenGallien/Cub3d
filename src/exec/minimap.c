/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:18:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/04 15:17:45 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fov_line_mm(t_game *game)
{
	int	start_x;
	int	start_y;
	int	i;
	int	l;

	i = -1;
	start_x = ((S_W - MM_S_X) + (MM_S_X / 2) - MM_SIZE) - 10;
	start_y = ((MM_S_Y / 2) - MM_SIZE) + 10;
	while (++i < FOV * RES)
	{
		l = -1;
		while (++l < game->ray[i].wall_height && l < 160)
			my_mlx_pixel_put(&game->world, start_x + MM_SIZE + \
			(l * cos(game->ray[i].ra)), \
			start_y + MM_SIZE - (l * sin(game->ray[i].ra)), 0xd9d509);
	}
}

void	draw_player(t_game *game, int start_x, int start_y, int color)
{
	int	i;
	int	j;
	int	u;

	u = -1;
	i = 0;
	while (++u < 15)
		my_mlx_pixel_put(&game->world, start_x + (u * game->player->pdx), \
		start_y - (u * game->player->pdy), 0xFF00FF);
	while (i < 1)
	{
		j = 0;
		while (j < 1)
		{
			my_mlx_pixel_put(&game->world, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_aux(t_game *game, t_minimap *m)
{
	if ((m->start_x + m->x) % MM_TILE_X == 0 || \
		(m->start_y + m->y) % MM_TILE_Y == 0)
		my_mlx_pixel_put(&game->world, (S_W - MM_S_X - 10) \
		+ m->x, m->y + 10, 0x000000);
	else if (game->map[(m->start_y + m->y) / MM_TILE_Y] \
	[(m->start_x + m->x) / MM_TILE_X] == '1')
		my_mlx_pixel_put(&game->world, (S_W - MM_S_X - 10) \
		+ m->x, m->y + 10, 0x0000FF);
	else if (game->map[(m->start_y + m->y) / MM_TILE_Y] \
	[(m->start_x + m->x) / MM_TILE_X] == '0' \
	|| game->map[(m->start_y + m->y) / MM_TILE_Y][(m->start_x + m->x) / \
	MM_TILE_X] == 'N' || game->map[(m->start_y + m->y) / MM_TILE_Y] \
	[(m->start_x + m->x) / MM_TILE_X] == 'S' || game->map[(m->start_y + m->y) \
	/ MM_TILE_Y][(m->start_x + m->x) / MM_TILE_X] == 'W' || \
	game->map[(m->start_y + m->y) / MM_TILE_Y] \
	[(m->start_x + m->x) / MM_TILE_X] == 'E')
		my_mlx_pixel_put(&game->world, (S_W - MM_S_X - 10) \
		+ m->x, m->y + 10, 0x9e9494);
	else
		my_mlx_pixel_put(&game->world, (S_W - MM_S_X - 10) \
		+ m->x, m->y + 10, 0x000000);
}

void	draw_minimap(t_game *game, t_minimap m)
{
	m.y = -1;
	while (++m.y < MM_S_Y)
	{
		m.x = -1;
		while (++m.x < MM_S_X)
		{
			if ((m.x - m.c_x) * (m.x - m.c_x) + (m.y - m.c_y) * \
			(m.y - m.c_y) <= m.r * m.r)
			{
				if (m.start_x + m.x < 0 || m.start_y + m.y < 0 || \
				(m.start_y + m.y) / MM_TILE_Y < 0 || (m.start_x + m.x) / \
				MM_TILE_X < 0 || (m.start_y + m.y) / MM_TILE_Y > game->y - 1 || \
				(m.start_x + m.x) / MM_TILE_X > game->x - 1 || \
				!game->map[(m.start_y + m.y) / MM_TILE_Y] \
				[(m.start_x + m.x) / MM_TILE_X])
					my_mlx_pixel_put(&game->world, (S_W - MM_S_X - 10) \
					+ m.x, m.y + 10, 0x000000);
				else
					draw_minimap_aux(game, &m);
			}
		}
	}
}

void	minimap(t_game *game)
{
	t_minimap	m;

	m.start_x = (game->player->pos_x) - (MM_S_X / 2);
	m.start_y = (game->player->pos_y) - (MM_S_X / 2);
	m.c_x = MM_S_X / 2;
	m.c_y = MM_S_X / 2;
	m.x = -1;
	m.y = -1;
	m.r = MM_S_X / 2;
	draw_minimap(game, m);
	if (game->torch)
		draw_fov_line_mm(game);
	draw_player(game, ((S_W - MM_S_X) + (MM_S_X / 2)) - 10, \
	(MM_S_Y / 2) + 10, 0xFF0000);
}
