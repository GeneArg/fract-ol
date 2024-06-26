NAME			:= fractol
NICKNAME		:= FRACTOL

# Directories
HDR_DIR			:= include
LIB_DIR			:= lib
SRC_DIR			:= src
OBJ_DIR			:= obj
BONUS_DIR		:= bonus
BONUS_OBJ_DIR	:= bonus_obj

# Libft
LIBFT_DIR		:= libft
LIBFT			:= ${LIBFT_DIR}/libft.a

# MLX42
MLX_DIR			:= MLX42
MLX				:= ${MLX_DIR}/build/libmlx42.a

ifeq (${shell uname}, Linux)
	MLX_FLAGS	:= -L ${MLX_DIR}/build -lmlx42 -lglfw -lm
else ifeq (${shell uname}, Darwin)
	MLX_FLAGS	:= -lglfw -L "/opt/homebrew/Cellar/glfw/3.4/lib/"
else
	MLX_FLAGS	:= -lglfw -L "/Users/${USER}/.brew/opt/glfw/lib/"
endif

# Compiler flags
CC				:= cc
CFLAGS			:= -Wall -Werror -Wextra
INCL			:= -I ${HDR_DIR}/ -I ${LIBFT_DIR}/include/ -I ${MLX_DIR}/include/MLX42/

# Includes
HDR_FILES :=	fractol.h 		\

# Files
SRC_FILES :=	fractol.c \
				fractals.c \
				handle_events.c \
				init.c \
				utils.c \

BONUS_SRC_FILES :=	fractol_bonus.c \
					fractals_bonus.c \
					burning_ship_bonus.c \
					handle_events_bonus.c \
					init_bonus.c \
					utils_bonus.c \

SRC				:= ${addprefix ${SRC_DIR}/, ${SRC_FILES}}
OBJ				:= ${addprefix ${OBJ_DIR}/, ${SRC_FILES:.c=.o}}
HDR				:= ${addprefix ${HDR_DIR}/, ${HDR_FILES}}
BONUS_SRC		:= ${addprefix ${BONUS_DIR}/, ${BONUS_SRC_FILES}}
BONUS_OBJ		:= ${addprefix ${BONUS_OBJ_DIR}/, ${BONUS_SRC_FILES:.c=.o}}

# Colours
GREEN			:= \033[32;1m
YELLOW			:= \033[33;1m
RED				:= \033[31;1m
BOLD			:= \033[1m
RESET			:= \033[0m

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@ printf "%b%s%b" "$(YELLOW)$(BOLD)" "Compiling $(NICKNAME)..." "$(RESET)"
	@ $(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) $(MLX) -o $(NAME)
	@ printf "\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "		[OK]" "$(RESET)"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@ $(CC) $(CFLAGS) $(INCL) -c $< -o $@

$(OBJ_DIR):
	@ mkdir -p $(OBJ_DIR)

$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c | $(BONUS_OBJ_DIR)
	@ $(CC) $(CFLAGS) $(INCL) -c $< -o $@

$(BONUS_OBJ_DIR):
	@ mkdir -p $(BONUS_OBJ_DIR)

$(LIBFT):
	@ printf "%b%s%b" "$(YELLOW)$(BOLD)" "Compiling and archiving LIBFT..." "$(RESET)"
	@ make -C $(LIBFT_DIR)														> /dev/null
	@ printf "\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "[OK]" "$(RESET)"

$(MLX):
	@ printf "%b%s%b" "$(YELLOW)$(BOLD)" "Compiling and archiving MLX42..." "$(RESET)"
	@ cmake $(MLX_DIR) -B $(MLX_DIR)/build										> /dev/null
	@ make -C $(MLX_DIR)/build -j4												> /dev/null
	@ printf "\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "[OK]" "$(RESET)"

bonus: $(LIBFT) $(MLX) $(BONUS_OBJ)
	@ printf "%b%s%b" "$(YELLOW)$(BOLD)" "Compiling BONUS..." "$(RESET)"
	@ $(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) $(MLX_FLAGS) $(MLX) -o $(NAME)
	@ printf "\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "		[OK]" "$(RESET)"

clean:
	@ echo "$(RED)$(BOLD)Cleaning LIBFT...$(RESET)"
	@ make clean -C $(LIBFT_DIR)												> /dev/null

	@ echo "$(RED)$(BOLD)Cleaning $(NICKNAME)...$(RESET)"
	@ rm -rf $(OBJ) $(BONUS_OBJ)
	@ rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)

fclean:
	@ echo "$(RED)$(BOLD)Fully cleaning LIBFT...$(RESET)"
	@ make fclean -C $(LIBFT_DIR)												> /dev/null

	@ echo "$(RED)$(BOLD)Fully cleaning MLX42...$(RESET)"
	@ make clean -C $(MLX_DIR)/build											> /dev/null

	@ echo "$(RED)$(BOLD)Fully cleaning $(NICKNAME)...$(RESET)"
	@ rm -rf ${NAME}
	@ rm -rf $(OBJ) $(BONUS_OBJ)
	@ rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)

re: fclean $(NAME)

.PHONY: all clean fclean re bonus
