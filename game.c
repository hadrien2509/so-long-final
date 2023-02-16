/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:57:26 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/16 17:08:17 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_move(int keycode, t_vars *vars, int x_copy, int y_copy)
{
	if (keycode == 13)
	{	
		if (vars->map_array[y_copy - 1][x_copy] != '1' && y_copy > 0)
			vars->mapc.player_y -= 1;
		vars->ren.path_p = "./textures/xpm/Player_up.xpm";
	}
	if (keycode == 0)
	{	
		if (vars->map_array[y_copy][x_copy - 1] != '1' && x_copy > 0)
			vars->mapc.player_x -= 1;
		vars->ren.path_p = "./textures/xpm/Player_left.xpm";
	}
	if (keycode == 1)
	{
		if (vars->map_array[y_copy + 1][x_copy] != '1' && y_copy < vars->lines)
			vars->mapc.player_y += 1;
		vars->ren.path_p = "./textures/xpm/Player_down.xpm";
	}
	if (keycode == 2)
	{
		if (vars->map_array[y_copy][x_copy + 1] != '1' && x_copy < vars->cols)
			vars->mapc.player_x += 1;
		vars->ren.path_p = "./textures/xpm/Player_right.xpm";
	}
}

void	ft_put_exit(t_vars *v, int x, int y)
{
	int	a;

	v->ren.img = mlx_xpm_file_to_image(v->ren.mlx, v->ren.path_e, &a, &a);
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
		v->ren.img = mlx_xpm_file_to_image(v->ren.mlx, v->ren.path_p, &a, &a);
		x = (v->mapc.player_x + 0.4) * 128;
		y = (v->mapc.player_y + 0.4) * 160;
		mlx_put_image_to_window(v->ren.mlx, v->ren.win, v->ren.img, x, y);
		ft_interactions(v);
	}
	if (key == 53)
		exit(0);
	return (0);
}
