/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:49:49 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/16 13:50:31 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_check_map_size(t_mapcoord *mapc)
{
	if (mapc->linem > 40)
	{
		ft_printf("Error. The map must not have more than 40 lines\n");
		return (-1);
	}
	if (mapc->linem < 3)
	{
		ft_printf("Error. The map must have at least 3 lines\n");
		return (-1);
	}
	if (mapc->linem * mapc->colm < 15)
	{
		ft_printf("Error. The map is too small to launch a game in it\n");
		return (-1);
	}
	return (0);
}

int	ft_check_colm(t_mapcoord *mapc, t_map *new)
{	
	if (!new)
		return (-1);
	mapc->linem = 0;
	mapc->colm = ft_strlen(new->line);
	if (mapc->colm > 50)
	{
		ft_printf("Error. The map may have 50 columns at most\n");
		return (-1);
	}
	if (mapc->colm < 3)
	{
		ft_printf("Error. The map must have 3 lines or more\n");
		return (-1);
	}
	return (0);
}

int	ft_file_to_lst(int fd, t_mapcoord *mapc, t_map **map)
{
	int		nbr_of_columns;
	t_map	*new;

	new = ft_lstnew(fd);
	ft_check_colm(mapc, new);
	while (new->line && mapc->linem < 40)
	{
		ft_lstadd_back(&map, new);
		(mapc->linem)++;
		new = ft_lstnew(fd);
		if (!new)
			return (-1);
		nbr_of_columns = ft_strlen(new->line);
		if (mapc->colm != nbr_of_columns && new->line)
		{
			ft_printf("Error. The map must be rectangular\n");
			return (-1);
		}
	}
	ft_check_map_size(mapc);
	close(fd);
	return (0);
}

char	**ft_map_array(t_map *map, int linem)
{
	char	**map_array;
	int		i;
	t_map	*trace;

	map_array = malloc(sizeof(char *) * (linem));
	if (!map_array)
		return (0);
	i = 0;
	while (i < linem)
	{
		map_array[i] = map->line;
		trace = map->next;
		free(map);
		map = trace;
		i++;
	}
	return (map_array);
}