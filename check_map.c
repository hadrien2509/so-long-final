/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:36:28 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/16 18:30:56 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check_map_items(char **map_array, int x, int y, t_mapcoord *mapc)
{
	static int	player_check;
	static int	exit_check;

	if (map_array[y][x] == 'P')
	{
		if (player_check == 2 || player_check == 4)
			player_check = 4;
		else
			player_check = 2;
		mapc->player_x = x;
		mapc->player_y = y;
	}
	else if (map_array[y][x] == 'E')
	{
		if (exit_check == 1 || exit_check == 5)
			exit_check = 5;
		else
			exit_check = 1;
	}
	else if (map_array[y][x] == 'C')
		mapc->nbr_of_coins++;
	else if (map_array[y][x] != '0' && map_array[y][x] != '1')
		return (-3);
	mapc->check_items = player_check + exit_check;
	return (mapc->check_items);
}

int	ft_check_map(char **map_array, t_mapcoord *mapc)
{
	int	x;
	int	y;
	int	check_items;

	mapc->nbr_of_coins = 0;
	y = 0;
	while (y < mapc->linem)
	{
		x = 0;
		while (x < mapc->colm)
		{
			check_items = ft_check_map_items(map_array, x, y, mapc);
			if (check_items == -3 || check_items == 9)
				return (check_items);
			if ((y == 0 || y == mapc->linem - 1) && map_array[y][x] != '1')
				return (-4);
			if ((x == 0 || x == mapc->colm - 1) && map_array[y][x] != '1')
				return (-4);
			x++;
		}
		y++;
	}
	if (mapc->nbr_of_coins == 0)
		return (-5);
	return (check_items);
}

void	ft_error_type(int error_type)
{
	if (error_type == 2 || error_type == 4)
		ft_printf("The map must have an exit.\n");
	if (error_type == 1 || error_type == 5)
		ft_printf("The map must have a player starting positon.\n");
	if (error_type == 0)
		ft_printf("The map must have a player starting positon and an exit.\n");
	if (error_type == 7)
		ft_printf("The map must have only 1 exit.\n");
	if (error_type == 6)
		ft_printf("The map must have only 1 player starting position.\n");
	if (error_type == 9)
		ft_printf("The map must have only 1 player position and 1 exit.\n");
	if (error_type == -3)
		ft_printf("Invalid characters in the map.\n");
	if (error_type == -4)
		ft_printf("The map must be delimited by walls.\n");
	if (error_type == -5)
		ft_printf("The map must have at least 1 coin.\n");
}
