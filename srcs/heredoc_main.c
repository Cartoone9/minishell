/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:52:45 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

// Main function to handle reading input for a heredoc until a delimiter.
// Manages the process, temporary file creation, and signal handling.
int	ft_wait_for_hdoc(t_data *data, char *delimiter_orig)
{
	char	*buffer;
	char	*delimiter;
	int		status;

	buffer = NULL;
	delimiter = NULL;
	data->input = NULL;
	if (ft_init_hdoc_read(data, delimiter_orig, &buffer, &delimiter) == ERROR)
		return (ERROR);
	status = ft_hdoc_readline_loop(data, delimiter_orig, &buffer, delimiter);
	if (status == ERROR)
		return (ERROR);
	if (status == 1)
		return (1);
	return (ft_finalize_hdoc(data, &buffer, &delimiter));
}

// Initializes variables needed for reading heredoc input.
int	ft_init_hdoc_read(t_data *data, char *del_orig,
		char **buf, char **del)
{
	if (!del_orig)
		return (ft_error("missing hdoc delim in wait_for_hdoc"), ERROR);
	*buf = malloc(1);
	if (!*buf)
		return (ft_error("malloc failed in wait_for_hdoc"), ERROR);
	(*buf)[0] = '\0';
	if (ft_xterm_isset(data))
		data->prompt = "\001\033[1;38;2;108;86;249m\002heredoc>"
			"\001\033[0m\002 ";
	else
		data->prompt = "heredoc> ";
	*del = ft_strjoin(del_orig, "\n");
	if (!*del)
	{
		ft_free_str(buf);
		return (ft_error("strjoin 0 failed in ft_temp_file"), ERROR);
	}
	ft_hdoc_signals();
	return (0);
}

// The main loop for reading heredoc input line by line.
int	ft_hdoc_readline_loop(t_data *data, char *del_orig,
		char **buf, char *del)
{
	int	status;

	while (1)
	{
		status = ft_process_hdoc_line(data, del, del_orig);
		if (status == 2)
			return (ft_free_str(buf), ft_free_str(&del), 1);
		if (status == ERROR)
			return (ft_free_str(buf), ft_free_str(&del), ERROR);
		if (status == 1)
			break ;
		if (ft_append_to_hdoc_buffer(buf, &data->input) == ERROR)
		{
			ft_free_str(buf);
			ft_free_str(&del);
			ft_free_str(&data->input);
			return (ERROR);
		}
	}
	return (0);
}

// Reads one line of heredoc input and processes it.
int	ft_process_hdoc_line(t_data *data, char *del, char *del_orig)
{
	char	*temp;

	temp = readline(data->prompt);
	if (g_signal == 1)
	{
		data->exit_status = 130;
		ft_free_str(&temp);
		if (dup2(g_stdin_save, STDIN_FILENO) == -1)
			return (ft_error("dup2 failed in wait_for_hdoc"), ERROR);
		return (2);
	}
	if (!temp)
	{
		ft_error_found(NULL, del_orig, 11);
		return (1);
	}
	data->input = ft_strjoin(temp, "\n");
	ft_free_str(&temp);
	if (!data->input)
		return (ft_error("strjoin 1 failed in ft_temp_file"), ERROR);
	if (ft_strncmp(data->input, del, ft_strlen(del)) == 0)
		return (ft_free_str(&data->input), 1);
	return (0);
}

// Finalizes heredoc processing: resets signals, saves buffer to file.
int	ft_finalize_hdoc(t_data *data, char **buffer_ptr, char **delimiter)
{
	int	final_status;

	ft_signals();
	ft_free_str(delimiter);
	final_status = 0;
	if (*buffer_ptr)
	{
		if (ft_replace_placeholders(data, buffer_ptr) == ERROR)
		{
			ft_free_str(buffer_ptr);
			final_status = ERROR;
		}
		else
		{
			if (ft_temp_file(data, buffer_ptr) == ERROR)
				final_status = ERROR;
		}
	}
	return (final_status);
}
