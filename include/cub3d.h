/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:39:37 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/29 17:01:04 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <mlx.h>
# include <stdio.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <time.h>
# include <sys/time.h>
# include <math.h>
# include <string.h>

typedef struct s_game
{
	void	*mlx;
	void	*mlx_win;
}			t_game;

#endif