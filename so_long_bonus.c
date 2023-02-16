/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:11:15 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/16 17:56:57 by hgeissle         ###   ########.fr       */
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
	void	*img0;
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
	char	*pathB;
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
	int				end;
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

t_map	*ft_lstnew(int fd)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
	{
		ft_printf("An error occured");
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
		printf("%d and %d\n", mapc->colm, nbr_of_columns);
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

void	ft_put_objects(t_mapcoord *mapc, t_rendering ren, char copy)
{
	int	a;
	int	x;
	int	y;

	x = (mapc->x + 0.4) * 128;
	y = (mapc->y + 0.4) * 160;
	if (copy == 'P')
	{
		ren.img = mlx_xpm_file_to_image(ren.mlx, ren.pathP, &a, &a);
		mlx_put_image_to_window(ren.mlx, ren.win, ren.img, x, y);
	}
	if (copy == 'C')
	{
		ren.img = mlx_xpm_file_to_image(ren.mlx, ren.pathC, &a, &a);
		mlx_put_image_to_window(ren.mlx, ren.win, ren.img, x, y);
	}
	if (copy == 'E')
	{
		x = (mapc->x + 0.1) * 128;
		ren.img = mlx_xpm_file_to_image(ren.mlx, ren.pathE, &a, &a);
		mlx_put_image_to_window(ren.mlx, ren.win, ren.img, x, y);
	}
}

void	ft_fixed_tiles(char **map_array, t_mapcoord *mapc, t_rendering ren)
{
	char	copy;
	int		x;
	int		y;
	int		a;

	mapc->y = 0;
	ren.img = mlx_xpm_file_to_image(ren.mlx, ren.path1, &a, &a);
	while (mapc->y < mapc->linem)
	{
		mapc->x = 0;
		while (mapc->x < mapc->colm)
		{
			x = mapc->x * 128;
			y = mapc->y * 160;
			copy = map_array[mapc->y][mapc->x];
			if (copy == '1')
				mlx_put_image_to_window(ren.mlx, ren.win, ren.img, x, y);
			if (copy == '0' || copy == 'E' || copy == 'C' || copy == 'P')
				mlx_put_image_to_window(ren.mlx, ren.win, ren.img0, x, y);
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
		vars->ren.pathP = "./textures/xpm/Player_up.xpm";
	}
	if (keycode == 0)
	{	
		if (vars->map_array[y_copy][x_copy - 1] != '1' && x_copy > 0)
			vars->mapc.player_x -= 1;
		vars->ren.pathP = "./textures/xpm/Player_left.xpm";
	}
	if (keycode == 1)
	{
		if (vars->map_array[y_copy + 1][x_copy] != '1' && y_copy < vars->lines)
			vars->mapc.player_y += 1;
		vars->ren.pathP = "./textures/xpm/Player_down.xpm";
	}
	if (keycode == 2)
	{
		if (vars->map_array[y_copy][x_copy + 1] != '1' && x_copy < vars->cols)
			vars->mapc.player_x += 1;
		vars->ren.pathP = "./textures/xpm/Player_right.xpm";
	}
}

void ft_text_box(t_vars *vars, char *str)
{
	int		x;
	void	*mlx;
	void	*img;
	int		a;
	char	*path;

	a = 0;
	x = vars->mapc.colm;
	mlx = vars->ren.mlx;
	img = vars->ren.img;
	path = "./textures/xpm/text_box.xpm";
	img = mlx_xpm_file_to_image(mlx, path, &a, &a);
	mlx_put_image_to_window(mlx, vars->ren.win, img, (x - 2) * 128, 5);
	mlx_string_put(mlx, vars->ren.win, (x - 1.87) * 128, 15, 0x000000, str);
}

void	ft_put_exit(t_vars *v, int x, int y)
{
	int	a;

	v->ren.img = mlx_xpm_file_to_image(v->ren.mlx, v->ren.pathE, &a, &a);
	if (v->end)
	{
		while (x >= 0)
		{
			mlx_put_image_to_window(v->ren.mlx, v->ren.win, v->ren.img0, x, y);
			x -= 128;
		}
		x += 128;
	}
	x = x + 0.1 * 128;
	y = y + 0.4 * 160;
	mlx_put_image_to_window(v->ren.mlx, v->ren.win, v->ren.img, x, y);
}

void	ft_interactions(t_vars *v)
{
	if (v->map_array[v->mapc.player_y][v->mapc.player_x] == 'C')
	{
		v->map_array[v->mapc.player_y][v->mapc.player_x] = '0';
		v->mapc.nbr_of_coins--;
	}
	if (v->map_array[v->mapc.player_y][v->mapc.player_x] == 'E')
	{
		if (v->mapc.nbr_of_coins == 0)
		{
			v->end = 1;
			ft_put_exit(v, v->mapc.player_x * 128, v->mapc.player_y * 160);
			ft_printf("You finished the game in %d moves.\n", v->moves);
		}
		else if (v->mapc.nbr_of_coins == 1)
			ft_text_box(v, "One bag remains");
		else
			ft_text_box(v, "Bags still remaining");
	}
}

static size_t	ft_nbrlen(int nb)
{
	size_t			count;

	count = 0;
	while (nb > 0)
	{
		count++;
		nb = nb / 10;
	}
	return (count);
}

char	*ft_itoa(int nb)
{
	char			*nbr;
	int				i;

	i = (int)ft_nbrlen(nb);
	nbr = malloc(sizeof(char) * (i + 7));
	if (!nbr)
		return (NULL);
	nbr[i] = ' ';
	nbr[i + 1] = 'M';
	nbr[i + 2] = 'o';
	nbr[i + 3] = 'v';
	nbr[i + 4] = 'e';
	if (nb >= 2)
		nbr[i + 5] = 's';
	else
		nbr[i + 5] = ' ';
	nbr[i + 6] = '\0';
	i--;
	while (i >= 0)
	{
		nbr[i] = "0123456789"[nb % 10];
		nb = nb / 10;
		i--;
	}
	return (nbr);
}

void	ft_count_moves(t_vars *vars)
{
	char	*itoa;

	vars->moves++;
	itoa = ft_itoa(vars->moves);
	ft_text_box(vars, itoa);
}

int	key_hook(int key, t_vars *v)
{
	int	a;
	int	x;
	int	y;

	x = v->mapc.player_x;
	y = v->mapc.player_y;
	if ((key == 13 || key == 0 || key == 1 || key == 2) && v->end == 0)
	{
		ft_move(key, v, x, y);
		if (x != v->mapc.player_x || y != v->mapc.player_y)
			ft_count_moves(v);
		x = x * 128;
		y = y * 160;
		mlx_put_image_to_window(v->ren.mlx, v->ren.win, v->ren.img0, x, y);
		if (v->map_array[y / 160][x / 128] == 'E')
			ft_put_exit(v, x, y);
		v->ren.img = mlx_xpm_file_to_image(v->ren.mlx, v->ren.pathP, &a, &a);
		x = (v->mapc.player_x + 0.4) * 128;
		y = (v->mapc.player_y + 0.4) * 160;
		mlx_put_image_to_window(v->ren.mlx, v->ren.win, v->ren.img, x, y);
		ft_interactions(v);
	}
	if (key == 53)
		exit(0);
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
	v->end = 0;
	ft_text_box(v, "Collect all the bags !");
	mlx_key_hook(ren.win, key_hook, v);
}

void	show_map(char **map_array, t_mapcoord mapc)
{
	t_rendering		ren;
	t_vars			vars;
	int				width;
	int				height;
	int				a;

	ren.path0 = "./textures/xpm/nocrosswalk.xpm";
	ren.path1 = "./textures/xpm/wall.xpm";
	ren.pathP = "./textures/xpm/Player_down.xpm";
	ren.pathC = "./textures/xpm/coin.xpm";
	ren.pathE = "./textures/xpm/car.xpm";
	width = mapc.colm * 128;
	height = mapc.linem * 160;
	ren.mlx = mlx_init();
	ren.img0 = mlx_xpm_file_to_image(ren.mlx, ren.path0, &a, &a);
	ren.win = mlx_new_window(ren.mlx, width, height, "So long!");
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
		ft_printf("The map must have an exit.\n");
	if (error_type == 1)
		ft_printf("The map must have a player starting positon.\n");
	if (error_type == 0)
		ft_printf("The map must have a player starting positon and an exit.\n");
	if (error_type == 4)
		ft_printf("The map must have only 1 exit.\n");
	if (error_type == 5)
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
	ft_pathfinding_utils(&mapc, map_array);
	show_map(map_array, mapc);
}
