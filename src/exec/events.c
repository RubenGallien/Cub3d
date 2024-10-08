/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:13:17 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/08 14:23:38 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game)
{
	if (game->player->up == 1 && game->map[((game->player->pos_y - 2) / 50)][game->player->pos_x / 50] != '1')
		game->player->pos_y -= 2;
	if (game->player->left == 1 && game->map[game->player->pos_y / 50][((game->player->pos_x - 2) / 50)] != '1')
		game->player->pos_x -= 2;
	if (game->player->down == 1 && game->map[((game->player->pos_y + 10) / 50)][game->player->pos_x / 50] != '1')
		game->player->pos_y += 2;
	if (game->player->right == 1 && game->map[game->player->pos_y / 50][((game->player->pos_x + 10) / 50)] != '1')
		game->player->pos_x += 2;
}

int	on_keypress(int keysym, t_game *game)
{
	// printf("%d\n", keysym);
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
		game->mlx_win = NULL;
	}
	else if (keysym == 119)
	{
		game->player->up = 1;
		game->player->down = 0;
	}
	else if (keysym == 115)
	{
		game->player->down = 1;
		game->player->up = 0;
	}
	else if (keysym == 100)
	{
		game->player->right = 1;
		game->player->left = 0;
	}
	else if (keysym == 97)
	{
		game->player->left = 1;
		game->player->right = 0;
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
	return (0);
}