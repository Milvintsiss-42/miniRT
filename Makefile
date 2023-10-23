# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 15:36:23 by ple-stra          #+#    #+#              #
#    Updated: 2023/10/23 02:11:56 by ple-stra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

SRCS_DIR	= srcs
SRCS		= $(addsuffix .c, \
	main \
	$(addprefix common/, \
		basic_utils \
		clear_mrt \
		errors \
		print_progress \
	) \
	$(addprefix engine/, \
		draw_frame \
		draw_test_card_f \
		lighting \
		color_helpers \
	) \
	$(addprefix parsing/, \
		parsing \
		parsing_helpers \
		parsing_helpers_color \
		parsing_helpers_vectors \
		parse_light \
		parse_camera \
		parse_sphere \
		parse_plane \
		parse_cylinder \
	) \
	$(addprefix img_helpers/, \
		img_garbage \
		img_helpers \
	) \
	$(addprefix mlx_helpers/, \
		basic_mlx_helpers \
		open_window \
		key_events \
		mouse_events \
		special_events \
	) \
	$(addprefix object_helpers/, \
		camera_helpers \
		object_getters \
		object_helpers \
		object_lists \
		object_modifiers \
	) \
	$(addprefix math_helpers/, \
		angle_helpers \
		matrix_helpers \
		vec3_basics \
		vec3_products \
	) \
 )
BUILD_DIR	= build
OBJ_DIR		= $(BUILD_DIR)/objs
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
INC			= -I./includes -I./$(LIBFT_DIR)/includes -I./$(MLX_DIR) -I./

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/build/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR)/build -lft

MLX_DIR		= minilibx
ifeq ($(shell uname), Linux)
MLX			= $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx_Linux \
 -L/usr/lib -L/usr/X11/lib -lXext -lX11 -lm
else
MLX			= $(MLX_DIR)/libmlx_Darwin.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx_Darwin \
 -L/usr/lib -L/usr/X11/lib -lXext -lX11 -lm
endif

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
