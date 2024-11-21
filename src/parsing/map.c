/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:14:47 by lvicino           #+#    #+#             */
/*   Updated: 2024/11/21 15:31:45 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_closed(char **map, int ln_x, int ln_y)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != ' ' && \
			map[y][x] != 'N' && map[y][x] != 'S' && map[y][x] != 'E' && \
			map[y][x] != 'W' && map[y][x] != 'D' \
			&& map[y][x] != 'A')
				return (ft_werror(COMP_ER), 0);
			else if ((map[y][x] == '0' || map[y][x] == 'D' || \
			map[y][x] == 'A' || map[y][x] == 'N' || map[y][x] == 'S' || \
			map[y][x] == 'E' || map[y][x] == 'W') && \
			(!y || y == ln_y - 1 || !x || x == ln_x - 1 || \
			map[y - 1][x] == ' ' || map[y + 1][x] == ' ' || \
			map[y][x - 1] == ' ' || map[y][x + 1] == ' '))
				return (ft_werror(WALL_ER), 0);
		}
	}
	return (1);
}

int	shape_map(t_map *info)
{
	char	*tmp;
	int		ln;
	int		i;

	i = -1;
	while (info->map[++i])
	{
		ln = ft_strlen(info->map[i]);
		if (ln < info->ln_x)
		{
			tmp = info->map[i];
			info->map[i] = malloc(sizeof(char) * (info->ln_x + 1));
			if (!info->map[i])
				return (0);
			info->map[i][info->ln_x] = 0;
			ft_strlcpy(info->map[i], tmp, ln + 1);
			free(tmp);
		}
		while (ln < info->ln_x)
			info->map[i][ln++] = 32;
	}
	return (1);
}

int	check_map(t_map *info)
{
	info->map = ft_split(info->seed, '\n');
	if (!info->map || !shape_map(info) || \
	!is_closed(info->map, info->ln_x, info->ln_y))
		return (ft_free_info(info), 0);
	return (1);
}
