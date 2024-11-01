# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/29 22:06:46 by hbettal           #+#    #+#              #
#    Updated: 2024/11/01 17:13:51 by hbettal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR		= src/Mandatory/
SRCSB_DIR		= src/Bonus/
PARSE_DIR		= $(SRCS_DIR)Parse/
RAYCASTING_DIR		= $(SRCS_DIR)Raycasting/
PARSE_BONUS_DIR		= $(SRCSB_DIR)Parse/
RAYCASTING_BONUS_DIR	= $(SRCSB_DIR)Raycasting/
SRCS_MANADTORY		= $(SRCS_DIR)main.c $(SRCS_DIR)ft_error.c \
			$(PARSE_DIR)map_analyzer.c \
			$(PARSE_DIR)map_analyzer_utils.c $(PARSE_DIR)map_parser.c \
			$(PARSE_DIR)map_parser_utils.c $(PARSE_DIR)map_parser_utils2.c \
			$(PARSE_DIR)parse_linked_list.c \
			$(RAYCASTING_DIR)ft_bresenhams.c \
			$(RAYCASTING_DIR)init_mlx.c $(RAYCASTING_DIR)mlx_event.c \
			$(RAYCASTING_DIR)render_2d.c $(RAYCASTING_DIR)render_3d.c \
			$(RAYCASTING_DIR)render_3d_utils.c $(RAYCASTING_DIR)utils.c \
			$(RAYCASTING_DIR)utils2.c $(RAYCASTING_DIR)render_3d_utils2.c
SRCS_BONUS		= $(SRCSB_DIR)main_bonus.c $(SRCSB_DIR)ft_error_bonus.c \
			$(PARSE_BONUS_DIR)door_linked_list_bonus.c $(PARSE_BONUS_DIR)map_analyzer_bonus.c \
			$(PARSE_BONUS_DIR)map_analyzer_utils_bonus.c $(PARSE_BONUS_DIR)map_parser_bonus.c \
			$(PARSE_BONUS_DIR)map_parser_utils_bonus.c $(PARSE_BONUS_DIR)map_parser_utils2_bonus.c \
			$(PARSE_BONUS_DIR)parse_linked_list_bonus.c \
			$(RAYCASTING_BONUS_DIR)door_bonus.c $(RAYCASTING_BONUS_DIR)ft_bresenhams_bonus.c \
			$(RAYCASTING_BONUS_DIR)init_mlx_bonus.c $(RAYCASTING_BONUS_DIR)mlx_event_bonus.c \
			$(RAYCASTING_BONUS_DIR)render_2d_bonus.c $(RAYCASTING_BONUS_DIR)render_3d_bonus.c \
			$(RAYCASTING_BONUS_DIR)render_3d_utils_bonus.c $(RAYCASTING_BONUS_DIR)utils_bonus.c \
			$(RAYCASTING_BONUS_DIR)utils2_bonus.c $(RAYCASTING_BONUS_DIR)render_3d_utils2_bonus.c\
			$(RAYCASTING_BONUS_DIR)minimap_bonus.c
OBJS_DIR		= obj/mandatory/
OBJSB_DIR		= obj/bonus/
OBJS 			= $(addprefix $(OBJS_DIR), $(SRCS_MANADTORY:.c=.o))
OBJSB 			= $(addprefix $(OBJSB_DIR), $(SRCS_BONUS:.c=.o))
INCS_DIR		= includes/
INCS			= $(INCS_DIR)cub3d.h $(INCS_DIR)struct.h $(INCS_DIR).MLX42.h
LIBFT_DIR		= lib/libft/
LIBFT			= $(LIBFT_DIR)libft.a
CFLAGS			= -I$(INCS_DIR) -I$(LIBFT_DIR) 
CFLAGS			+= -Wall -Werror -Wextra -g
NAME			= cub3D
NAME_BONUS		= cub3D_bonus
RM			= rm -rf
ERASE			= \033[2K\r
BLUE			= \033[34m
YELLOW			= \033[33m
GREEN			= \033[32m
END			= \033[0m
LDFLAGS			= -framework OpenGL -framework AppKit libmlx42.a -Iinclude -lglfw -L"$(shell brew --prefix glfw)/lib"

define PRINT_BANNER
	@echo "\n\033[0;36m"
	@echo " 	  ██████╗██╗   ██╗██████╗ ██████╗ █████╗ ██████╗ "
	@echo " 	 ██╔════╝██║   ██║██╔══██╗╚══███╔╝██╔══██╗╚══███╔╝"
	@echo " 	 ██║     ██║   ██║██████╔╝  ███╔╝ ███████║  ███╔╝ "
	@echo " 	 ██║     ██║   ██║██╔══██╗ ███╔╝  ██╔══██║ ███╔╝  "
	@echo " 	 ╚██████╗╚██████╔╝██║  ██║███████╗██║  ██║███████╗ "
	@echo " 	  ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝ "
	@echo " \033[0;35m                 Welcome to cub3D!                  "
	@echo " \033[1;37m      ~ A Journey Into 3D with Raycasting ~         \033[0m\n"
endef

all:			$(NAME)

bonus:			$(NAME_BONUS)

$(NAME) : $(OBJS) $(LIBFT)
	cc $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	printf "$(ERASE)$(GREEN)$@ made\n$(END)"
	$(PRINT_BANNER)

$(NAME_BONUS) : $(OBJSB) $(LIBFT)
	cc $(CFLAGS) $(OBJSB) $(LIBFT) $(LDFLAGS) -o $(NAME_BONUS)
	printf "$(ERASE)$(GREEN)$@ made\n$(END)"
	$(PRINT_BANNER)

$(OBJS_DIR)%.o : %.c $(INCS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@	
	printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(OBJSB_DIR)%.o : %.c $(INCS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@	
	printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(LIBFT) :
	make -C $(LIBFT_DIR) && make clean -C $(LIBFT_DIR)

clean :
	printf "$(YELLOW)$(OBJS_DIR) removed$(END)\n"
	$(RM) $(OBJS_DIR)
	printf "$(YELLOW)$(OBJSB_DIR) removed$(END)\n"
	$(RM) $(OBJSB_DIR)

fclean : clean
	printf "$(YELLOW)$(NAME) removed$(END)\n"
	printf "$(YELLOW)$(LIBFT) removed$(END)\n"
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re : fclean all

.PHONY : clean

.SILENT:
