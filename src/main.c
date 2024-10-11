/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:37:51 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/10 19:23:49 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv, char **envp)
{
	t_game		game;
	t_player	player;
	t_ray		ray;
	char		**map;

	map = malloc(sizeof(char *) * (10 + 1));
	map[0] = ft_strdup("11111111111111111");
	map[1] = ft_strdup("10000000000000001");
	map[2] = ft_strdup("100000N0011111111");
	map[3] = ft_strdup("1001101001");
	map[4] = ft_strdup("100100100111111");
	map[5] = ft_strdup("100001001101001");
	map[6] = ft_strdup("1001011001111111111");
	map[7] = ft_strdup("1000100000000000001");
	map[8] = ft_strdup("1000000000000000001");
	map[9] = ft_strdup("1111111111111111111");
	map[10] = NULL;
	(void)argc;
	(void)argv;
	(void)envp;
	// parsing(argc, argv);
	init_player(&player, map);
	init_game(&game, &player, &ray, map);
	mlx_hook(game.mlx_win,KeyPress, KeyPressMask, &on_keypress, &game);
	mlx_hook(game.mlx_win,KeyRelease, KeyReleaseMask, &on_keyrelease, &game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
	return (0);
}
