/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:16:08 by lvicino           #+#    #+#             */
/*   Updated: 2024/11/19 11:08:36 by lvicino          ###   ########.fr       */
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
	if ((info->colour[0] < 0 && !info->texture_f) || \
	(info->colour[1] < 0 && !info->texture_c))
		return (ft_werror(NDEF_ER), 0);
	return (1);
}

int	bigger(char *s1, char *s2)
{
	int	a;
	int	b;

	a = ft_strlen(s1);
	b = ft_strlen(s2);
	if (a > b)
		return (a);
	return (b);
}

int	fill_texture_tab(int i, char **tmp, t_map *info)
{
	char *str;

	if (0 <= i && i <= 3 && !info->texture[i])
	{
		info->texture[i] = ft_strtrim(tmp[1], "\n");
		return (ft_free_str(tmp, 3), 1);
	}
	else if (4 <= i && i <= 5 && info->colour[i - 4] < 0)
	{
		str = ft_strrchr(tmp[1], '.');
		if (str && !ft_strncmp(str, ".xpm\n", 6))
		{
			if (i == 4)
				info->texture_f = ft_strtrim(tmp[1], "\n");
			else
				info->texture_c = ft_strtrim(tmp[1], "\n");
			return (ft_free_str(tmp, 3), 1);
		}
		else if (get_colour(ft_strtrim(tmp[1], "\n"), &(info->colour[i - 4])))
			return (ft_free_str(tmp, 3), 1);
		return (ft_free_str(tmp, 3), 0);
	}
	return (ft_free_str(tmp, 3), ft_werror(MULTI_DEF_ER), 0);
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
			if (fill_texture_tab(i, tmp, info))
				return (1);
			else
				return (0);
		}
	}
	return (ft_free_str(tmp, 3), ft_werror(ID_ER), 0);
}
