/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:33:01 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/18 15:59:45 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	int			fd;
	char		**map_array;
	t_map		*map;
	t_mapcoord	mapc;

	map = 0;
	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (ft_file_to_lst(fd, &mapc, &map) == -1)
		return (-1);
	map_array = ft_map_array(map, mapc.linem);
	fd = ft_check_map(map_array, &mapc);
	if (fd != 3)
	{
		ft_error_type(fd);
		return (-1);
	}
	if (ft_pathfinding_utils(&mapc, map_array) == -1)
		return (-1);
	show_map(map_array, mapc);
	return (0);
}
