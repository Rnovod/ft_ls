# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/24 19:41:22 by rnovodra          #+#    #+#              #
#    Updated: 2018/09/24 19:41:24 by rnovodra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS	+=	-s

NAME		=	ft_ls

SRC			=	main.c						\
				manage_file.c				\
				manage_options.c			\
				sort_by.c					\
				sort_files.c				\
				mode.c						\
				error.c						\
				print_current_files.c		\
				print_longform.c			\
				print_commas.c				\
				print_singlecol.c			\
				print_cols.c				\
				clear_files.c				\
				queue_dir.c					\
				extract_dirs_from_files.c	\
				print_all_dir.c				\
				attach.c					\
				rev_sort_by.c				\
				set_color.c					\
				reinit_data.c				\
				printname.c					\
				printtype.c					\
				realloc_files.c				\

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

SRC_DIR		=	./src/
OBJ_DIR		=	./obj/
INC_DIR		=	./inc/
LIB_DIR		=	./lib/

LIBFT_DIR	=	$(LIB_DIR)libft/

LIBFT		=	$(LIBFT_DIR)libft.a

PRINTF_DIR	=	$(LIB_DIR)ft_printf/

LIBPRINTF	=	$(PRINTF_DIR)libftprintf.a

HEADER		=	$(INC_DIR)ft_ls.h

HEAD_FLAGS	=	-I $(INC_DIR) -I $(PRINTF_DIR)$(INC_DIR) -I $(LIBFT_DIR)$(INC_DIR)

LIBS_FLAGS	=	-L $(PRINTF_DIR) -lft -L $(LIBFT_DIR) -lftprintf

CC_FLAGS	=	-Wall -Werror -Wextra -std=c11

CC			=	clang

BG			=	"\033[32;1m"
BR			=	"\033[31;1m"
EOC			=	"\033[0m"

all: $(LIBPRINTF) $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(LIBPRINTF):
	make -C $(PRINTF_DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS_FLAGS)
	echo ${BG}"ft_ls is ready"${EOC}

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c $(HEADER)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(HEAD_FLAGS) 
	echo ${BG}"[✓] $<"

clean:
	make clean -C $(PRINTF_DIR)
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ)
	echo ${BR}"[✗] clean"

fclean: clean
	make fclean -C $(PRINTF_DIR)
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)
	rm -rf $(OBJ_DIR)
	echo ${BR}"[✗] $(NAME)"

re: fclean all

vpath %.c $(SRC_DIR)

.PHONY: all fclean clean re $(LIBPRINTF) $(LIBFT)

