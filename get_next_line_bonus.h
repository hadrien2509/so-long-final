/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:25:58 by hgeissle          #+#    #+#             */
/*   Updated: 2022/11/14 16:13:51 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char		*get_next_line(int fd);
char		*ft_finish_line(int fd, char *buffer, char *line, int length);
char		*ft_old_buffer(char *buffer, char *line, int *length, int *start);
char		*ft_readstatus(char *buffer, int read_status);
char		*ft_setzero(char *buffer);
char		*ft_stradd(char *line, char *buffer, int length, int buffer_start);
char		*ft_alloc_line(char *line, int length);

#endif