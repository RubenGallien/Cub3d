/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:58:50 by rgallien          #+#    #+#             */
/*   Updated: 2024/10/29 12:33:29 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_free_img(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(game->mlx, game->textures.wall[i].img);
	return (0);
}

int	ft_exit(t_game *game)
{
	ft_free_img(game);
	ft_free_info(&(game->info));
	mlx_destroy_image(game->mlx, game->world.img);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	return (exit(0), 0);
}