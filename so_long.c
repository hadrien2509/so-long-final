/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:11:15 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/16 17:55:54 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "ft_printf.h"
#include <stdio.h>

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
}					t_map;

typedef struct s_mapcoord
{
	int		linem;
	int		colm;
	int		i;
	int		x;
	int		y;
	int		player_x;
	int		player_y;
	int		nbr_of_coins;
	int		coin_collect;
	int		exit_found;
	int		check_items;
}				t_mapcoord;

typedef struct s_rendering {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_width;
	int		img_height;
	char	*path0;
	char	*path1;
	char	*pathP;
	char	*pathC;
	char	*pathE;
	void	*mlx;
	void	*win;
}				t_rendering;

typedef struct s_vars
{
	t_mapcoord		mapc;
	t_rendering		ren;
	char			**map_array;
	int				lines;
	int				cols;
	int				moves;
	int				x_copy;
	int				y_copy;
}					t_vars;

int	ft_strlen(char *s)
{
	int		len;

	if (!s)
		return (-1);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	**ft_arraydup(char **map_array, int linem, int colm)
{
	int		i;
	int		j;
	char	**map_array_copy;

	i = 0;
	map_array_copy = malloc(sizeof(char *) * linem);
	if (!map_array_copy)
		return (NULL);
	while (i < linem)
	{	
		map_array_copy[i] = malloc(sizeof(char) * colm);
		j = colm - 1;
		while (j >= 0)
		{
			map_array_copy[i][j] = map_array[i][j];
			j--;
		}
		i++;
	}
	return (map_array_copy);
}

t_map	*ft_lstnew(int fd)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
	{
		printf("An error occured");
		return (NULL);
	}
	new->line = get_next_line(fd);
	new->next = NULL;
	return (new);
}

t_map	*ft_lstlast(t_map *lst)
{
	if (lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
	}
	return (lst);
}

void	ft_lstadd_back(t_map ***lst, t_map *new)
{
	t_map	*last;

	if (!new)
		return ;
	if (**lst)
	{
		last = ft_lstlast(**lst);
		last->next = new;
	}
	else
		**lst = new;
}

