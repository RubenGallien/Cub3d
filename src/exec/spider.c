/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:25:57 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/18 16:54:56 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_sprite(t_img asset, t_img *img, int x, int y)
{
	int				i;
	int				j;
	unsigned char	*dst;
	unsigned int	color;

	i = 0;
	while (i < asset.width)
	{
		j = -1;
		while (++j < asset.height)
		{
			color = ((int *)asset.pixels)[j * asset.width + i];
			if (color == 0xFF000000 || (y + j) < 0 || (y + j) > S_H || (x + j) < 0 || (x + j) > S_W)
				continue ;
			dst = img->pixels + ((y + j) * img->line_length + (x + i) \
			* (img->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
		i++;
	}
	return (1);
}

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

void	make_spider(t_game *game)
{
	t_spider	*curr;

	init_spider(game);
	sort_spider(game, &game->spider);
	curr = game->spider;
	while (curr)
	{
		recup_spider_infos(curr, game);
		if (curr->proj_sprite_h >= S_H || curr->proj_sprite_w >= S_W)
		{
			curr = curr->next;
			continue;
		}
		draw_spider(curr, game, curr->sp_screen_x - (curr->proj_sprite_w / 2), curr->sp_screen_y - (curr->proj_sprite_h / 2));
		curr = curr->next;
	}
}
