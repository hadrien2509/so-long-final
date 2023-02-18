/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:53:33 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/18 20:10:06 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "ft_printf.h"

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
}					t_map;

typedef struct s_mapcoord
{
	int		linem;
	int		colm;
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
	void	*imgd;
	void	*imgu;
	void	*imgl;
	void	*imgr;
	void	*imge;
	void	*img1;
	void	*imgc;
	void	*imgtb;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_width;
	int		img_height;
	char	*path0;
	char	*path1;
	char	*path_p;
	char	*path_c;
	char	*path_e;
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

int		ft_check_map_items(char **map_array, int x, int y, t_mapcoord *mapc);
int		ft_check_map(char **map_array, t_mapcoord *mapc);
void	ft_error_type(int error_type);
void	ft_move(int keycode, t_vars *vars, int x_copy, int y_copy);
void	ft_put_exit(t_vars *v, int x, int y);
void	ft_interactions(t_vars *v);
int		key_hook(int key, t_vars *v);
int		ft_strlen(char *s);
t_map	*ft_lstnew(int fd);
t_map	*ft_lstlast(t_map *lst);
void	ft_lstadd_back(t_map ***lst, t_map *new);
int		ft_check_map_size(t_mapcoord *mapc);
int		ft_check_colm(t_mapcoord *mapc, t_map *new);
int		ft_file_to_lst(int fd, t_mapcoord *mapc, t_map **map);
char	**ft_map_array(t_map *map, int linem);
char	**ft_arraydup(char **map_array, t_mapcoord *mapc);
void	ft_free_array(t_mapcoord *mapc, char **map_array_dup);
int		ft_pathfinding(char **map_array, int y, int x, t_mapcoord *mapc);
int		ft_pathfinding_utils(t_mapcoord *mapc, char **map_array);
void	ft_put_objects(t_mapcoord *mapc, t_rendering *ren, char copy);
void	ft_fixed_tiles(char **map_array, t_mapcoord *mapc, t_rendering *ren);
void	ft_move_tiles(t_mapcoord *mapc, t_rendering ren, t_vars *v, char **ar);
void	show_map(char **map_array, t_mapcoord mapc);
void	ft_text_box(t_vars *vars, char *str);
char	*ft_itoa(int nb);
void	ft_count_moves(t_vars *vars);
void	ft_free_img(t_rendering *ren);
int		ft_create_img(t_rendering *ren);
int		ft_create_player_img(t_rendering *ren);
void	ft_print_map(t_mapcoord *mapc, char **map_array);

#endif