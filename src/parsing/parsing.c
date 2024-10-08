/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:31:25 by lvicino           #+#    #+#             */
/*   Updated: 2024/10/07 14:38:29 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_dot_cub(char *map_file)
{
	char	*str;

	str = ft_strrchr(map_file, '.');
	if (!str || ft_strncmp(str, ".cub", 5))
		return (ft_putstr_fd(CUB_ER, 2), 0);
	return (1);
}

int	check_description_file(char *map_file, t_game *game)
{
	int		fd;

	if (!is_dot_cub(map_file))
		return (0);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (perror(map_file), 0);
	else if (!check_texture(game) || !check_map(game))
		return (0);
	return (1);
}

int	parsing(int ac, char **av, t_game *game)
{
	if (ac == 1)
		ft_putstr_fd("Enter a map name\n", 2);
	else if (ac > 2)
		ft_putstr_fd("Too many arguments\n", 2);
	else if (check_description_file(av[1], game))
		return (1);
	return (0);
}
