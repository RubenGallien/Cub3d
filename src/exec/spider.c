/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:25:57 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/12 13:46:30 by rgallien         ###   ########.fr       */
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
		return;
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

	new_node = (t_spider *)malloc(sizeof(t_spider));
	if (!new_node)
		return (NULL);
	new_node->x = i * (MM_S_X / MM_SIZE) + ((MM_S_Y / MM_SIZE) / 2);
	new_node->y = j * (MM_S_Y / MM_SIZE) + ((MM_S_Y / MM_SIZE) / 2);
	new_node->distance = (game->player->pos_x - new_node->x) * \
	(game->player->pos_x - new_node->x) + (game->player->pos_y - new_node->y) * \
	(game->player->pos_y- new_node->y);
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

void	sort_spider(t_game *game, t_spider **spider)
{
	t_spider	*curr;
	t_spider	*next;

	(void)game;
	curr = *spider;
	while (curr)
	{
		next = curr->next;
		if (curr && next && curr->distance < next->distance)
		{
			if (!curr->prev)
			{
				*spider = next;
				next->prev = NULL;
			}
			else
			{
				curr->prev->next = next;
				next->prev = curr->prev;
			}
			curr->next =  next->next;
			next->next = curr;
			curr->prev = next;
			curr = *spider;
		}
		else
			curr = curr->next;
	}
}

void	draw_spider(t_game *game)
{
	sort_spider(game, &game->spider);
	// projection;
	// scale;
	// draw;
}