int	ft_check_map_size(t_mapcoord *mapc)
{
	if (mapc->linem > 40)
	{
		printf("Error. The map must not have more than 40 lines\n");
		return (-1);
	}
	if (mapc->linem < 3)
	{
		printf("Error. The map must have at least 3 lines\n");
		return (-1);
	}
	if (mapc->linem * mapc->colm < 15)
	{
		printf("Error. The map is too small to launch a game in it\n");
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
		printf("Error. The map may have 50 columns at most\n");
		return (-1);
	}
	if (mapc->colm < 3)
	{
		printf("Error. The map must have 3 lines or more\n");
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
		printf("%d and %d\n", mapc->colm, nbr_of_columns);
		if (mapc->colm != nbr_of_columns && new->line)
		{
			printf("Error. The map must be rectangular\n");
			return (-1);
		}
	}
	ft_check_map_size(mapc);
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

void	ft_put_objects(t_mapcoord *mapc, t_rendering ren, char copy)
{
	if (copy == 'P')
	{
		ren.img = mlx_xpm_file_to_image(ren.mlx, ren.pathP, &ren.img_width, &ren.img_height);
		mlx_put_image_to_window(ren.mlx, ren.win, ren.img, (mapc->x + 0.4) * 128, (mapc->y + 0.4) * 160);
	}
	if (copy == 'C')
	{	
		ren.img = mlx_xpm_file_to_image(ren.mlx, ren.pathC, &ren.img_width, &ren.img_height);
		mlx_put_image_to_window(ren.mlx, ren.win, ren.img, (mapc->x + 0.4) * 128, (mapc->y + 0.4) * 160);
	}
	if (copy == 'E')
	{
		ren.img = mlx_xpm_file_to_image(ren.mlx, ren.pathE, &ren.img_width, &ren.img_height);
		mlx_put_image_to_window(ren.mlx, ren.win, ren.img, (mapc->x + 0.1) * 128, (mapc->y + 0.4) * 160);
	}
}

void	ft_fixed_tiles(char **map_array, t_mapcoord *mapc, t_rendering ren)
{
	char	copy;

	mapc->y = 0;
	while (mapc->y < mapc->linem)
	{
		mapc->x = 0;
		while (mapc->x < mapc->colm)
		{
			copy = map_array[mapc->y][mapc->x];
			if (copy == '1')
			{
				ren.img = mlx_xpm_file_to_image(ren.mlx, ren.path1, &ren.img_width, &ren.img_height);
				mlx_put_image_to_window(ren.mlx, ren.win, ren.img, mapc->x * 128, mapc->y * 160);
			}
			if (copy == '0' || copy == 'E' || copy == 'C' || copy == 'P')
			{
				ren.img = mlx_xpm_file_to_image(ren.mlx, ren.path0, &ren.img_width, &ren.img_height);
				mlx_put_image_to_window(ren.mlx, ren.win, ren.img, mapc->x * 128, mapc->y * 160);
			}
			ft_put_objects(mapc, ren, copy);
			mapc->x++;
		}
		mapc->y++;
	}
}

void	ft_move(int keycode, t_vars *vars, int x_copy, int y_copy)
{
	if (keycode == 13)
	{	
		if (vars->map_array[y_copy - 1][x_copy] != '1' && y_copy > 0)
			vars->mapc.player_y -= 1;
		vars->ren.pathP = "./Tiles/xpm/Player_up.xpm";
	}
	if (keycode == 0)
	{	
		if (vars->map_array[y_copy][x_copy - 1] != '1' && x_copy > 0)
			vars->mapc.player_x -= 1;
		vars->ren.pathP = "./Tiles/xpm/Player_left.xpm";
	}
	if (keycode == 1)
	{
		if (vars->map_array[y_copy + 1][x_copy] != '1' && y_copy < vars->lines)
			vars->mapc.player_y += 1;
		vars->ren.pathP = "./Tiles/xpm/Player_down.xpm";
	}
	if (keycode == 2)
	{
		if (vars->map_array[y_copy][x_copy + 1] != '1' && x_copy < vars->cols)
			vars->mapc.player_x += 1;
		vars->ren.pathP = "./Tiles/xpm/Player_right.xpm";
	}
}

void	ft_interactions(t_vars *vars)
{
	if (vars->map_array[vars->mapc.player_y][vars->mapc.player_x] == 'C')
	{	
		vars->map_array[vars->mapc.player_y][vars->mapc.player_x] = '0';
		vars->mapc.nbr_of_coins--;
		printf("Remaining coin(s) : %d\n", vars->mapc.nbr_of_coins);
		if (vars->mapc.nbr_of_coins == 0)
			printf("Head to the nearest car quickly!\n");
	}
	if (vars->map_array[vars->mapc.player_y][vars->mapc.player_x] == 'E')
	{
		if (vars->mapc.nbr_of_coins == 0)
		{	
			usleep(200000);
			mlx_destroy_window(vars->ren.mlx, vars->ren.win);
			printf("You have done this in %d moves!\n", vars->moves);
			exit(0);
		}
	}
}

int	key_hook(int keycode, t_vars *vars)
{
	vars->x_copy = vars->mapc.player_x;
	vars->y_copy = vars->mapc.player_y;
	if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2)
	{
		ft_move(keycode, vars, vars->x_copy, vars->y_copy);
		vars->ren.img = mlx_xpm_file_to_image(vars->ren.mlx, vars->ren.path0, &vars->ren.img_width, &vars->ren.img_height);
		mlx_put_image_to_window(vars->ren.mlx, vars->ren.win, vars->ren.img, vars->x_copy * 128, vars->y_copy * 160);
		if (vars->map_array[vars->y_copy][vars->x_copy] == 'E')
		{	
			vars->ren.img = mlx_xpm_file_to_image(vars->ren.mlx, vars->ren.pathE, &vars->ren.img_width, &vars->ren.img_height);
			mlx_put_image_to_window(vars->ren.mlx, vars->ren.win, vars->ren.img, (vars->x_copy + 0.1) * 128, (vars->y_copy + 0.4) * 160);
		}
		ft_interactions(vars);
		vars->ren.img = mlx_xpm_file_to_image(vars->ren.mlx, vars->ren.pathP, &vars->ren.img_width, &vars->ren.img_height);
		mlx_put_image_to_window(vars->ren.mlx, vars->ren.win, vars->ren.img, (vars->mapc.player_x + 0.4) * 128, (vars->mapc.player_y + 0.4) * 160);
		if (vars->x_copy != vars->mapc.player_x || vars->y_copy != vars->mapc.player_y)
		{
			vars->moves++;
			printf("Number of moves : %d\n", vars->moves);
		}
	}
	return (0);
}

