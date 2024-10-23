/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:16:08 by lvicino           #+#    #+#             */
/*   Updated: 2024/10/23 18:59:10 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_texture(t_map *info)
{
	int	i;
	int	fd;

	i = -1;
	while (++i < 4)
	{
		if (info->texture[i])
			fd = open(info->texture[i], O_RDONLY);
		else
			return (ft_werror(NDEF_ER), 0);
		if (fd < 0)
			return (ft_werror(NULL), perror(info->texture[i]), 0);
		close(fd);
	}
	i = -1;
	while (++i < 2)
	{
		if (info->colour < 0)
			return (ft_werror(NDEF_ER), 0);
	}
	return (1);
}

int	get_texture_def(t_map *info, char *str)
{
	const char	*list[] = {"NO", "SO", "EA", "WE", "F", "C"};
	char		**tmp;
	int			i;

	tmp = ft_split(str, 32);
	if (!tmp)
		return (0);
	i = 0;
	while (tmp[i])
		i++;
	if (i != 2)
		return (ft_free_str(tmp, i), ft_werror(ID_ER), 0);
	i = -1;
	while (list[++i])
	{
		if (!ft_strncmp(tmp[0], list[i], ft_strlen(list[i]) + 1))
		{
			if (0 <= i && i <= 3 && !info->texture[i])
			{
				info->texture[i] = ft_strtrim(tmp[1], "\n");
				return (ft_free_str(tmp, 3), 1);
			}
			else if (4 <= i && i <= 5 && info->colour[i - 4] < 0)
			{
				if (get_colour(ft_strtrim(tmp[1], "\n"), &(info->colour[i - 4])))
					return (ft_free_str(tmp, 3), 1);
				return (ft_free_str(tmp, 3), 0);
			}
			return (ft_free_str(tmp, 3), ft_werror(MULTI_DEF_ER), 0);
		}
	}
	return (ft_free_str(tmp, 3), ft_werror(ID_ER), 0);
}
