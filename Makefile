# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 15:36:23 by ple-stra          #+#    #+#              #
#    Updated: 2023/03/18 21:34:33 by ple-stra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

SRCS_DIR	= srcs
SRCS		= main.c
BUILD_DIR	= build
OBJ_DIR		= $(BUILD_DIR)/objs
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
INC			= -I./includes -I./$(LIBFT_DIR)/includes -I./$(MLX_DIR) -I./

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/build/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR)/build -lft

MLX_DIR		= minilibx-linux
MLX			= $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm

CC			= cc
CFLAGS		= -Wall -Wextra -O3
LFLAGS		= $(LIBFT_FLAGS) $(MLX_FLAGS)
ifneq (nWerror, $(filter nWerror,$(MAKECMDGOALS)))
	CFLAGS	+= -Werror
endif
ifeq (sanitize, $(filter sanitize,$(MAKECMDGOALS)))
	CFLAGS 	+= -fsanitize=address
endif
ifeq (g3, $(filter g3,$(MAKECMDGOALS)))
	CFLAGS 	+= -g3
endif
ifeq (debug, $(filter debug,$(MAKECMDGOALS)))
	CFLAGS	+= -D KDEBUG=1
endif

RM			= rm -rf

all			: $(NAME)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT)	:
ifeq (,$(wildcard $(LIBFT)))
			@echo "building libft..."
			@$(MAKE) -sC $(LIBFT_DIR) all
endif

rmlibft		:
			@echo "deleting libft build..."
			@$(MAKE) -sC $(LIBFT_DIR) fclean

$(MLX)	:
ifeq (,$(wildcard $(MLX)))
			@echo "building mlx..."
			@$(MAKE) -sC $(MLX_DIR) all
endif

rmmlx		:
			@echo "deleting mlx build..."
			@$(MAKE) -sC $(MLX_DIR) clean

$(NAME)		: $(LIBFT) $(MLX) $(OBJ)
			$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJ) $(LFLAGS)
			
clean		:
			$(RM) $(OBJ_DIR)
			$(RM) $(OBJBNS_DIR)

fclean		:
			$(RM) $(BUILD_DIR)
			$(RM) $(NAME)

fcleanall	: rmlibft rmmlx
			$(RM) $(BUILD_DIR)
			$(RM) $(NAME)

bonus		: all

re			: fclean all

nWerror		:
			@echo "WARN: Compiling without Werror flag!"
sanitize	:
			@echo "WARN: Compiling with fsanitize flag!"
g3			:
			@echo "WARN: Compiling with g3 flag!"
debug		:
			@echo "WARN: debug is enabled"
debug_exec	:
			@echo "WARN: debug_exec is enabled"

.PHONY: \
 all bonus clean fclean fcleanall re rmlibft rmmlx\
 nWerror sanitize debug g3 debug_exec
