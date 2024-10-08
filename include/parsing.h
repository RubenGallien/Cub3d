/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:57:14 by lvicino           #+#    #+#             */
/*   Updated: 2024/10/07 14:30:00 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	int		f[3];
	int		c[3];
	char	*seed;
	char	**map;
	int		x_max;
	int		y_max;
}			t_map;

/*Map errors*/
# define CUB_ER "Map description file needs to end with the '.cub' extension\n"
# define WALL_ER "Map must be surrounded by walls\n"
# define COMP_ER "Map can be composed of only these 6 characters: 01CEPM\n" //! subject to change
# define SPAWN_ER "Map must contain 1 starting position\n"
# define SIZE_ER "Map max size is 48x27\n"

/*Check map fonctions*/
int	parsing(int ac, char **av, t_game *game);
int	check_texture(t_game *game);
int	check_map(t_game *game);

#endif
