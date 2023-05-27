# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 10:56:52 by adi-stef          #+#    #+#              #
#    Updated: 2023/05/27 13:12:24 by adi-stef         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

SRC		= main.c	\
			$(wildcard Game/*.c)	\
			$(wildcard Utils/*.c)	\
			$(wildcard Parser/*.c)
OBJ		= $(SRC:%.c=%.o)

CC		= gcc
FLAGS	= -Wall -Wextra -Werror
MLX		= mlx/libmlx.a -Lmlx -lXext -lX11 -lm
RM		= rm -f

RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;36m
RESET	= \033[0;0m

%.o:%.c
	@printf "\r\033[K$(GREEN)Compiling cub3d...$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@printf "\r\033[K$(GREEN)cub3d compiled$(RESET)\n"
	@printf "$(GREEN)Compiling minilibx...$(RESET)"
	@make -C mlx 1>/dev/null 2>&1
	@printf "\r\033[K$(GREEN)minilibx compiled$(RESET)\n"
	@$(CC) $(FLAGS) $(OBJ) $(MLX) -o $(NAME)
	@printf "$(BLUE)cub3d created successfully\n$(RESET)"
	@printf "$(BLUE)------------------------------------------\n$(RESET)"
	@printf "  ██████╗██╗   ██╗██████╗ ██████╗ ██████╗  \n"
	@printf " ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗ \n"
	@printf " ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║ \n"
	@printf " ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║ \n"
	@printf " ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝ \n"
	@printf "  ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝  \n"
	@printf "$(YELLOW)        Made by Adi-stef and Gpanico\n$(RESET)"
	@printf "$(BLUE)------------------------------------------\n$(RESET)"

all: $(NAME)

clean:
	@printf "$(RED)Removing object files...$(RESET)"
	@$(RM) $(OBJ)
	@printf "\r\033[K$(RED)object files removed$(RESET)\n"

fclean: clean
	@printf "$(RED)Cleaning minilibx...$(RESET)"
	@make clean -C mlx 1>/dev/null 2>&1
	@printf "\r\033[K$(RED)minilibx cleaned$(RESET)\n"
	@printf "$(RED)Removing program executable...$(RESET)"
	@$(RM) $(NAME)
	@printf "\r\033[K$(RED)cub3d removed$(RESET)\n"

re: fclean all

bonus: all

.PHONY: all clean fclean bonus re
