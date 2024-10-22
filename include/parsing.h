/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:57:14 by lvicino           #+#    #+#             */
/*   Updated: 2024/10/22 15:25:10 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/*Map errors*/
# define CUB_ER "Map description file needs to end with the '.cub' extension\n"
# define WALL_ER "Map must be surrounded by walls\n"
# define COMP_ER "Map can be composed of only these 6 characters: 01NSEWVH\n"
# define SPAWN_ER "Map must contain 1 starting position\n"

/*Element errors*/
# define ID_ER "Unknown element identifier\n"
# define MULTI_DEF_ER "Element defined multiple times\n"
# define RGB_ER "Wrong R,G,B values\n"
# define NDEF_ER "Missing element definition\n"

/*Check map fonctions*/
int		parsing(int ac, char **av, t_map *info);
int		check_texture(t_map *info);
int		get_texture_def(t_map *info, char *str);
int		get_colour(char *s, int *colour);
int		check_map(t_map *info);

/*Utils*/
void	ft_werror(char *error);
void	ft_free_str(char **str, int str_ln);

#endif
