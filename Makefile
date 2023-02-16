# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/19 14:22:07 by hgeissle          #+#    #+#              #
#    Updated: 2022/11/23 18:55:19 by hgeissle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long.out

SRC = mlx3.c

BONUS = 

FLAGS = -Wall -Wextra -Werror
INCLUDE = -lmlx -framework OpenGL -framework AppKit
AR = ar rcs
RM = rm -f
OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(BONUS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

bonus: ${OBJS_BONUS}
		$(AR) ${NAME} ${OBJS_BONUS}

clean:
		${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
		${RM} ${NAME}

re: fclean ${NAME}

reall : fclean all

rebonus : fclean bonus

.PHONY: all bonus clean fclean re reall rebonus