# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 14:08:21 by joao-alm          #+#    #+#              #
#    Updated: 2025/11/05 17:27:42 by joao-alm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT
BNAME	= miniRT_bonus

CC		= cc
FLAGS	= -Wall -Wextra -Werror \
		  -O3 -march=native -ffast-math \
		  -Wno-incompatible-pointer-types

# libs
MLX		= lib/mlx/libmlx.a
MLXINC	= -I lib/mlx
MLXL	= -Llib/mlx -lmlx -lXext -lX11 -lm

LIBFT	= lib/libft/libft.a
LIBFTIN	= -I lib/libft
LIBFTL	= -Llib/libft -lft

# mandatory files
# INC		= -I mandatory/inc $(MLXINC) $(LIBFTIN)
# SRC		=
# SRC		:= $(addprefix mandatory/src/, $(SRC))
# OBJ		= $(SRC:%.c=obj/%.o)

# bonus files
BINC	= -I bonus/inc
BSRC	= main_bonus.c

BPARSER	= parser_bonus.c \
		  parse_elements_bonus.c \
		  parse_objects_bonus.c \
		  parse_utils_bonus.c \
		  parse_validation_bonus.c \
		  parse_options_bonus.c
BPARSER	:= $(addprefix parser/, $(BPARSER))

BRENDER	= render_bonus.c \
		  lighting_bonus.c \
		  find_closest_hit_bonus.c \
		  pattern_bonus.c \
		  cylinder/hit_cylinder_bonus.c \
		  cylinder/intersect_cylinder_bonus.c \
		  plane/hit_plane_bonus.c \
		  plane/intersect_plane_bonus.c \
		  sphere/hit_sphere_bonus.c \
		  sphere/intersect_sphere_bonus.c \
		  cone/hit_cone_bonus.c \
		  cone/intersect_cone_bonus.c
BRENDER	:= $(addprefix render/, $(BRENDER))

BUTIL	= color_bonus.c \
		  mlx_helper_bonus.c \
		  vec3_bonus.c \
		  keyhook_bonus.c
BUTIL	:= $(addprefix util/, $(BUTIL))

BSRC	+= $(BPARSER) $(BRENDER) $(BUTIL)
BSRC	:= $(addprefix bonus/src/, $(BSRC))
BOBJ	= $(BSRC:%.c=obj/%.o)

# compile libs and fdf
all: $(MLX) $(LIBFT) $(BNAME)

# compile libs
$(MLX):
	make -C lib/mlx

$(LIBFT):
	make -C lib/libft

# compile from .c to .o inside obj/
obj/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@ $(MLXINC) $(LIBFTIN) $(BINC)

# compile fdf
# $(NAME): $(OBJ)
# 	$(CC) $^ -o $@ $(MLXL) $(LIBFTL)

# compile libs and fdf_bonus
# bonus: $(MLX) $(LIBFT) $(BNAME)

# compile fdf_bonus
$(BNAME): $(BOBJ)
	$(CC) $^ -o $@ $(MLXL) $(LIBFTL)

clean:
	make -C lib/libft clean
	rm -rf obj

fclean: clean
# 	make -C lib/mlx clean
	make -C lib/libft fclean
	rm -rf $(NAME)
	rm -rf $(BNAME)

re: fclean all bonus

.PHONY: all clean fclean re bonus
