/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:37:51 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/04 11:22:36 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv, char **envp)
{
	t_game		game;
	t_player	player;
	t_ray		ray;

	char *map[] = {
    "1111111111",
    "1000000001",
    "10P0000001",
    "1001101001",
    "1001001001",
    "1001001001",
    "1001011001",
    "1000000001",
    "1000000001",
    "1111111111",
    NULL
	};

	(void)argc;
	(void)argv;
	(void)envp;
	// parsing(argc, argv);
	init_player(&player, map);
	init_ray(&ray);
	init_game(&game, &player, &ray, map);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_hook(game.mlx_win,KeyPress, KeyPressMask, &on_keypress, &game);
	mlx_loop(game.mlx);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
	return (0);
}
