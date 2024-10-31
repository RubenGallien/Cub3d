/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:13:17 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/31 01:16:41 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game)
{
	if (game->player->left_r == 1)
		game->player->angle += 5;
	if (game->player->right_r == 1)
		game->player->angle -= 5;
	if (game->player->right_r == 1 || game->player->left_r == 1)
	{
		game->player->angle =  (int)game->player->angle % 360;
		if (game->player->angle < 0)
			game->player->angle += 360;
		game->player->pdx = cos(to_radiant(game->player->angle));
		game->player->pdy = sin(to_radiant(game->player->angle));
	}
	if (game->player->up == 1 && game->map[((int)(game->player->pos_y - (3 * game->player->pdy)) / 50)][(int)(game->player->pos_x + 2 * game->player->pdx) / 50] != '1')
	{
		game->player->pos_x += 3 * game->player->pdx;
		game->player->pos_y -= 3 * game->player->pdy;
	}
	if (game->player->down == 1 && game->map[((int)(game->player->pos_y + (3 * game->player->pdy)) / 50)][(int)(game->player->pos_x - 2 * game->player->pdx) / 50] != '1')
	{
		game->player->pos_x -= 3 * game->player->pdx;
		game->player->pos_y += 3 * game->player->pdy;
	}
	if (game->player->left == 1 && game->map[(int)(game->player->pos_y - sin(to_radiant(game->player->angle + 90)) * 3) / 50][((int)(game->player->pos_x + cos(to_radiant(game->player->angle + 90)) * 3) / 50)] != '1')
	{
		game->player->pos_x += cos(to_radiant(game->player->angle + 90)) * 3;
		game->player->pos_y -= sin(to_radiant(game->player->angle + 90)) * 3;
	}
	if (game->player->right == 1 && game->map[(int)(game->player->pos_y + sin(to_radiant(game->player->angle + 90)) * 3) / 50][((int)(game->player->pos_x - cos(to_radiant(game->player->angle + 90)) * 3) / 50)] != '1')
	{
		game->player->pos_x -= cos(to_radiant(game->player->angle + 90)) * 3;
		game->player->pos_y += sin(to_radiant(game->player->angle + 90)) * 3;
	}
}

int	on_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
	{
		ft_exit(game);
		game->mlx_win = NULL;
	}
	else if (keysym == XK_f)
	{
		if (game->torch == 1)
			game->torch = 0;
		else
			game->torch = 1;
	}
	else if (keysym == XK_w)
	{
		game->player->up = 1;
		game->player->down = 0;
	}
	else if (keysym == XK_s)
	{
		game->player->down = 1;
		game->player->up = 0;
	}
	else if (keysym == XK_d)
	{
		game->player->right = 1;
		game->player->left = 0;
	}
	else if (keysym == XK_a)
	{
		game->player->left = 1;
		game->player->right = 0;
	}
	else if (keysym == 65361)
	{
		game->player->left_r = 1;
		game->player->right_r = 0;
	}
	else if (keysym == 65363)
	{
		game->player->right_r = 1;
		game->player->left_r = 0;
	}
	return (0);
}

int	on_keyrelease(int keysym, t_game *game)
{
	if (keysym == 119)
		game->player->up = 0;
	else if (keysym == 115)
		game->player->down = 0;
	else if (keysym == 100)
		game->player->right = 0;
	else if (keysym == 97)
		game->player->left = 0;
	else if (keysym == 65361)
		game->player->left_r = 0;
	else if (keysym == 65363)
		game->player->right_r = 0;
	return (0);
}
