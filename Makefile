NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline

S_DIR = srcs
O_DIR = .objs

SRCS = srcs/minishell.c srcs/banner.c srcs/free.c srcs/close.c srcs/slash.c \
	   srcs/error.c srcs/error_msg.c \
	   srcs/env.c srcs/fetch_cwd.c srcs/signal.c srcs/signal_handler.c srcs/term.c \
	   srcs/utils.c srcs/utils_two.c srcs/utils_main.c srcs/utils_main_init.c \
	   \
	   srcs/wildcards.c srcs/wildcards_utils.c srcs/wildcards_match.c srcs/wildcards_match_utils.c srcs/wildcards_merge.c \
	   \
	   srcs/prompt.c srcs/prompt_user.c srcs/prompt_host.c srcs/prompt_cwd.c srcs/prompt_uid.c srcs/prompt_merge.c \
	   srcs/prompt_merge_noenv.c \
	   \
	   srcs/exec.c srcs/exec_child.c srcs/exec_parent.c srcs/exec_redirections.c \
	   \
	   srcs/token_build.c srcs/token_type.c srcs/token_type_check.c srcs/token_split.c srcs/token_split_utils.c \
	   srcs/token_main.c srcs/input_handler.c  srcs/input_handler_result.c srcs/env_vars.c srcs/expansion_replace.c \
	   srcs/expansion_append.c srcs/expansion_unquoted.c srcs/expansion_utils.c srcs/heredoc_main.c srcs/heredoc_utils.c \
	   srcs/heredoc_file.c \
	   \
	   srcs/cmd_exec.c srcs/cmd_build.c srcs/cmd_args.c srcs/cmd_path.c srcs/cmd_redir.c srcs/cmd_redir_utils.c \
	   srcs/cmd_utils.c \
	   \
	   srcs/exit.c srcs/exit_seq.c srcs/atoll.c \
	   \
	   srcs/builtins/bt_cd.c srcs/builtins/bt_cd_arg.c srcs/builtins/bt_cd_noarg.c \
	   srcs/builtins/bt_cd_error.c srcs/builtins/bt_cd_error_2.c \
	   \
	   srcs/builtins/bt_export.c srcs/builtins/bt_export_cd.c \
	   srcs/builtins/bt_export_noarg.c srcs/builtins/bt_export_utils.c \
	   \
	   srcs/builtins/bt_env.c srcs/builtins/bt_unset.c \
	   srcs/builtins/bt_pwd.c srcs/builtins/bt_echo.c \
	   \
	   \
	   libft/libft_utils.c libft/libft_utils_two.c libft/libft_utils_three.c libft/ft_strdup.c libft/ft_strchr.c \
	   libft/gnl/get_next_line.c libft/gnl/get_next_line_utils.c \
	   \
	   libft/ft_split_minishell.c libft/ft_split_minishell_join.c \
	   libft/ft_split_minishell_quote.c libft/ft_split_minishell_noquote.c\
	   libft/ft_split_minishell_nextch.c libft/ft_split_minishell_strcnt.c \
	   libft/ft_split_minishell_strcnt_handle.c \
	   libft/ft_split_minishell_dispatch.c libft/ft_split_minishell_check_prev.c \
	   \
	   libft/ft_strjoin.c libft/ft_strjoin_spe.c libft/ft_strnstr.c libft/ft_atoi.c \
	   libft/ft_itoa.c libft/ft_substr.c libft/ft_split.c \
	   \
	   \
	   srcs/tester.c \

OBJS = $(SRCS:%.c=$(O_DIR)/%.o)

RESET = \033[0m
GREEN = \033[0;32m
RED	= \033[0;31m

COUNTER_FILE = .counter_makefile


all: reset_counter $(NAME)
	@if [ ! -f .built ]; then \
		echo "$(NAME): everything is already up to date."; \
	fi
	@rm -f .built .counter_makefile

bonus: all

$(O_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I./hdrs/ -c $< -o $@
	@count=`cat $(COUNTER_FILE)`; \
	count=`expr $$count + 1`; \
	echo $$count > $(COUNTER_FILE); \
	echo -n "\rminishell: compiling... $$count/$(words $(SRCS))"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I./hdrs/ $(OBJS) $(LIBS) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)$(NAME)$(RESET) has been compiled."
	@rm $(COUNTER_FILE)
	@touch .built

clean:
	@rm -rf $(O_DIR) $(COUNTER_FILE) .built
	@echo "$(NAME): ${RED}${O_DIR}${RESET} has been deleted."

fclean:
	@rm -rf $(O_DIR) $(NAME) $(COUNTER_FILE) .built
	@echo "$(NAME): ${RED}${O_DIR}${RESET} and ${RED}${NAME}${RESET} have been deleted."

re: fclean all

reset_counter:
	@echo 0 > $(COUNTER_FILE)

.PHONY: all bonus clean fclean re reset_counter
