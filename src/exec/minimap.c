/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:18:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/21 15:34:32 by lvicino          ###   ########.fr       */
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

void	draw_player(t_game *game, int start_x, int start_y, t_minimap m)
{
	int	i;

	m.y = -11;
	while (++m.y < MM_S_Y + 11)
	{
		m.x = -11;
		while (++m.x < MM_S_X + 11)
		{
			if ((m.x - m.c_x) * (m.x - m.c_x) + (m.y - m.c_y) * \
			(m.y - m.c_y) >= 160 * 160 && \
			(m.x - m.c_x) * (m.x - m.c_x) + (m.y - m.c_y) * \
			(m.y - m.c_y) <= 165 * 165)
				my_mlx_pixel_put(&game->world, (S_W - MM_S_X - 10) \
				+ m.x, m.y + 10, 0x717178);
			else if ((m.x - m.c_x) * (m.x - m.c_x) + (m.y - m.c_y) * \
			(m.y - m.c_y) < 5 * 5)
				my_mlx_pixel_put(&game->world, (S_W - MM_S_X - 10) \
				+ m.x, m.y + 10, 0xFF0000);
		}
	}
	i = -1;
	while (++i < 8)
		my_mlx_pixel_put(&game->world, start_x + (i * game->player->pdx), \
		start_y - (i * game->player->pdy), 0xFF0000);
}

void	draw_minimap_aux(t_game *game, t_minimap *m)
{
	int	tile_x;
	int	tile_y;

	tile_x = MM_S_X / MM_SIZE;
	tile_y = MM_S_Y / MM_SIZE;
	if ((m->start_x + m->x) % tile_x == 0 || (m->start_y + m->y) % tile_y == 0)
		my_mlx_pixel_put(&game->world, (S_W - MM_S_X - 10) \
		+ m->x, m->y + 10, 0xc6c7cf);
	else if (game->map[(m->start_y + m->y) / tile_y] \
	[(m->start_x + m->x) / tile_x] == '1')
		my_mlx_pixel_put(&game->world, (S_W - MM_S_X - 10) \
		+ m->x, m->y + 10, 0x47474a);
	else if (game->map[(m->start_y + m->y) / tile_y] \
	[(m->start_x + m->x) / tile_x] == '0' \
	|| game->map[(m->start_y + m->y) / tile_y][(m->start_x + m->x) / \
	tile_x] == 'N' || game->map[(m->start_y + m->y) / tile_y] \
	[(m->start_x + m->x) / tile_x] == 'S' || game->map[(m->start_y + m->y) \
	/ tile_y][(m->start_x + m->x) / tile_x] == 'W' || \
	game->map[(m->start_y + m->y) / tile_y] \
	[(m->start_x + m->x) / tile_x] == 'E')
		my_mlx_pixel_put(&game->world, (S_W - MM_S_X - 10) \
		+ m->x, m->y + 10, 0xaba9a2);
	else
		draw_minimap_obj(game, m);
}

void	draw_minimap(t_game *game, t_minimap m, int tile_x, int tile_y)
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
				(m.start_y + m.y) / tile_y < 0 || (m.start_x + m.x) / \
				tile_x < 0 || (m.start_y + m.y) / \
				tile_y > game->info.ln_y - 1 || \
				(m.start_x + m.x) / tile_x > game->info.ln_x - 1 || \
				!game->map[(m.start_y + m.y) / tile_y] \
				[(m.start_x + m.x) / tile_x] || game->map[(m.start_y + m.y) \
				/ tile_y][(m.start_x + m.x) / tile_x] == ' ')
					my_mlx_pixel_put(&game->world, (S_W - MM_S_X - 10) \
					+ m.x, m.y + 10, 0xc6c7cf);
				else
					draw_minimap_aux(game, &m);
			}
		}
	}
}

void	minimap(t_game *game)
{
	t_minimap	m;
	int			tile_x;
	int			tile_y;

	tile_x = MM_S_X / MM_SIZE;
	tile_y = MM_S_Y / MM_SIZE;
	m.start_x = (game->player->pos_x) - (MM_S_X / 2);
	m.start_y = (game->player->pos_y) - (MM_S_X / 2);
	m.c_x = MM_S_X / 2;
	m.c_y = MM_S_X / 2;
	m.x = -1;
	m.y = -1;
	m.r = MM_S_X / 2;
	draw_minimap(game, m, tile_x, tile_y);
	if (game->torch)
		draw_fov_line_mm(game);
	draw_player(game, ((S_W - MM_S_X) + (MM_S_X / 2)) - 10, \
	(MM_S_Y / 2) + 10, m);
}
