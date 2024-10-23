/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:31:25 by lvicino           #+#    #+#             */
/*   Updated: 2024/10/23 18:44:02 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_seed(t_map *info, char *str)
{
	char	*tmp;

	info->y_max++;
	tmp = info->seed;
	if (!info->seed)
		info->seed = ft_strdup(str);
	else
		info->seed = ft_strjoin(info->seed, str);
	if (tmp)
		free(tmp);
	if (!info->seed)
		return (0);
	return (1);
}

int	get_info(t_map *info, int fd)
{
	char	*str;
	int		i;

	str = get_next_line(fd);
	while (str)
	{
		i = 0;
		while (!info->seed && \
		((9 <= str[i] && str[i] <= 13) || str[i] == 32 || str[i] == '\n'))
			i++;
		(void)info;
		if (!info->seed && str && ft_isalpha(str[i]))
		{
			if (!get_texture_def(info, str))
				return (0);
		}
		else if (str && str[i])
		{
			if (!get_seed(info, str))
				return (0);
		}
		free(str);
		str = get_next_line(fd);
	}
	return (1);
}

void	init_info(t_map *info)
{
	int		i;

	i = -1;
	while (++i < 5)
		info->texture[i] = NULL;
	info->colour[0] = -1;
	info->colour[1] = -1;
	info->seed = NULL;
	info->map = NULL;
}

int	check_description_file(char *map_file, t_map *info)
{
	char	*str;
	int		fd;

	info->texture = malloc(sizeof(char *) * (5));
	if (!info->texture)
		return (0);
	init_info(info);
	str = ft_strrchr(map_file, '.');
	if (!str || ft_strncmp(str, ".cub", 5))
		return (ft_free_info(info), ft_werror(CUB_ER), 0);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (ft_free_info(info), ft_werror(NULL), perror(map_file), 0);
	else if (!get_info(info, fd) || !check_texture(info) || !check_map(info))
		return (ft_free_info(info), close(fd), 0);
	return (close(fd), 1);
}

int	parsing(int ac, char **av, t_map *info)
{
	if (ac == 1)
		ft_putstr_fd("Enter a map name\n", 2);
	else if (ac > 2)
		ft_putstr_fd("Too many arguments\n", 2);
	else if (check_description_file(av[1], info))
		return (1);
	return (0);
}
