/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:37:51 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/18 14:17:59 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_spider(t_game *game)
{
	t_spider	*current;

	current = game->spider;
	while (current)
	{
		printf("x = %f\n", current->x);
		printf("y = %f\n", current->y);
		printf("distance = %f\n\n", current->distance);
		current = current->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_game		game;
	t_player	player;

	ft_memset(&game, 0, sizeof(t_game));
	(void)envp;
	(void)argc;
	(void)argv;
	if (!parsing(argc, argv, &(game.info)))
		return (1);
	if (init_player(&player, game.info.map))
		ft_exit(&game);
	init_game(&game, &player, game.info.map);
	init_textures(&game);
	// mlx_mouse_hide(game.mlx, game.mlx_win);
	mlx_mouse_move(game.mlx, game.mlx_win, S_W / 2, S_H / 2);
	mlx_hook(game.mlx_win, DestroyNotify, StructureNotifyMask, &ft_exit, &game);
	mlx_hook(game.mlx_win, KeyPress, KeyPressMask, &on_keypress, &game);
	mlx_hook(game.mlx_win, KeyRelease, KeyReleaseMask, &on_keyrelease, &game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
