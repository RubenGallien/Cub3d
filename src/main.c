/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:37:51 by rgallien          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/30 18:14:34 by rgallien         ###   ########.fr       */
=======
/*   Updated: 2024/10/02 15:25:02 by lvicino          ###   ########.fr       */
>>>>>>> origin/lvicino
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_game *game)
{
	if (game->mlx_win)
		mlx_pixel_put(game->mlx, game->mlx_win, 300, 150, 0xFF0000);
	return (0);
}

int	on_keypress(int keysym, t_game *game)
{
	(void)game;
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
		game->mlx_win = NULL;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_game		game;
	t_player	player;

	(void)envp;
	parsing(argc, argv);
	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, 1280, 720, "Welcome to Cub3D");
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_hook(game.mlx_win,KeyPress, KeyPressMask, &on_keypress, &game);
	mlx_loop(game.mlx);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
	return (0);
}
