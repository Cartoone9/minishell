/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:51:12 by *******           #+#    #+#             */
/*   Updated: 2025/04/18 15:26:31 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef _GNU_SOURCE
#  define _GNU_SOURCE
# endif

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define RESET "\033[0m"
# define RED "\033[1;38;2;233;0;36m"
# define ORANGE "\033[1;38;2;255;129;0m"
# define YELLOW "\033[1;38;2;255;200;50m"
# define GREEN "\033[1;38;2;75;205;82m"
# define TEAL "\033[1;38;2;0;180;210m"
# define BLUE "\033[1;38;2;0;117;226m"
# define PURPLE "\033[1;38;2;108;86;249m"
# define MAGENTA "\033[1;38;2;181;51;251m"
# define VIOLET "\033[1;38;2;204;102;255m"

# define HDOC_FILE ".temporary_heredoc_minishell"

# define ERROR -1

// token type IDs :
// redirections, '<', '<<', '>', '>>', '|'
# define IN_ID 1
# define HDOC_IN_ID 2
# define OUT_ID 3
# define A_OUT_ID 4
# define PIPE_ID 5
// infile, outfile, hdoc infile
# define INFILE_ID 7
# define OUTFILE_ID 8
# define HEOF_ID 9
// arg, cmd
# define ARG_ID 10
# define CMD_ID 11

// ARG_MAX (2MB usually) minus 16KB
// as a safeguard for the program to run
// (2097152 - 16384 = 2080768)
# define ARG_MAX_SIZE 2080768

typedef struct s_tkn
{
	int							type;
	char						*arg;
	struct s_tkn				*next;
}								t_tkn;

typedef struct s_hdoc
{
	size_t						saved;
	int							hdoc_filen;
	char						*hdoc_eof;
	struct s_hdoc				*next;
}								t_hdoc;

typedef struct s_cmd
{
	char						**args;
	char						*path;
	pid_t						pid;
	int							fd_in;
	int							fd_out;
	int							pipe[2];
	size_t						error;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_data
{
	char						**env;
	char						**path;
	t_tkn						*tkn_list;
	t_hdoc						*hdoc_list;
	t_cmd						*cmd_list;
	char						*prompt;
	char						*input;
	char						*full_input;
	int							error;
	int							exit_status;
	int							envless;
}								t_data;

typedef struct s_sizet
{
	size_t						i;
	size_t						j;
	size_t						k;
	size_t						strr_len;
	size_t						space;
	int							wild;
	int							placehd;
}								t_sizet;

extern volatile sig_atomic_t	g_signal;
extern int						g_stdin_save;

// ----------------------------------- UI ----------------------------------

// PROMPT :
char							*ft_make_prompt(t_data *data);
char							*ft_set_user(t_data *data, size_t *which);
char							*ft_set_host(t_data *data, size_t *which);
char							*ft_set_cwd(t_data *data, size_t *which);
char							*ft_build_cwd(t_data *data);
char							*ft_getcwd_alloc(void);
char							*ft_remove_home(char *full_cwd, t_data *data);
int								ft_check_home_prefix(char *full_cwd,
									char **home_ptr, size_t home_len);
char							*ft_build_tilde_path(char *partial_cwd);
char							*ft_get_username(t_data *data);
int								ft_check_deeper_uid(char **loginuid);
int								ft_process_status_line(char **buffer_ptr,
									char **loginuid, int fd);
char							*ft_extract_uid_from_buffer(char *buffer);
char							*ft_extract_from_etcpass(int which);
char							*ft_get_validated_loginuid(void);
char							*ft_find_and_extract(int fd, char *loginuid,
									int which);
char							*ft_matching_uid(char *temp, int which);
char							*ft_extract_field(char *line, int which);
char							*ft_extract_field_home(char *line);

char							*ft_make_hostname(t_data *data);
size_t							ft_short_hostname(char *buffer);

// ----------------------------------- UI ----------------------------------
//
//
//
// --------------------------------- UTILS ---------------------------------

// ID :
int								ft_is_a_directory(char *pathname);
int								ft_lookslike_directory(char *str);
int								ft_is_a_pipe(int fd);
int								ft_is_a_file(int fd);
int								ft_has_only_digit(char *str);
int								ft_is_separator(char check_char, char c,
									char c_2);
int								ft_is_separator_nospace(char check_char);
int								ft_str_is_a_redirection(char *str);
// INIT :
void							ft_init_strr(char ***strr, size_t len);
int								ft_init_szt(const char *s, t_sizet *szt);
void							ft_init_buffer(char *buffer);
int								ft_full_init_main(int ac, char **av,
									char **envp, t_data *data);
void							ft_main_signals(void);
// LIBFT MODIF :
char							*ft_strjoin_prompt(char const *s1,
									char const *s2, char const *s3);
void							ft_append_user(char *ret, size_t ret_size,
									const char *s1);
void							ft_append_host(char *ret, size_t ret_size,
									const char *s2);
void							ft_append_cwd(char *ret, size_t ret_size,
									const char *s3);
void							ft_append_end(char *ret, size_t ret_size);
char							*ft_strjoin_prompt_noenv(char const *s1,
									char const *s2, char const *s3);

// --------------------------------- UTILS ---------------------------------
//
//
//
// --------------------------------- PARSING --------------------------------

// SPLIT MINISHELL :
char							**ft_split_minishell(char const *s,
									t_data *data);
int								ft_split_suite(char ***strr, const char *s,
									t_sizet *szt, t_data *data);
int								ft_process_word_loop(char ***strr,
									const char *s, t_sizet *szt, t_data *data);
int								ft_replace_strr_by_empty(char ***strr,
									int which);
int								ft_process_non_quote_segment(char ***strr,
									const char *s, t_sizet *szt, t_data *data);
int								ft_handle_single_quote_case(char ***strr,
									const char *s, t_sizet *szt);
int								ft_handle_double_quote_case(char ***strr,
									const char *s, t_sizet *szt, t_data *data);
int								ft_handle_non_quote_case(char ***strr,
									const char *s, t_sizet *szt, t_data *data);
int								ft_allocate_and_copy_token(char **strr,
									const char *s, t_sizet *szt,
									size_t malloc_size);
int								ft_check_prev_placeholder(char ***strr,
									t_sizet *szt, t_data *data, int unquoted);
int								ft_check_prev_placeholder_suite(char ***strr,
									t_sizet *szt, t_data *data, int unquoted);
int								ft_join_adjacent_words(char ***strr,
									t_sizet *szt, int placehd);
int								ft_join_with_placeholder(char ***strr,
									t_sizet *szt, int placehd);
int								ft_check_prev_wildcard(char ***strr,
									t_sizet *szt);
int								ft_previous_is_redirection(char *str);
int								ft_split_no_quotes(char **strr, const char *s,
									t_sizet *szt);
int								ft_allocate_and_copy_token(char **strr,
									const char *s, t_sizet *szt,
									size_t malloc_size);
int								ft_single_quotes(char **strr, const char *s,
									size_t *i, size_t *j);
int								ft_double_quotes(char **strr, const char *s,
									size_t *i, size_t *j);
size_t							ft_nextch_s_quote(const char *str, char c);
size_t							ft_nextch_d_quote(const char *str, char c);
size_t							ft_nextch_spe(const char *str);
size_t							ft_nextch_noquote(const char *str, char d,
									char e);
size_t							ft_strcnt_spe(const char *str, char c,
									char c_2);
void							ft_strcnt_dispatch(const char *str,
									size_t *i_ptr, size_t str_len);
void							ft_strcnt_handle_quotes(const char *str,
									size_t *i_ptr, size_t str_len);
void							ft_strcnt_handle_operator(const char *str,
									size_t *i_ptr, size_t str_len);
void							ft_strcnt_handle_dollar(const char *str,
									size_t *i_ptr, size_t str_len);
void							ft_strcnt_handle_star(const char *str,
									size_t *i_ptr, size_t str_len);

// TOKEN LIST :
t_tkn							*ft_build_tkn_list(char *input, t_data *data);
void							ft_what_type(t_tkn *tkn_list);
int								ft_is_a_redirection(t_tkn *tkn_list);
void							ft_assign_redirection_type(t_tkn *tkn_list,
									size_t *cmd);
void							ft_assign_main_type(t_tkn *tkn_list,
									t_tkn *previous, size_t *cmd);
void							ft_handle_other_type(t_tkn *tkn_list,
									int *loop);
int								ft_cutoff_subtoken(t_tkn *tkn_list, char *arg,
									int which);
int								ft_cutoff_pos(char *arg, int which);
char							*ft_make_old_token_arg(char *arg,
									size_t cutoff);
int								ft_insert_new_token(t_tkn **tkn_list,
									char *new_arg);
int								ft_get_input(t_data *data, int piped);
int								ft_setup_prompt_and_signals(t_data *data,
									int piped);
int								ft_handle_input_result(t_data *data, int piped);
int								ft_check_missing_quotes(char *str);
int								ft_update_quote_state(char c, char next_c,
									int *s_quote, int *d_quote);
int								ft_handle_post_read_signals(t_data *data);
void							ft_merge_data_input(t_data *data);
int								ft_tokenization(t_data *data);
int								ft_tokenize_current_input(t_data *data);
int								ft_build_or_append_tkn_list(t_data *data);
int								ft_process_heredocs(t_data *data);
int								ft_islast_pipe(t_tkn *tkn_list);
char							*ft_getenv(t_data *data, char *key);
char							*ft_search_env_for_key(t_data *data,
									const char *full_key, size_t key_len);
char							*ft_extract_env_value(const char *env_str,
									size_t key_len);
int								ft_replace_placeholders(t_data *data,
									char **str);
int								ft_process_segment_placehd(t_data *data,
									char **new_arg, char *arg,
									size_t current_i);
int								ft_handle_placeholder_part(t_data *data,
									char **new_arg, char *arg,
									size_t dollar_idx);
int								ft_finalize_replacement(char **new_arg_ptr,
									char **str_ptr,
									char *arg_orig, size_t suffix_idx);
int								ft_append_suffix(char **new_arg_ptr,
									char **str_ptr, char *suffix_start);
int								ft_append_prefix(char **new_arg,
									char *prefix_start, int len);
int								ft_append_dollar_sign(char **new_arg);
int								ft_append_exit_status(t_data *data,
									char **new_arg);
int								ft_append_env_case(t_data *data, char **new_arg,
									char *start, size_t len);
int								ft_append_literal_placeholder(char **new_arg,
									char *placeholder_start,
									size_t placeholder_len);
int								ft_replace_placeholders_unquoted(t_data *data,
									char ***strr, size_t j, t_sizet *szt);
int								ft_handle_dollar_question(t_data *data,
									char ***strr, size_t j);
int								ft_handle_other_case(t_data *data,
									char ***strr, t_sizet *szt);
int								ft_handle_empty_case(char ***strr, size_t j,
									t_sizet *szt, char *new_arg);
int								ft_handle_split_and_merge(char ***strr,
									t_sizet *szt, char *new_arg);
int								ft_join_and_update(char **dst, char *src);
size_t							ft_strlen_placeholder(char *str);
int								ft_wait_for_hdoc(t_data *data,
									char *delimiter_orig);
int								ft_init_hdoc_read(t_data *data, char *del_orig,
									char **buf, char **del);
int								ft_hdoc_readline_loop(t_data *data,
									char *del_orig, char **buf, char *del);
int								ft_process_hdoc_line(t_data *data,
									char *del, char *del_orig);
int								ft_finalize_hdoc(t_data *data,
									char **buffer_ptr, char **delimiter);
int								ft_isthere_hdoc(t_data *data);
size_t							ft_how_manyhdoc(t_data *data);
int								ft_make_hdoc_node(t_data *data, char *eof);
int								ft_append_to_hdoc_buffer(char **buffer,
									char **line_ptr);
int								ft_temp_file(t_data *data, char **buffer_ptr);
t_hdoc							*ft_find_hdoc_node(t_hdoc *list);
char							*ft_generate_hdoc_filename(t_hdoc *node,
									char **buf_ptr);

// CMD LIST :
int								ft_replace_w_path(t_cmd *cursor_cmd,
									t_data *data);
void							ft_init_dots(int *dot, int *dot_2,
									t_cmd *cmd);
int								ft_search_path(t_cmd *cursor_cmd, char **paths,
									char *cmd_name);
int								ft_handle_non_builtin_no_path(t_cmd *cmd);
int								ft_handle_non_builtin_with_path(t_cmd *cmd,
									t_data *data);
int								ft_build_cmd_list(t_data *data);
int								ft_init_build_vars(t_data *data,
									t_cmd **cmd_ptr,
									t_hdoc **hdoc_ptr, t_tkn **tkn_ptr);
int								ft_process_token_loop(t_data *data,
									t_cmd **cmd_ptr, t_tkn *tkn,
									t_hdoc **hdoc_ptr);
int								ft_ensure_cmd_args(t_cmd *cmd,
									t_tkn *current_tkn, size_t *i_ptr);
int								ft_new_cmd_node(t_data *data);
int								ft_process_arg_cmd(t_cmd *cmd, t_tkn *tkn,
									size_t *i_ptr);
int								ft_process_pipe(t_data *data, t_cmd **cmd_ptr,
									size_t *i_ptr);
int								ft_allocate_cmd_args(t_cmd *cmd, t_tkn *tkn);
size_t							ft_args_size(t_tkn *cursor_tkn);
void							ft_cmd_node_null(t_cmd *new_cmd);
int								ft_convert_first_arg(t_data *data);
int								ft_process_command_node(t_cmd *cmd,
									t_data *data, size_t pipeline);
int								ft_handle_valid_command_arg(t_cmd *cmd,
									t_data *data, size_t papipeline);
int								ft_set_builtin_path(t_cmd *cmd,
									int builtin, size_t pipeline);
int								ft_is_builtin_path(char *arg);
int								ft_handle_redir_token(t_data *data, t_cmd *cmd,
									t_tkn **tkn_ptr, t_hdoc **hdoc_ptr);
int								ft_handle_redirection(t_data *data, t_cmd *cmd,
									t_tkn *tkn, t_hdoc **hdoc_ptr);
int								ft_process_input_redir(t_data *data,
									t_cmd *cmd, t_tkn *tkn,
									t_hdoc *hdoc_node);
int								ft_process_output_redir(t_data *data,
									t_cmd *cmd, t_tkn *tkn);
int								ft_check_redir_ambiguous(t_data *data,
									t_cmd *cmd, char **filename_ptr);
void							ft_handle_open_error(t_data *data,
									t_cmd *cmd, char *filename,
									int fd_to_close);
int								ft_open_and_handle_input(t_data *data,
									t_cmd *cmd, t_tkn *tkn,
									char *filename);
int								ft_open_output_file(t_data *data,
									t_cmd *cmd, char *filename,
									int open_flags);
int								ft_another_output(t_tkn *cursor_tkn);
int								ft_another_input(t_tkn *cursor_tkn);
int								ft_clean_filename(char **str);
int								ft_clean_eof(char **str);
size_t							ft_process_escapes(const char *orig,
									char *buf, size_t *ret);
char							*ft_filename_hdoc(t_hdoc *cursor_hdoc);

// --------------------------------- PARSING --------------------------------
//
//
//
// --------------------------------- SLASH --------------------------------

int								ft_remove_slash(t_data *data);
int								ft_process_command_args(t_cmd *cmd);
int								ft_process_single_arg(char **arg_ptr);
int								ft_slash_matching(char **arg_ptr, size_t j);
size_t							ft_count_slash(char *str);

// --------------------------------- SLASH --------------------------------
//
//
//

// libft_utils
int								ft_strncmp(const char *s1, const char *s2,
									size_t n);
char							**ft_split(char const *s, char c);
size_t							ft_strlcpy(char *dst, const char *src,
									size_t siz);
int								ft_strlen(const char *str);
size_t							ft_strlcat(char *dest, const char *src,
									size_t buf);
char							*get_next_line(int fd, int clear);
char							*ft_strdup(const char *src);
char							*ft_strchr(const char *str, int c);
char							*ft_strchr_second(const char *str, int c);
int								ft_strchr_int(const char *str, int c);
char							**ft_split_minishell(char const *s,
									t_data *data);
size_t							ft_strcnt(const char *str, char c);
char							*ft_strjoin(char const *s1, char const *s2);
char							*ft_strjoin_input(char *s1, char *s2);
char							*ft_strjoin_input_copy(char *ret, char *s1,
									char *s2);
char							*ft_strnstr(const char *dest, const char *src,
									size_t n);
char							*ft_strnstr_end(const char *dest,
									const char *src, size_t n);
int								ft_atoi(const char *str);
long long						ft_atol(const char *str);
char							*ft_itoa(int n);
char							*ft_substr(char const *s, unsigned int start,
									size_t max);
char							*ft_strjoin_path(char const *s1,
									char const *s2);
int								ft_strrlen(char **strr);
size_t							ft_strr_full_len(char **strr);
char							*ft_strchr_d_quote(const char *str);
int								ft_isdigit(int c);
int								ft_isalpha(int c);
int								ft_is_alphanum(int c);
size_t							ft_strlcpy2(char *dst, const char *src,
									size_t siz);
void							ft_putstr_fd(char *s, int fd);

// env

int								ft_init_woenv(t_data *data);
int								ft_init_envcpy(char **envp, t_data *data);
char							*ft_get_from_env(t_data *data, char *str);
char							*ft_getenv(t_data *data, char *key);
int								ft_xterm_isset(t_data *data);
int								ft_save_stdin(void);

// srcs
int								ft_temp_file(t_data *data, char **buffer_ptr);
char							*ft_make_prompt(t_data *data);
char							*ft_strjoin_prompt(char const *s1,
									char const *s2, char const *s3);
char							*ft_strjoin_prompt_noenv(char const *s1,
									char const *s2, char const *s3);
t_tkn							*ft_strr_to_list(char **strr);
void							ft_init_token(t_tkn *token);
int								ft_add_token(t_tkn **tkn_list, char *str);
void							ft_init_buffer(char *buffer);
int								ft_is_cmd(char *str);
int								ft_wait_for_pipe(t_data *data);
int								ft_islast_pipe(t_tkn *tkn_list);
char							*ft_tknlist_to_str(t_tkn *tkn_list);
char							*ft_get_username(t_data *data);
void							ft_merge_data_input(t_data *data);
char							*ft_extract_from_etcpass(int which);
char							*ft_remove_home(char *full_cwd, t_data *data);
int								ft_isthere_hdoc(t_data *data);
int								ft_make_hdoc_node(t_data *data, char *eof);
int								ft_wait_for_hdoc(t_data *data,
									char *delimiter_orig);
size_t							ft_how_manyhdoc(t_data *data);
int								ft_better_analysis(t_tkn *tkn_list);
int								ft_no_delimiter(char *arg);
int								ft_cutoff_subtoken(t_tkn *tkn_list, char *arg,
									int which);
int								ft_only_delimiter(char *arg);
void							ft_data_init_zero(t_data *data);
void							ft_data_init_one(t_data *data);
void							ft_data_init_two(t_data *data);
void							ft_display_hud(void);
void							ft_single_n_double_qu(t_tkn *tkn, char *arg);
int								ft_build_cmd_list(t_data *data);
int								ft_new_cmd_node(t_data *data);
void							ft_cmd_node_null(t_cmd *new_cmd);
size_t							ft_args_size(t_tkn *cursor_tkn);
char							*ft_filename_hdoc(t_hdoc *cursor_hdoc);
int								ft_another_input(t_tkn *cursor_tkn);
int								ft_another_output(t_tkn *cursor_tkn);
int								ft_convert_first_arg(t_data *data);
int								ft_empty_str(char *str);
int								ft_build_path(t_data *data);
int								ft_replace_w_path(t_cmd *cursor_cmd,
									t_data *data);
int								ft_check_deeper_uid(char **loginuid);
size_t							ft_short_hostname(char *buffer);
int								ft_is_a_pipe(int fd);
int								ft_is_a_file(int fd);
void							ft_init_strr(char ***strr, size_t len);
int								ft_clean_filename(char **str);
int								ft_clean_eof(char **str);

// execution
int								ft_pipe_n_fork(t_data *data, t_cmd *cursor_cmd,
									int prev_pipe[2]);
void							ft_child_redirections(t_cmd *cursor_cmd,
									int prev_pipe[2], t_data *data);
void							ft_parent_process(t_cmd *cursor_cmd,
									int prev_pipe[2], int has_next);
int								ft_execute(t_data *data, t_cmd *cursor_cmd,
									char **env);
int								ft_wait(t_data *data);
int								ft_is_a_child(t_data *data);
int								ft_builtin_child_exec(t_cmd *cursor_cmd,
									t_data *data);
// placeholders
size_t							ft_strlen_placeholder(char *str);
int								ft_replace_placeholders(t_data *data,
									char **arg);
int								ft_check_prev_placeholder(char ***strr,
									t_sizet *szt, t_data *data, int unquoted);
int								ft_replace_placeholders_unquoted(t_data *data,
									char ***strr, size_t j, t_sizet *szt);
//
//
//
// --------------------------------- EXECUTION --------------------------------

int								ft_start_execution(t_data *data);
int								ft_builtin_parent_exec(t_data *data,
									t_cmd *cursor_cmd, int prev_pipe[2],
									int which);
int								ft_pipe_n_fork(t_data *data, t_cmd *cursor_cmd,
									int prev_pipe[2]);
int								ft_setup_pipe(t_cmd *cursor_cmd);
int								ft_handle_parent_builtin(t_data *data,
									t_cmd *cursor_cmd, int prev_pipe[2]);
int								ft_handle_child_process(t_data *data,
									t_cmd *cursor_cmd, int prev_pipe[2]);
void							ft_parent_process(t_cmd *cursor_cmd,
									int prev_pipe[2], int has_next);
int								ft_execute(t_data *data, t_cmd *cursor_cmd,
									char **env);
int								ft_builtin_child_exec(t_cmd *cursor_cmd,
									t_data *data);
int								ft_empty_str(char *str);
int								ft_wait(t_data *data);
int								ft_handle_execute_errors(t_data *data,
									t_cmd *cursor_cmd, int which);
void							ft_child_redirections(t_cmd *cursor_cmd,
									int prev_pipe[2], t_data *data);
void							ft_handle_input_redirection(t_cmd *cursor_cmd,
									int prev_pipe[2]);
void							ft_handle_output_redirection(t_cmd *cursor_cmd);

// --------------------------------- EXECUTION --------------------------------
//
//
//
// --------------------------------- BUILTINS --------------------------------

// CD :
int								ft_cd(t_data *data, t_cmd *cmd);
int								ft_cd_no_arg(t_data *data);
int								ft_cd_update_pwd(t_data *data);
int								ft_cd_with_arg(t_data *data, t_cmd *cmd);
int								ft_validate_cd_target(t_data *data,
									char *target_path);
int								ft_cd_with_arg_checkenv(t_data *data,
									char cwd[PATH_MAX]);
int								ft_cd_update_pwd_with_arg(t_data *data,
									char *arg);
int								ft_cd_handle_getcwd_fail(t_data *data,
									char *arg);
int								ft_cd_error_home_not_set(t_data *data);
int								ft_cd_error_home_empty(t_data *data);
int								ft_cd_error_strjoin(t_data *data);
int								ft_cd_error_getcwd(t_data *data);
int								ft_cd_error_chdir_home(t_data *data,
									char *source);
int								ft_cd_error_too_many_args(t_data *data);
int								ft_cd_error_access_fok(t_data *data, char *arg);
int								ft_cd_error_access_fok(t_data *data, char *arg);
int								ft_cd_error_not_directory(t_data *data,
									char *arg);
int								ft_cd_error_access_xok(t_data *data, char *arg);

// ECHO :
int								ft_echo(t_data *data, t_cmd *cmd);
int								ft_is_newline(char *arg);

// ENV :
int								ft_env(t_data *data, char **env);

// EXPORT :
int								ft_export(t_data *data, t_cmd *cmd);
int								ft_check_env_size_overflow(char **env,
									char **args);
int								ft_process_export_args(t_data *data,
									t_cmd *cmd);
int								ft_export_no_args(t_data data);
void							ft_print_export_env(char *env_var);
int								ft_export_cd(t_data *data, char *env_name,
									char *arg_path);
int								ft_check_valid_arg(char *arg);
int								ft_add_env(t_data *data, char *arg);
int								ft_update_existing_env(t_data *data, char *arg,
									char *var_name);
int								ft_getenv_len(char **env);
void							ft_swap_env_value(char **env, int i, int j);
void							ft_sort_env(char **env);
char							**ft_append_env(t_data *data, char *arg);
int								ft_get_var_name_len(char *arg);

// PWD :
int								ft_pwd(t_data *data);

// UNSET :
int								ft_unset(t_data *data, t_cmd *cmd);
void							ft_unset_env_var(t_data *data, char *arg);
char							**ft_apply_unset(t_data *data, char *arg);
int								ft_should_skip(char *env_var, char *arg);

// --------------------------------- BUILTINS --------------------------------
//
//
//
// --------------------------------- WILDCARDS --------------------------------

char							**ft_fetch_cwd(int which);
int								ft_replace_wildcards(char ***old_strr,
									t_sizet *szt);
char							**ft_fetch_files_based_on_wildcard(
									char *wildcard);
char							**ft_filter_valid_files(char **f_all,
									char *wildcard, size_t *at_least);
void							ft_perform_filtering_loop(char **f_all,
									char **f_valid, char *wildcard,
									size_t *at_least);
int								ft_merge_strr(char ***old_strr, char **new_strr,
									t_sizet *szt);
int								ft_copy_initial_part(char **merged_strr,
									char **old_strr, size_t count);
int								ft_copy_new_part(char **merged_strr,
									char **new_strr, size_t start_index,
									size_t new_len);
char							*ft_wildcard_strr_to_str(char **strr);
int								ft_append_and_space(char **current_res_ptr,
									char *str_to_add, int add_space);
int								ft_matching_wildcard(char *f_name,
									char *wildcard);
int								ft_handle_wildcard_stars(char *wildcard,
									size_t *i_ptr, int *start_ptr);
int								ft_process_segment(char **f_name_ptr,
									int *start_ptr, char *wildcard,
									size_t *i_ptr);
int								ft_match_segment(char **f_name_ptr,
									char *buffer, int is_start_segment,
									int is_end_segment);
int								ft_handle_start_segment(char **f_name_ptr,
									char *buffer, size_t buffer_len);
int								ft_handle_middle_segment(char **f_name_ptr,
									char *buffer, size_t buffer_len,
									char *original_f_name);
int								ft_handle_end_segment(char **f_name_ptr,
									char *buffer, size_t buffer_len);
void							ft_fill_buffer_wpattern(char buffer[PATH_MAX],
									char *wildcard, size_t *i);

// --------------------------------- WILDCARDS --------------------------------
//
//
//
// --------------------------------- SIGNALS --------------------------------

void							ft_signals(void);
void							ft_wait_signals(void);
void							ft_child_signals(void);
void							ft_hdoc_signals(void);
void							ft_pipe_signals(void);
void							ft_handle_sigint(int signal);
void							ft_handle_hdoc_sigint(int signal);
void							ft_handle_pipe_sigint(int signal);

// --------------------------------- SIGNALS --------------------------------
//
//
//
// --------------------------------- TESTER --------------------------------

void							ft_tester_tkn(t_tkn *tkn_list);
void							ft_tester_cmd(t_data *data);
void							ft_tester_strr(char **strr);

// --------------------------------- TESTER --------------------------------
//
//
//
// --------------------------------- ERRORS --------------------------------

void							ft_error(char *error_msg);
void							ft_error_min(char *error_msg);
int								ft_check_tkn_error(t_tkn *tkn_list);
int								ft_check_tkn_error_loop(t_tkn *tkn_list);
int								ft_check_tkn_error_end(t_tkn *tkn_list);
void							ft_error_found(t_tkn *tkn_list, char *source,
									int which);
void							ft_handle_initial_error(t_tkn *tkn_list,
									char *source, int which);
void							ft_handle_errors_suite(char *source, int which);
void							ft_handle_errors_suite_two(char *source,
									int which);
char							*ft_syntax_error_msg(char *arg);
char							*ft_strjoin_three(char const *s1,
									char const *s2, char const *s3);
char							*ft_strjoin_error(char const *s1,
									char const *s2, char const *s3);

// --------------------------------- ERRORS --------------------------------
//
//
//
// --------------------------------- FREE & CLOSE --------------------------

void							ft_free_str(char **str);
void							ft_free_strr(char ***strr);
void							ft_free_tokens(t_tkn *tkn_list);
void							ft_free_hdoc(t_hdoc *hdoc_list);
void							ft_free_cmds(t_cmd *cmd_list);
void							ft_close_fd_in(t_cmd *cmd);
void							ft_close_fd_out(t_cmd *cmd);
void							ft_close_all_fd(t_data *data);
void							ft_close_pipe(int pipe[2]);
void							ft_unlink_hdoc_file(int hdoc_filen);
void							ft_free_loop(t_data *data);
void							ft_free_the_rest(char ***strr, size_t pos,
									size_t total);
void							ft_free_prompt_elem(char *user, char *host,
									char *cwd, int which);

// --------------------------------- FREE & CLOSE --------------------------
//
//
//
// --------------------------------- EXIT --------------------------------

int								ft_check_exit(char *full_input, t_data *data);
int								ft_handle_exit_with_args(char *full_input,
									t_data *data);
int								ft_handle_valid_exit_arg(char **temp_args,
									t_data *data);
void							ft_exit_seq(t_data *data, int exit_code);
void							ft_exit_seq_silent(t_data *data, int exit_code);
int								ft_atoll_safe(char *str, long long *ret);
int								ft_atoll_safe_handle_sign(char *str,
									long long *neg, long long *last_digit,
									size_t *i);
int								ft_atoll_safe_parse_digits(char *str,
									unsigned long long *temp,
									long long last_digit, size_t *i);
int								ft_lookslike_directory(char *str);

// --------------------------------- EXIT --------------------------------

#endif
