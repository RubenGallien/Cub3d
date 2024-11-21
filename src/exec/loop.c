/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:12:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/14 13:23:53 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	choose_color_door(t_door *curr, t_game *game, int y)
{
	int				i;
	int				j;
	t_img			door;

	j = y / (curr->dist / 64);
	i = curr->offset;
	door = game->textures.door;
	curr->color = ((int *)door.pixels)[j * door.width + i];
	// rgb.r = ((ray->color >> 16) & 0xFF) / 255.0 * ray->perc;
	// rgb.g = ((ray->color >> 8) & 0xFF) / 255.0 * ray->perc;
	// rgb.b = (ray->color & 0xFF) / 255.0 * ray->perc;
	// curr->color = (((int)(rgb.r * 255) & 0xFF) << 16) + (((int)(rgb.g * 255)
	// & 0xFF) << 8) + ((int)(rgb.b * 255) & 0xFF);
	return (curr->color);
}

void	draw_doors(t_door *curr, t_game *game, int start)
{
	int	min;
	int	max;
	int	y;

	min = (S_H - (int)curr->dist) / 2;
	max = (S_H + (int)curr->dist) / 2;
	y = min - 1;
	while (++y < max)
	{
		my_mlx_pixel_put(&game->world, start, y, choose_color_door(curr, game, \
			y - ((S_H - (int)curr->dist) / 2)));
	}
}

void	draw_doors_and_spider(t_game *game, int i, int start)
{
	t_spider	*s_curr;
	t_door		*d_curr;
	s_curr = game->spider;
	d_curr = game->ray[i].doors;
	while (s_curr || d_curr)
	{
		if ((s_curr && d_curr && s_curr->distance > d_curr->dist) \
		|| (s_curr && !d_curr))
		{
			if (s_curr->proj_sprite_h < S_H && s_curr->proj_sprite_w < S_W)
				draw_spider(s_curr, game, s_curr->sp_screen_x - \
				(s_curr->proj_sprite_w / 2), s_curr->sp_screen_y - \
				(s_curr->proj_sprite_h / 2) - 94);
			s_curr = s_curr->next;
		}
		else if ((s_curr && d_curr && s_curr->distance < d_curr->dist) || \
		(!s_curr && d_curr))
		{
			if (d_curr->dist < game->ray[i].wall_height)
				draw_doors(d_curr, game, start);
			d_curr = d_curr->next;
		}
		else
			return ;
	}
}

void	draw_sprite(t_game *game)
{
	int	i;
	int	start;

	start = 0;
	i = -1;
	while (++i < S_W)
	{
		if (game->ray[i].doors && game->ray[i].spider)
		{
			printf("1\n");
			draw_doors_and_spider(game, i, start);
		}
		else if (game->ray[i].doors)
		{
			printf("2\n");
			if (game->ray[i].doors->dist < game->ray[i].wall_height)
				draw_doors(game->ray[i].doors, game, start);
		}
		else if (game->spider)
		{
			// printf("3\n");
			if (game->spider->proj_sprite_h < S_H && game->spider->proj_sprite_w < S_W)
				draw_spider(game->spider, game, game->spider->sp_screen_x - \
				(game->spider->proj_sprite_w / 2), game->spider->sp_screen_y - \
				(game->spider->proj_sprite_h / 2) - 94);
			game->spider = game->spider->next;
		}
		start += S_W / (FOV * RES);
	}
}

int	game_loop(t_game *game)
{
	int	y_torch_start;
	int	x_torch_start;

	x_torch_start = S_W / 8;
	y_torch_start = S_H - (64 * 12);
	mlx_mouse_get_pos(game->mlx, game->mlx_win, &game->mouse.x, &game->mouse.y);
	if (!game->tick && game->mlx_win)
	{
		mouse_ctrl(game);
		move_player(game);
		mlx_mouse_move(game->mlx, game->mlx_win, S_W / 2, S_H / 2);
		fill_rays_infos(game);
		draw_gameplan(game);
		make_spider(game);
		draw_sprite(game);
		minimap(game);
		if (game->torch)
			draw_torch(game, x_torch_start, y_torch_start);
		mlx_put_image_to_window(game->mlx, game->mlx_win, \
		game->world.img, 0, 0);
	}
	game->tick = (game->tick + 1) % (15000 / SPEED);
	return (0);
}
