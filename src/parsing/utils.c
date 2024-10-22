/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 00:10:14 by lvicino           #+#    #+#             */
/*   Updated: 2024/10/16 17:02:19 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_werror(char *error)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
}

void	ft_free_str(char **str, int str_ln)
{
	while (--str_ln >= 0 && str)
	{
		if (str[str_ln])
			free(str[str_ln]);
	}
	if (str)
		free(str);
}
