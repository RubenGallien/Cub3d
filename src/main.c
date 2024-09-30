/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:37:51 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/30 18:14:34 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main()
{
	t_game		game;
	t_player	player;

	char *map[] = {
	"1111111111",
	"1000000001",
	"1010010P01",
	"1000000001",
	"1000010001",
	"1000000001",
	"1000000001",
	"1010010101",
	"1000000001",
	"1111111111",
	NULL
	};
	init_player(&player, map);
	game.map = map;
	game.player = &player;
	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, 1280, 720, "Welcome to Cub3D");
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_hook(game.mlx_win,KeyPress, KeyPressMask, &on_keypress, &game);
	mlx_loop(game.mlx);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
	return (0);
}
