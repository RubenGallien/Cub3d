/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:58:50 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/29 16:11:10 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_free_img(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (game->textures.wall[i].img)
			mlx_destroy_image(game->mlx, game->textures.wall[i].img);
	}
	i = -1;
	while (++i < 2)
	{
		if (game->textures.torch[i].img)
			mlx_destroy_image(game->mlx, game->textures.torch[i].img);
	}
	if (game->textures.floor.img)
		mlx_destroy_image(game->mlx, game->textures.floor.img);
	if (game->textures.ceiling.img)
		mlx_destroy_image(game->mlx, game->textures.ceiling.img);
	if (game->textures.door.img)
		mlx_destroy_image(game->mlx, game->textures.door.img);
	if (game->textures.spider.img)
		mlx_destroy_image(game->mlx, game->textures.spider.img);
	if (game->textures.pause.img)
		mlx_destroy_image(game->mlx, game->textures.pause.img);
	return (0);
}

int	ft_exit(t_game *game)
{
	if (game->mlx)
	{
		ft_free_img(game);
		mlx_destroy_image(game->mlx, game->world.img);
		mlx_destroy_window(game->mlx, game->mlx_win);
		mlx_destroy_display(game->mlx);
		free_spider(game->spider);
		free(game->mlx);
	}
	if (game && &(game->info) != NULL)
		ft_free_info(&(game->info));
	return (exit(0), 0);
}
