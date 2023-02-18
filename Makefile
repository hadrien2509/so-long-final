# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/19 14:22:07 by hgeissle          #+#    #+#              #
#    Updated: 2023/02/18 13:33:31 by hgeissle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long.out

SRC = parsing.c check_map.c pathfinding.c images.c show_map.c game.c text_box_bonus.c main.c

SRC_LIBFT = libft_fcts.c get_next_line_bonus.c get_next_line_utils_bonus.c ft_printf.c ft_printf_tools.c

FLAGS = -Wall -Wextra -Werror
INCLUDE = -lmlx -framework OpenGL -framework AppKit
AR = ar rcs
RM = rm -f
OBJS = $(SRC:.c=.o)
OBJS_LIBFT = $(SRC_LIBFT:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_LIBFT)
	gcc $(FLAGS) $(OBJS) $(OBJS_LIBFT) $(INCLUDE) -o $(NAME)

bonus: all

clean:
		$(RM) $(OBJS) $(OBJS_LIBFT)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re