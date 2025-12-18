# Mini RT
# by joao-alm

NAME   		= miniRT
CC     		= cc
CFLAGS 		= -Wall -Werror -Wextra -Ofast -march=native -Wno-incompatible-pointer-types
O_DIR		= obj
HEADER		= $(O_DIR)/.header

all: $(NAME)

SRC_PARSER	= src/parser/objects/parse_cone_bonus.c \
			  src/parser/objects/parse_cylinder.c \
			  src/parser/objects/parse_plane.c \
			  src/parser/objects/parse_sphere.c \
			  src/parser/parse_elements.c \
			  src/parser/parse_options_bonus.c \
			  src/parser/parse_utils.c \
			  src/parser/parse_validation.c \
			  src/parser/parser.c

SRC_RENDER	= src/render/bump/bump_bonus.c \
			  src/render/bump/bump_normal_bonus.c \
			  src/render/bump/bump_uv_bonus.c \
			  src/render/closest_hit/cone/hit_cone_bonus.c \
			  src/render/closest_hit/cone/intersect_cone_bonus.c \
			  src/render/closest_hit/cylinder/hit_cylinder.c \
			  src/render/closest_hit/cylinder/intersect_cylinder.c \
			  src/render/closest_hit/plane/intersect_plane.c \
			  src/render/closest_hit/plane/hit_plane.c \
			  src/render/closest_hit/sphere/intersect_sphere.c \
			  src/render/closest_hit/sphere/hit_sphere.c \
			  src/render/closest_hit/closest_hit.c \
			  src/render/lighting/lighting.c \
			  src/render/lighting/specular_bonus.c \
			  src/render/texture/texture_bonus.c \
			  src/render/texture/texture_uv_bonus.c \
			  src/render/pattern_bonus.c \
			  src/render/render.c

SRC_UTIL	= src/util/color/color_utils.c \
			  src/util/color/color.c \
			  src/util/mlx/images_bonus.c \
			  src/util/mlx/keyhook.c \
			  src/util/mlx/mlx_util.c \
			  src/util/vec3/vec3_utils.c \
			  src/util/vec3/vec3.c \

SRC			= src/main.c $(SRC_PARSER) $(SRC_RENDER) $(SRC_UTIL)
OBJ 		= $(SRC:%.c=$(O_DIR)/%.o)

libft:
	@git clone https://github.com/42-joaorodrigues/mylib.git libft > /dev/null 2>&1
	@echo "Libft downloaded successfully"

mlx:
	@git clone https://github.com/42-joaorodrigues/compiled_mlx.git mlx > /dev/null 2>&1
	@echo "Mlx downloaded successfully"

$(O_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -Iinc -Imlx -Ilibft/inc

$(NAME): $(HEADER) libft mlx $(OBJ)
	@make -C libft --no-print-directory > /dev/null 2>&1
	@echo "Libft compiled successfully"
#	@make -C mlx --no-print-directory > /dev/null 2>&1
#	@echo "Mlx compiled successfully"
	@$(CC) $(CFLAGS) $(OBJ) -o $@ -Llibft -lft -Lmlx -lmlx -lXext -lX11 -lm
	@echo "MiniRT compiled successfully"

bonus: $(NAME)

clean:
	@rm -rf $(O_DIR)
	@echo "MiniRT objects removed successfully"

fclean: libft mlx
	@rm -rf $(O_DIR)
	@rm -rf $(NAME)
	@echo "MiniRT objects & executable removed successfully"
	@make -C libft fclean --no-print-directory > /dev/null 2>&1
	@echo "Libft objects & executable removed successfully"
#	@make -C mlx clean --no-print-directory > /dev/null 2>&1
#	@echo "Mlx objects & executable removed successfully"

re: fclean all

$(HEADER):
	@mkdir -p $(dir $@)
	@touch $@
	@printf "\n"
	@printf "█████████████████████████████\n"
	@printf "        ██  █▓███  ██  █▓███ \n"
	@printf "joao-alm  █████      █████   \n"
	@printf "╔╦╗┬┌┐┌┬ ╦═╗┌┬┐\n"
	@printf "║║║│││││ ╠╦╝ │ \n"
	@printf "╩ ╩┴┘└┘┴ ╩╚═ ┴ \n\n"

.PHONY: all bonus clean fclean re