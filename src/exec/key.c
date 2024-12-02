/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 03:20:27 by rgallien          #+#    #+#             */
/*   Updated: 2024/12/02 12:29:52 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pause_game(t_game *game)
{
	if (game->lock == 1)
		game->lock = 0;
	else
	{
		mlx_mouse_move(game->mlx, game->mlx_win, S_W / 2, S_H / 2);
		game->lock = 1;
	}
	return (0);
}

void	on_keypress_aux(int keysym, t_game *game)
{
	if (keysym == XK_s)
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
	else if (keysym == XK_Left)
	{
		game->player->left_r = 1;
		game->player->right_r = 0;
	}
	else if (keysym == XK_Right)
	{
		game->player->right_r = 1;
		game->player->left_r = 0;
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
	else if (keysym == XK_e)
		open_door(game);
	else if (keysym == XK_w)
	{
		game->player->up = 1;
		game->player->down = 0;
	}
	else if (keysym == XK_p)
		pause_game(game);
	else
		on_keypress_aux(keysym, game);
	return (0);
}

int	on_keyrelease(int keysym, t_game *game)
{
	if (keysym == XK_w)
		game->player->up = 0;
	else if (keysym == XK_s)
		game->player->down = 0;
	else if (keysym == XK_d)
		game->player->right = 0;
	else if (keysym == XK_a)
		game->player->left = 0;
	else if (keysym == XK_Left)
		game->player->left_r = 0;
	else if (keysym == XK_Right)
		game->player->right_r = 0;
	return (0);
}
