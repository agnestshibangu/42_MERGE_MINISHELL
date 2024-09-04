NAME = minishell
DIR_SRC = src/
DIR_OBJ = obj/
CC = cc -g
CFLAGS = -Wall -Wextra -Werror 
LDFLAGS = -lreadline
RM = rm -f

SRCS =  $(wildcard $(DIR_SRC)*.c) \
		$(wildcard $(DIR_SRC)/parsing/*.c) \
		$(wildcard $(DIR_SRC)/exec/*.c) \
		$(wildcard $(DIR_SRC)/libft/*.c) \
		$(wildcard $(DIR_SRC)/builtins/*.c) \
		$(wildcard $(DIR_SRC)/pipex/*.c) \

OBJS = $(SRCS:$(DIR_SRC)%.c=$(DIR_OBJ)%.o)

all: $(NAME)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	@echo "  "
	@echo "  "
	@echo "MINISHELL"
	@echo "  "
	@echo "  "

clean:
	@echo "🧹 ALL FILES HAVE BEEN DELETED 🧹"
	rm -rf $(DIR_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all


# # Program name
# NAME	=  minishell

# # Compiler options
# CC		= cc -g
# CFLAGS	= -Wall -Wextra -Werror

# #libft
# LIBFT_DIR := ./libft/
# LIBFT_SRCS := $(wildcard $(LIBFT_DIR)*.c)
# LIBFT_OBJS := $(patsubst $(LIBFT_DIR)%.c, $(LIBFT_DIR)%.o, $(LIBFT_SRCS))

# SRC		= 	src/init.c \
# 			src/main.c \
# 			src/builtins/cd_builtins.c \
# 			src/builtins/echo_builtins.c \
# 			src/builtins/env_builtins.c \
# 			src/builtins/exit_builtins.c \
# 			src/builtins/pwd_builtins.c \
# 			src/builtins/unset_builtins.c \
# 			src/builtins/export_builtins.c \
# 			src/pipex/pipex.c \
# 			src/pipex/gnl_function.c \
# 			src/pipex/gnl.c \
# 			src/run/run_builtins.c \
# 			src/run/run_utils.c \
# 			src/run/run_exec.c \
# 			src/free.c \
# 			src/signal.c \

# OBJ		= $(SRC:.c=.o)

# all : $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@ 

# $(LIBFT_OBJS): $(LIBFT_SRCS)
# 	@make -C $(LIBFT_DIR)

# # Compiling minishell
# $(NAME): $(OBJ) $(LIBFT_OBJS)
# 	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT_OBJS) -lreadline
# 	@echo "  "
# 	@echo "  "
# 	@echo "MINISHELL"
# 	@echo "  "
# 	@echo "  "


# clean:
# 	@echo "🧹 ALL FILES HAVE BEEN DELETED 🧹"
# 	@rm -rf $(OBJ)


# fclean: clean
# 	@echo "🧹 ALL FILES HAVE BEEN DELETED 🧹"
# 	@rm -rf $(NAME)

# re: fclean all

# .PHONY: all clean fclean re bonus
