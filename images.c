/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:57:58 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/18 20:27:15 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_create_player_img(t_rendering *ren)
{
	char	*path;
	int		a;

	path = "./textures/xpm/Player_up.xpm";
	ren->imgu = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->imgu)
		ft_free_img(ren);
	path = "./textures/xpm/Player_left.xpm";
	ren->imgl = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->imgl)
		ft_free_img(ren);
	path = "./textures/xpm/Player_right.xpm";
	ren->imgr = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->imgr)
		ft_free_img(ren);
	return (0);
}

int	ft_create_img(t_rendering *ren)
{
	char	*path;
	int		a;

	path = "./textures/xpm/path.xpm";
	ren->img0 = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->img0)
		ft_free_img(ren);
	path = "./textures/xpm/wall.xpm";
	ren->img1 = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->img1)
		ft_free_img(ren);
	path = "./textures/xpm/coin.xpm";
	ren->imgc = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->imgc)
		ft_free_img(ren);
	path = "./textures/xpm/car.xpm";
	ren->imge = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->imge)
		ft_free_img(ren);
	path = "./textures/xpm/Player_down.xpm";
	ren->imgd = mlx_xpm_file_to_image(ren->mlx, path, &a, &a);
	if (!ren->imgd)
		ft_free_img(ren);
	return (0);
}

void	ft_free_img(t_rendering *ren)
{
	if (ren->img1)
		mlx_destroy_image(ren->mlx, ren->img1);
	if (ren->imgc)
		mlx_destroy_image(ren->mlx, ren->imgc);
	if (ren->img0)
		mlx_destroy_image(ren->mlx, ren->img0);
	if (ren->imge)
		mlx_destroy_image(ren->mlx, ren->imge);
	if (ren->imgd)
		mlx_destroy_image(ren->mlx, ren->imgd);
	if (ren->imgu)
		mlx_destroy_image(ren->mlx, ren->imgu);
	if (ren->imgl)
		mlx_destroy_image(ren->mlx, ren->imgl);
	if (ren->imgr)
		mlx_destroy_image(ren->mlx, ren->imgr);
	if (ren->imgtb)
		mlx_destroy_image(ren->mlx, ren->imgtb);
	mlx_destroy_window(ren->mlx, ren->win);
	exit(0);
}
