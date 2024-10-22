/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:32:21 by lvicino           #+#    #+#             */
/*   Updated: 2024/10/22 15:27:33 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_hextoi(char *hex)
{
	static char	base[] = {"0123456789ABCDEF"};
	long		i;
	long		j;
	long		nb;

	nb = 0;
	i = 0;
	while (hex[i] == 32 || (hex[i] >= 9 && hex[i] <= 13))
		i++;
	while ((hex[i] >= '0' && hex[i] <= '9') || \
	((hex[i] >= 'A' && hex[i] <= 'F')))
	{
		j = 0;
		while (base[j] != hex[i])
			j++;
		nb = (nb * 16) + j;
		i++;
	}
	return (nb);
}

void	ft_rgbtohex(unsigned char *rgb, char *hex)
{
	static char	base[] = {"0123456789ABCDEF"};
	int			i;
	int			j;
	int			k;

	i = 6;
	k = 3;
	while (--k >= 0)
	{
		j = 2;
		while (--j >= 0)
		{
			hex[i] = base[rgb[k] % 16];
			rgb[k] /= 16;
			i--;
		}
	}
	return ;
}

int	ft_rgbtoi(char **rgb, int	*colour)
{
	char	hex[7];
	int		tab[3];
	int		i;

	i = -1;
	while (rgb[++i])
	{
		tab[i] = ft_atoi(rgb[i]);
		if (tab[i] > 255)
			return (ft_free_str(rgb, 3), ft_werror(RGB_ER), 0);
	}
	hex[6] = 0;
	ft_rgbtohex((unsigned char *)tab, hex);
	*colour = ft_hextoi(hex);
	return (1);
}

int	get_colour(char *s, int *colour)
{
	char		**rgb;
	int			i;
	int			j;

	rgb = ft_split(s, ',');
	if (!rgb)
		return (0);
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
		return (ft_free_str(rgb, i), 0);
	i = -1;
	while (rgb[++i])
	{
		if (ft_strlen(rgb[i]) > 3)
			return (ft_free_str(rgb, 3), ft_werror(RGB_ER), 0);
		j = -1;
		while (rgb[i][++j])
		{
			if (!ft_isdigit(rgb[i][j]))
				return (ft_free_str(rgb, 3), ft_werror(RGB_ER), 0);
		}
	}
	return (ft_rgbtoi(rgb, colour));
}
