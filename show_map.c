/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:45:35 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/16 19:46:15 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_put_objects(t_mapcoord *mapc, t_rendering ren, char copy)
{
	int	a;
	int	x;
	int	y;

	x = (mapc->x + 0.4) * 128;
	y = (mapc->y + 0.4) * 160;
	if (copy == 'P')
	{
		ren.img = mlx_xpm_file_to_image(ren.mlx, ren.path_p, &a, &a);
		mlx_put_image_to_window(ren.mlx, ren.win, ren.img, x, y);
	}
	if (copy == 'C')
	{
		ren.img = mlx_xpm_file_to_image(ren.mlx, ren.path_c, &a, &a);
		mlx_put_image_to_window(ren.mlx, ren.win, ren.img, x, y);
	}
	if (copy == 'E')
	{
		x = (mapc->x + 0.1) * 128;
		ren.img = mlx_xpm_file_to_image(ren.mlx, ren.path_e, &a, &a);
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

void	ft_move_tiles(t_mapcoord *mapc, t_rendering ren, t_vars *v, char **ar)
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
	char			*path;

	path = "./textures/xpm/nocrosswalk.xpm";
	ren.img0 = mlx_xpm_file_to_image(ren.mlx, path, &a, &a);
	path = "./textures/xpm/wall.xpm";
	ren.img1 = mlx_xpm_file_to_image(ren.mlx, path, &a, &a);
	path = "./textures/xpm/Player_down.xpm";
	ren.imgp = mlx_xpm_file_to_image(ren.mlx, path, &a, &a);
	path = "./textures/xpm/coin.xpm";
	ren.imgc = mlx_xpm_file_to_image(ren.mlx, path, &a, &a);
	path = "./textures/xpm/car.xpm";
	ren.imge = mlx_xpm_file_to_image(ren.mlx, path, &a, &a);
	width = mapc.colm * 128;
	height = mapc.linem * 160;
	ren.mlx = mlx_init();
	ren.img0 = mlx_xpm_file_to_image(ren.mlx, ren.path0, &a, &a);
	ren.win = mlx_new_window(ren.mlx, width, height, "So long!");
	ft_fixed_tiles(map_array, &mapc, ren);
	ft_move_tiles(&mapc, ren, &vars, map_array);
	mlx_loop(ren.mlx);
}