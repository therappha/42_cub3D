# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/31 23:19:12 by gde-la-r          #+#    #+#              #
#    Updated: 2025/06/01 17:08:23 by rafaelfe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= cub3D
CC= cc
CFLAGS = -g -Wall -Wextra -Werror -I $(INCLUDES) #-fsanitize=address
LDFLAGS =  -L $(LIBFT_DIR) -lft -L $(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm
INCLUDES= ./includes
LIBFT_DIR= ./libs/libft
MLX_DIR= ./libs/mlx
MLX= $(MLX_DIR)/libmlx.a
LIBFT= $(LIBFT_DIR)/libft.a
SRCS_DIR= ./srcs

SRCS= $(SRCS_DIR)/delta.c \
	  $(SRCS_DIR)/game_loop.c \
	  $(SRCS_DIR)/load_map.c \
	  $(SRCS_DIR)/drawcircle.c \
	  $(SRCS_DIR)/main.c \
	  $(SRCS_DIR)/drawlines.c \
	  $(SRCS_DIR)/get_time.c \
	  $(SRCS_DIR)/math.c \
	  $(SRCS_DIR)/free_displays.c \
	  $(SRCS_DIR)/init_cub.c \
	  $(SRCS_DIR)/render_utils.c \
	  $(SRCS_DIR)/ft_free.c \
	  $(SRCS_DIR)/init_window.c \
	  $(SRCS_DIR)/ft_pixelput.c \
	  $(SRCS_DIR)/input_handler.c \
	  $(SRCS_DIR)/raycast.c \
	  $(SRCS_DIR)/move.c \
	  $(SRCS_DIR)/load_images.c \
	  $(SRCS_DIR)/debug.c \
	  $(SRCS_DIR)/collision.c \
	  $(SRCS_DIR)/flood_fill.c \
	  $(SRCS_DIR)/raycast_utils.c \
	  $(SRCS_DIR)/checkers.c \
	  $(SRCS_DIR)/load_map_utils.c \
	  $(SRCS_DIR)/colors.c \
	  $(SRCS_DIR)/check_map.c \
  	  $(SRCS_DIR)/map_dup.c \


OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $^ -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

$(MLX):
	if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR)

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT_DIR) --no-print-directory
	if [ -d "$(MLX_DIR)" ]; then \
		make clean -C $(MLX_DIR) --no-print-directory; \
	fi

	@echo "Cleaning Objects!"
fclean: clean
	@rm -rf $(NAME)
	if [ -d "$(MLX_DIR)" ]; then \
		rm -rf $(MLX_DIR); \
	fi

	@make fclean -C $(LIBFT_DIR) --no-print-directory
	@echo "Cleaning Objects and executable"

re: fclean all

.PHONY: all clean fclean re


