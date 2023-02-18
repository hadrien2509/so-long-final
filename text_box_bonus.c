/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_box_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:41:53 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/18 17:26:05 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_text_box(t_vars *vars, char *str)
{
	int		x;
	void	*mlx;
	void	*img;
	int		a;
	char	*path;

	x = vars->mapc.colm;
	mlx = vars->ren.mlx;
	path = "./textures/xpm/text_box.xpm";
	vars->ren.imgtb = mlx_xpm_file_to_image(mlx, path, &a, &a);
	img = vars->ren.imgtb;
	mlx_put_image_to_window(mlx, vars->ren.win, img, (x - 2) * 128, 5);
	mlx_string_put(mlx, vars->ren.win, (x - 1.87) * 128, 15, 0x000000, str);
}

static int	ft_nbrlen(int nb)
{
	int	count;

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

	i = ft_nbrlen(nb);
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
