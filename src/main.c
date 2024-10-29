/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:37:51 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/29 13:47:22 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv, char **envp)
{
	t_game		game;
	t_player	player;

	(void)envp;
	if (!parsing(argc, argv, &(game.info)))
		return (1);
	game.tick = 0;
	init_player(&player, game.info.map);
	init_game(&game, &player, game.info.map);
	mlx_hook(game.mlx_win,KeyPress, KeyPressMask, &on_keypress, &game);
	mlx_hook(game.mlx_win,KeyRelease, KeyReleaseMask, &on_keyrelease, &game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
	ft_free_info(&(game.info));
	return (0);
}
