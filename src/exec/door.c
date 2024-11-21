/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:15:29 by lvicino           #+#    #+#             */
/*   Updated: 2024/11/20 23:40:16 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_door(t_door *door)
{
	t_door	*tmp;

	while (door)
	{
		tmp = door->next;
		free(door);
		door = tmp;
	}
}

t_door	*get_door(int *n, t_game *game, int i, t_door *node)
{
	t_door	*door;

	(*n)++;
	door = malloc(sizeof(t_door));
	if (!door)
		return (free_door(node), NULL);
	door->next = NULL;
	door->dist = found_distance(game->player->pos_x, \
	game->player->pos_y, game->ray[i].rx, game->ray[i].ry);
	door->dist -= 32;
	if (node)
		door->next = node;
	return (door);
}

void	check_door_h(t_game *game, int i)
{
	if (game->ray[i].mx >= 0 && game->ray[i].my >= 0 \
		&& game->ray[i].mx < game->info.ln_x && game->ray[i].my < \
		game->info.ln_y && (game->map[game->ray[i].my][game->ray[i].mx] == 'V' \
		|| game->map[game->ray[i].my][game->ray[i].mx] == 'H'))
	{
		game->ray[i].doors = \
		get_door(&game->ray[i].n_door, game, i, game->ray[i].doors);
		game->ray[i].doors->offset = (int)game->ray[i].rx % 64;
	}
}

void	check_door_v(t_game *game, int i, t_door *tmp, int n)
{
	if (game->ray[i].mx >= 0 && game->ray[i].my >= 0 \
		&& game->ray[i].mx < game->info.ln_x && game->ray[i].my < \
		game->info.ln_y && (game->map[game->ray[i].my][game->ray[i].mx] == 'V' \
		|| game->map[game->ray[i].my][game->ray[i].mx] == 'H'))
	{
		tmp = get_door(&n, game, i, tmp);
		tmp->offset = (int)game->ray[i].ry % 64;
	}
}
