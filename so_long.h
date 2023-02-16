/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:53:33 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/16 13:53:35 by hgeissle         ###   ########.fr       */
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