/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:37:51 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/27 22:02:31 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv, char **envp)
{
	t_game		game;
	t_player	player;

	(void)envp; (void)argc; (void)argv;
	if (!parsing(argc, argv, &(game.info)))
		return (1);
	game.tick = 0;
	init_player(&player, game.info.map);
	init_game(&game, &player, game.info.map);
	init_textures(&game);
	mlx_hook(game.mlx_win, DestroyNotify, StructureNotifyMask, &ft_exit, &game);
	mlx_hook(game.mlx_win,KeyPress, KeyPressMask, &on_keypress, &game);
	mlx_hook(game.mlx_win,KeyRelease, KeyReleaseMask, &on_keyrelease, &game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