void	ft_moving_tiles(t_mapcoord *mapc, t_rendering ren, t_vars *v, char **ar)
{
	v->mapc = *mapc;
	v->ren = ren;
	v->map_array = ar;
	v->lines = v->mapc.linem;
	v->cols = v->mapc.colm;
	v->moves = 0;
	mlx_key_hook(ren.win, key_hook, v);
}

void	show_map(char **map_array, t_mapcoord mapc)
{
	t_rendering		ren;
	t_vars			vars;

	ren.path0 = "./Tiles/xpm/nocrosswalk.xpm";
	ren.path1 = "./Tiles/xpm/wall.xpm";
	ren.pathP = "./Tiles/xpm/Player_down.xpm";
	ren.pathC = "./Tiles/xpm/coin.xpm";
	ren.pathE = "./Tiles/xpm/car.xpm";
	ren.mlx = mlx_init();
	printf("%dx%d\n", mapc.colm * 128, mapc.linem * 160);
	ren.win = mlx_new_window(ren.mlx, mapc.colm * 128, mapc.linem * 160, "So long!");
	ft_fixed_tiles(map_array, &mapc, ren);
	ft_moving_tiles(&mapc, ren, &vars, map_array);
	mlx_loop(ren.mlx);
}

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

void	ft_error_type(int error_type)
{
	if (error_type == 2)
		printf("Error. The map must have an exit\n");
	if (error_type == 1)
		printf("Error. The map must have a player starting positon\n");
	if (error_type == 0)
		printf("Error. The map must have a player starting positon and an exit\n");
	if (error_type == 4)
		printf("Error. The map must have only one exit\n");
	if (error_type == 5)
		printf("Error. The map must have only one player starting position\n");
	if (error_type == 9)
		printf("Error. The map must have only one player starting position and one exit\n");
	if (error_type == -3)
		printf("Error. Invalid characters in the map\n");
	if (error_type == -4)
		printf("Error. The map must be delimited by walls\n");
	if (error_type == -5)
		printf("Error. The map have at least one coin\n");
}

int	main(int ac, char **av)
{
	int			fd;
	char		**map_array;
	char		**map_array_dub;
	t_map		*map;
	t_mapcoord	mapc;

	map = 0;
	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (ft_file_to_lst(fd, &mapc, &map) == -1)
		return (-1);
	close(fd);
	map_array = ft_map_array(map, mapc.linem);
	fd = ft_check_map(map_array, &mapc);
	if (fd != 3)
	{
		ft_error_type(fd);
		return (-1);
	}
	map_array_dub = ft_arraydup(map_array, mapc.linem, mapc.colm);
	if (map_array_dub == NULL)
		return (-1);
	mapc.coin_collect = 0;
	if (ft_pathfinding(map_array_dub, mapc.player_y, mapc.player_x, &mapc) == 0)
	{
		printf("Error. No valid path in the map\n");
		return (-1);
	}
	show_map(map_array, mapc);
}
