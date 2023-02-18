/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:57:26 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/18 20:37:14 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_move(int keycode, t_vars *vars, int x_copy, int y_copy)
{
	if (keycode == 13)
	{	
		if (vars->map_array[y_copy - 1][x_copy] != '1' && y_copy > 0)
			vars->mapc.player_y -= 1;
		vars->ren.img = vars->ren.imgu;
	}
	if (keycode == 0)
	{	
		if (vars->map_array[y_copy][x_copy - 1] != '1' && x_copy > 0)
			vars->mapc.player_x -= 1;
		vars->ren.img = vars->ren.imgl;
	}
	if (keycode == 1)
	{
		if (vars->map_array[y_copy + 1][x_copy] != '1' && y_copy < vars->lines)
			vars->mapc.player_y += 1;
		vars->ren.img = vars->ren.imgd;
	}
	if (keycode == 2)
	{
		if (vars->map_array[y_copy][x_copy + 1] != '1' && x_copy < vars->cols)
			vars->mapc.player_x += 1;
		vars->ren.img = vars->ren.imgr;
	}
}
#include <stdio.h>
int	ft_exit_animation(t_vars *v)
{
	int	x;
	int	y;

	x = v->mapc.player_x * 8;
	y = v->mapc.player_y * 160;
	mlx_put_image_to_window(v->ren.mlx, v->ren.win, v->ren.img0, x, y);
	v->mapc.player_x -= 1;
	x = (v->mapc.player_x + 0.1) * 8;
	y = (v->mapc.player_y + 0.4) * 160;
	if (v->mapc.player_x >= 0)
		mlx_put_image_to_window(v->ren.mlx, v->ren.win, v->ren.imge, x, y);
	if (v->mapc.player_x == -20)
	{
		ft_printf("You finished the game in %d moves.\n", v->moves);
		ft_free_img(&v->ren);
	}
	return (0);
}

void	ft_put_exit(t_vars *v, int x, int y)
{
	if (v->end)
	{
		while (x >= 0)
		{
			mlx_put_image_to_window(v->ren.mlx, v->ren.win, v->ren.img0, x, y);
			x -= 128;
		}
		x += 128;
		v->mapc.player_x *= 16;
		mlx_loop_hook(v->ren.mlx, ft_exit_animation, v);
	}
	else
	{
		x = x + 0.1 * 128;
		y = y + 0.4 * 160;
		mlx_put_image_to_window(v->ren.mlx, v->ren.win, v->ren.imge, x, y);
	}
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
		}
		else if (v->mapc.nbr_of_coins == 1)
			ft_text_box(v, "One bag remains");
		else
			ft_text_box(v, "Bags still remaining");
	}
}

int	key_hook(int key, t_vars *v)
{
	int		a;
	int		x;
	int		y;
	void	*img;

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
		x = (v->mapc.player_x + 0.4) * 128;
		y = (v->mapc.player_y + 0.4) * 160;
		mlx_put_image_to_window(v->ren.mlx, v->ren.win, v->ren.img, x, y);
		ft_interactions(v);
	}
	if (key == 53)
		ft_free_img(&v->ren);
	return (0);
}
