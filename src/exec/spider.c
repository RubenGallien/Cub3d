/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:25:57 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/21 14:09:47 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_add_spider(t_spider **lst, t_spider *new)
{
	t_spider	*node;

	if (!lst || !new)
		return ;
	else if (!*lst)
	{
		*lst = new;
		return ;
	}
	node = *lst;
	while (node->next)
		node = node->next;
	node->next = new;
	new->prev = node;
}

t_spider	*ft_new_spider(int i, int j, t_game *game)
{
	t_spider	*new_node;

	new_node = malloc(sizeof(t_spider));
	if (!new_node)
		return (NULL);
	new_node->x = i * (MM_S_X / MM_SIZE) + ((MM_S_Y / MM_SIZE) / 2);
	new_node->y = j * (MM_S_Y / MM_SIZE) + ((MM_S_Y / MM_SIZE) / 2);
	new_node->distance = (game->player->pos_x - new_node->x) * \
	(game->player->pos_x - new_node->x) + (game->player->pos_y - new_node->y) * \
	(game->player->pos_y - new_node->y);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	init_spider(t_game *game)
{
	int			i;
	int			j;
	t_spider	*spider;

	game->spider = NULL;
	j = -1;
	while (game->map[++j])
	{
		i = -1;
		while (game->map[j][++i])
		{
			if (game->map[j][i] == 'A')
			{
				spider = ft_new_spider(i, j, game);
				ft_add_spider(&game->spider, spider);
			}
		}
	}
}

void	sort_spider(t_spider **spider)
{
	t_spider	*curr;
	t_spider	*next;

	curr = *spider;
	while (curr && curr->next)
	{
		next = curr->next;
		if (curr->distance < next->distance)
		{
			if (curr->prev)
				curr->prev->next = next;
			else
				*spider = next;
			next->prev = curr->prev;
			curr->prev = next;
			curr->next = next->next;
			next->next = curr;
			curr = *spider;
		}
		else
			curr = curr->next;
	}
}

void	make_spider(t_game *game)
{
	t_spider	*curr;

	if (game->spider)
		free_spider(game->spider);
	init_spider(game);
	sort_spider(&game->spider);
	curr = game->spider;
	while (curr)
	{
		recup_spider_infos(curr, game);
		if (curr->proj_sprite_h >= S_H || curr->proj_sprite_w >= S_W)
		{
			curr = curr->next;
			continue ;
		}
		draw_spider(curr, game, curr->sp_screen_x - (curr->proj_sprite_w / 2), \
		curr->sp_screen_y - (curr->proj_sprite_h / 2) - 94);
		curr = curr->next;
	}
}
