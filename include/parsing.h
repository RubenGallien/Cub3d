/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:57:14 by lvicino           #+#    #+#             */
/*   Updated: 2024/10/03 15:30:37 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/*Map errors*/
# define CUB_ER "Map description file needs to end with the '.cub' extension\n"
# define WALL_ER "Map must be surrounded by walls\n"
# define COMP_ER "Map can be composed of only these 6 characters: 01CEPM\n" //! subject to change
# define SPAWN_ER "Map must contain 1 starting position\n"
# define SIZE_ER "Map max size is 48x27\n"

/*Check map fonctions*/
int	parsing(int ac, char **av);
int	check_texture();
int	check_map();

#endif
