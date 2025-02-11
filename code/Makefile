# Variables
CC = clang
CFLAGS = -g -fsanitize=address

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(LIBFT_DIR)

SRC_DIR = ./src
SRCS =	$(SRC_DIR)/parseo.c\
		$(SRC_DIR)/aux.c\
		$(SRC_DIR)/delete_quotes.c\
		$(SRC_DIR)/expand_quotes.c\
		$(SRC_DIR)/token_list_func.c\
		$(SRC_DIR)/tokenize_functions.c\
		$(SRC_DIR)/tokenize_aux.c\
		$(SRC_DIR)/tokenize.c\
		$(SRC_DIR)/command_lst.c\
		$(SRC_DIR)/command_lst2.c\
		$(SRC_DIR)/search_path.c\
		$(SRC_DIR)/execute.c\
		$(SRC_DIR)/ex_single_cmd.c\
		$(SRC_DIR)/command_types.c\
#		$(SRC_DIR)/ft_utils.c\

OBJ_DIR = ./objs
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = parseo

#OBJ_DIR_BONUS = ./objs_bonus
#BONUS_DIR = ./src
#BONUS_SRCS = $(BONUS_DIR)/bonus/pipex_bonus.c\
			$(BONUS_DIR)/ft_execute.c\
			$(BONUS_DIR)/ft_process.c\
			$(BONUS_DIR)/ft_utils.c\

#BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(OBJ_DIR_BONUS)/%.o)

#BONUS_NAME = pipex_bonus

# Colors
RED     			= \033[0;31m
GREEN   			= \033[0;32m
YELLOW  			= \033[0;33m
CYAN    			= \033[0;36m
WHITE   			= \033[0;37m
RESET   			= \033[0m

# Reglas
all: $(NAME)

#bonus: $(BONUS_NAME)

#$(BONUS_NAME): $(OBJ_DIR_BONUS) $(LIBFT) $(BONUS_OBJS)
#	@printf "$(CYAN)[Building Bonus] Creating $(BONUS_NAME)...\n$(RESET)"
#	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)
#	@printf "$(GREEN)[Success] $(BONUS_NAME) created successfully!\n$(RESET)"

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJS)
	@printf "$(CYAN)[Building Main] Creating $(NAME)...\n$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@printf "$(GREEN)[Success] $(NAME) created successfully!\n$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)[Compiling]$(RESET) $<\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#$(OBJ_DIR_BONUS)/%.o: $(BONUS_DIR)/%.c | $(OBJ_DIR_BONUS)
#	@mkdir -p $(dir $@)
#	@printf "$(YELLOW)[Compiling Bonus]$(RESET) $<\n"
#	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@printf "$(CYAN)[Directory] Creating object directory $(OBJ_DIR)...\n$(RESET)"
	@mkdir -p $(OBJ_DIR)

#$(OBJ_DIR_BONUS):
#	@printf "$(CYAN)[Directory] Creating bonus object directory $(OBJ_DIR_BONUS)...\n$(RESET)"
#	@mkdir -p $(OBJ_DIR_BONUS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFT_DIR) bonus
	@$(MAKE) -C $(LIBFT_DIR) clean
	@printf "$(GREEN)[Libft Ready] Libft compiled successfully!\n$(RESET)"

clean:
	@printf "$(RED)[Cleaning] Removing object files...\n$(RESET)"
	@rm -rf $(OBJ_DIR)
	@printf "$(GREEN)[Cleaned] Object files removed successfully!\n$(RESET)"

fclean: clean
	@printf "$(RED)[Full Clean] Removing binaries and $(LIBFT)...\n$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@printf "$(GREEN)[Cleaned] All binaries and libraries removed successfully!\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
