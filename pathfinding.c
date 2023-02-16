/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:33:40 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/16 13:35:43 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**ft_arraydup(char **map_array, t_mapcoord *mapc)
{
	int		i;
	int		j;
	char	**map_array_copy;

	i = 0;
	map_array_copy = malloc(sizeof(char*) * mapc->linem);
	if (!map_array_copy)
		return (NULL);
	while (i < mapc->linem)
	{	
		map_array_copy[i] = malloc(sizeof(char) * mapc->colm);
		j = mapc->colm - 1;
		while (j >= 0)
		{
			map_array_copy[i][j] = map_array[i][j];
			j--;
		}
		i++;
	}
	mapc->coin_collect = 0;
	return (map_array_copy);
}

void	ft_free_array(t_mapcoord *mapc, char **map_array_dup)
{
	int		i;

	i = 0;
	while (i < mapc->linem)
	{
		free(map_array_dup[i]);
		i++;
	}
	free(map_array_dup);
}

int	ft_pathfinding(char **map_array, int y, int x, t_mapcoord *mapc)
{
	if (map_array[y][x] == 'E')
		mapc->exit_found = 1;
	if (map_array[y][x] == 'C')
		mapc->coin_collect++;
	if (mapc->coin_collect == mapc->nbr_of_coins && mapc->exit_found)
		return (1);
	if (map_array[y][x] != 'E')
		map_array[y][x] = '1';
	if (map_array[y + 1][x] != '1')
		if (ft_pathfinding(map_array, y + 1, x, mapc) == 1)
			return (1);
	if (map_array[y][x + 1] != '1')
		if (ft_pathfinding(map_array, y, x + 1, mapc) == 1)
			return (1);
	if (map_array[y - 1][x] != '1')
		if (ft_pathfinding(map_array, y - 1, x, mapc) == 1)
			return (1);
	if (map_array[y][x - 1] != '1')
		if (ft_pathfinding(map_array, y, x - 1, mapc) == 1)
			return (1);
	return (0);
}

int	ft_pathfinding_utils(t_mapcoord *mapc, char **map_array)
{
	char	**map_arr_dup;

	map_arr_dup = ft_arraydup(map_array, mapc);
	if (map_arr_dup == NULL)
		return (-1);
	mapc->coin_collect = 0;
	if (ft_pathfinding(map_arr_dup, mapc->player_y, mapc->player_x, mapc) == 0)
	{
		ft_printf("No valid path in the map.\n");
		return (-1);
	}
	ft_free_array(mapc, map_arr_dup);
	return (0);
}