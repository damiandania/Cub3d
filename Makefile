# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddania-c <ddania-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2023/12/07 12:02:17 by ddania-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		:= cub3D

BONUS		= 0

#DIRECTORIES_________________________________________________________

LIBS		:=	ft gnl mlx
LIBS_TARGET	:=							\
				lib/libft/libft.a		\
				lib/libgnl/libgnl.a		\
				lib/libmlx/libmlx.a

INCS		:=	include					\
				lib/libft/include		\
				lib/libgnl/include		\
				lib/libmlx

#SOURCES_____________________________________________________________

SRC_DIR		:=	sources
SRCS		:=	main.c							\
				init/data.c						\
				init/ray.c						\
				init/window.c					\
				movement/events.c				\
				movement/move_player.c			\
				parsing/check_parsing.c			\
				parsing/check_map.c				\
				parsing/check_color.c			\
				parsing/file_stock.c			\
				parsing/map_stock.c				\
				parsing/player_stock.c			\
				parsing/utils.c					\
				render/minimap.c				\
				render/picture.c				\
				render/player.c					\
				render/raycasting.c				\
				render/render.c					\
				render/textures.c				\
				free.c

SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

#OBJECT______________________________________________________________

BUILD_DIR	:= .build
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

#FLAGS_______________________________________________________________

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g
CPPFLAGS	:= $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS		:= $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS		:= $(addprefix -l,$(LIBS))
LMLX		:= -lXext -lX11 -lm -lz
RM			:= rm -f
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(@D)

#COLORS______________________________________________________________

GREEN	=	\033[0;32m
RED		=	\033[0;31m
WHITE	=	\033[0;97m
RESET	=	\033[0m
YELLOW 	=	\033[0;93m

#MAIN_RULE___________________________________________________________

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	@echo -n "$(YELLOW)Compiling	${WHITE}→	$(YELLOW)$(NAME)$(RESET) "
	@echo "$(GREEN)[ok]✓$(RESET)"
	@$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) $(LMLX) -o $(NAME)
#	$(info CREATED $(NAME))

#OBJECT_RULE_________________________________________________________

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -DBONUS=$(BONUS) -c -o $@ $<

#LIBFT_RULE__________________________________________________________

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

bonus:
	make all BONUS=1

#CLEAN_RULE__________________________________________________________

clean:
	@echo -n "$(RED)Deleting	${WHITE}→	$(RED)$(NAME) object$(RESET) "
	$(RM) $(OBJS)
	@echo "$(GREEN)[ok]$(RED)✗$(RESET)"
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done

fclean: clean
	@echo -n "$(RED)Deleting	${WHITE}→	$(RED)$(NAME) executable$(RESET) "
	$(RM) $(NAME)
	@echo "$(GREEN)[ok]$(RED)✗$(RESET)"
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done

re: fclean all

rebonus: fclean bonus

#SPEC________________________________________________________________

.PHONY: clean fclean re bonus
.SILENT:

