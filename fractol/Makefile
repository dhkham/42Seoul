# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkham <dkham@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/11 20:23:05 by dkham             #+#    #+#              #
#    Updated: 2023/02/18 15:43:27 by dkham            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm	-f
SRCS 	=	fractol.c \
			hook_utils.c \
			my_mlx_pixel_put.c \
			ft_strncmp.c \
			ft_isdigit.c \
			./plot_fractal/mandelbrot.c \
			./plot_fractal/julia.c \
			./plot_fractal/burningship.c \
			ft_atod.c \

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(SRCS)
	$(MAKE) all -C mlx 2> /dev/null
	$(CC) $(CFLAGS) $(SRCS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	$(MAKE) clean -C mlx

fclean: clean
	$(RM) $(NAME)
	$(MAKE) clean -C mlx

re: fclean $(NAME)

bonus: all

.PHONY = all clean fclean re bonus