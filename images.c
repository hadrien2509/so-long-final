/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:57:58 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/18 14:13:30 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_create_player_img(t_rendering *ren)
{
	char	*path;
	int		a;

	path = "./textures/xpm/Player_down.xpm";
	ren->imgd = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->imgd)
		return (-1);
	path = "./textures/xpm/Player_up.xpm";
	ren->imgu = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->imgu)
		return (-1);
	path = "./textures/xpm/Player_left.xpm";
	ren->imgl = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->imgl)
		return (-1);
	path = "./textures/xpm/Player_right.xpm";
	ren->imgr = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->imgr)
		return (-1);
	return (0);
}

int	ft_create_img(t_rendering *ren)
{
	char	*path;
	int		a;

	path = "./textures/xpm/nocrosswalk.xpm";
	ren->img0 = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->img0)
		return (-1);
	path = "./textures/xpm/wall.xpm";
	ren->img1 = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->img1)
		return (-1);
	path = "./textures/xpm/coin.xpm";
	ren->imgc = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->imgc)
		return (-1);
	path = "./textures/xpm/car.xpm";
	ren->imge = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->imge)
		return (-1);
	return (0);
}

void	ft_free_img(t_vars *vars)
{
	if (vars->ren.img0)
		free(vars->ren.img0);
	if (vars->ren.img1)
		free(vars->ren.img1);
	if (vars->ren.imgc)
		free(vars->ren.imgc);
	if (vars->ren.imge)
		free(vars->ren.imge);
	if (vars->ren.imgd)
		free(vars->ren.imgd);
	if (vars->ren.imgu)
		free(vars->ren.imgu);
	if (vars->ren.imgl)
		free(vars->ren.imgl);
	if (vars->ren.imgr)
		free(vars->ren.imgr);
	exit(0);
}
