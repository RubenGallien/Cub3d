/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:31:25 by lvicino           #+#    #+#             */
/*   Updated: 2024/10/22 15:00:24 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_seed(t_map *info, char *str)
{
	char	*tmp;

	info->y_max++;
	tmp = info->seed;
	info->seed = ft_strjoin(info->seed, str);
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
		while ((str[i] >= 9 && 13 <= str[i]) || str[i] == 32 || str[i] == '\n')
			i++;
		if (str && ft_isalpha(str[i]) && !get_texture_def(info, str))
			return (free(str), 0);
		else if (str && str[i] == '1' && !get_seed(info, str)) //! might not need to check == '1'
			return (free(str), 0);
		free(str);
		str = get_next_line(fd);
	}
	return (1);
}

int	check_description_file(char *map_file, t_map *info)
{
	char	*str;
	int		fd;
	int		i;

	info->texture = malloc(sizeof(char *) * (5));
	if (!info->texture)
		return (0);
	i = -1;
	while (++i < 5)
		info->texture[i] = NULL;
	info->colour[0] = -1;
	info->colour[1] = -1;
	str = ft_strrchr(map_file, '.');
	if (!str || ft_strncmp(str, ".cub", 5))
		return (ft_free_str(info->texture, 5), ft_werror(CUB_ER), 0);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (ft_free_str(info->texture, 5), perror(map_file), 0);
	else if (!get_info(info, fd) || !check_texture(info) || !check_map(info))
		return (ft_free_str(info->texture, 5), close(fd), 0);
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
