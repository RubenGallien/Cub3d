/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:14:12 by rgallien          #+#    #+#             */
/*   Updated: 2024/11/03 19:26:45 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_game *game)
{
	int		i;
	char	*torch[2];

	torch[0] = TORCH_ON;
	torch[1] = TORCH_OFF;
	i = -1;
	while (++i < 4)
		set_data_assets(game, game->info.texture[i], &game->textures.wall[i]);
	i = -1;
	while (++i < 2)
		set_data_assets(game, torch[i], &game->textures.torch[i]);
}

double	get_angle(char c)
{
	if (c == 'N')
		return (90);
	else if (c == 'S')
		return (270);
	else if (c == 'W')
		return (180);
	else if (c == 'E')
		return (0);
	else
		return (18);
}

void	init_game(t_game *game, t_player *player, char **map)
{
	int	i;
	int	j;

	game->map = map;
	i = 0;
	while (game->map && game->map[i])
	{
		j = 0;
		while (game->map && game->map[i][j])
			j++;
		game->x = j;
		i++;
	}
	game->y = i;
	game->torch = 1;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, S_W, S_H, "Welcome to Cub3D");
	game->player = player;
	game->world.img = mlx_new_image(game->mlx, S_W, S_H);
	game->world.pixels = (unsigned char *)mlx_get_data_addr \
	(game->world.img, &game->world.bits_per_pixel, \
	&game->world.line_length, &game->world.endian);
	game->world.height = S_H;
	game->world.width = S_W;
}

void	init_player_aux(t_player *player, char **map, int i, int j)
{
	player->pos_x = j * MM_TILE_X + (MM_TILE_Y / 2);
	player->pos_y = i * MM_TILE_Y + (MM_TILE_Y / 2);
	player->left = 0;
	player->right = 0;
	player->angle = get_angle(map[i][j]);
	player->pdx = cos(to_radiant(player->angle));
	player->pdy = sin(to_radiant(player->angle));
	player->left_r = 0;
	player->right_r = 0;
	player->down = 0;
	player->up = 0;
	player->pos = map[i][j];
}

int	init_player(t_player *player, char **map)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (map && map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] && (map[i][j] == 'N' || map[i][j] == 'S' || \
			map[i][j] == 'E' || map[i][j] == 'W'))
			{
				count++;
				if (count == 1)
					init_player_aux(player, map, i, j);
				if (count > 1)
					return (write(2, "Too much player on the field\n", 30));
			}
		}
	}
	return (0);
}
