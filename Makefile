# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/29 22:06:46 by hbettal           #+#    #+#              #
#    Updated: 2024/10/13 16:51:22 by hbettal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= $(shell find src -type f -name "*.c")
OBJS_DIR		= obj/
OBJS 			= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
INCS_DIR		= includes/
INCS			= $(INCS_DIR)cub3d.h $(INCS_DIR)struct.h $(INCS_DIR).MLX42.h
LIBFT_DIR		= lib/libft/
LIBFT			= $(LIBFT_DIR)libft.a
CFLAGS			= -I$(INCS_DIR) -I$(LIBFT_DIR) 
CFLAGS			+= -Wall -Werror -Wextra -g -fsanitize=address
NAME			= cub3d
RM			= rm -rf
ERASE			= \033[2K\r
BLUE			= \033[34m
YELLOW			= \033[33m
GREEN			= \033[32m
END			= \033[0m
LDFLAGS			= -framework OpenGL -framework AppKit libmlx42.a -Iinclude -lglfw -L"$(shell brew --prefix glfw)/lib"

# Banner
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

$(NAME) : $(OBJS) $(LIBFT)
	cc $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	printf "$(ERASE)$(GREEN)$@ made\n$(END)"
	$(PRINT_BANNER)

$(OBJS_DIR)%.o : %.c $(INCS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@	
	printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(LIBFT) :
	make -C $(LIBFT_DIR) && make clean -C $(LIBFT_DIR)      

clean :
	printf "$(YELLOW)$(OBJS_DIR) removed$(END)\n"
	$(RM) $(OBJS_DIR)


fclean : clean
	printf "$(YELLOW)$(NAME) removed$(END)\n"
	printf "$(YELLOW)$(LIBFT) removed$(END)\n"
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re : fclean all

.PHONY : clean


.SILENT:
