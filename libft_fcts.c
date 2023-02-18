/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:51:40 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/18 13:41:08 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
