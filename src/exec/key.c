/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 03:20:27 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/02 16:03:51 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	else
		on_keypress_aux(keysym, game);
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
