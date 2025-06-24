/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:40:57 by *******           #+#    #+#             */
/*   Updated: 2025/04/14 20:47:18 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

// Handles file open errors for redirections
void	ft_handle_open_error(t_data *data, t_cmd *cmd, char *filename,
		int fd_to_close)
{
	cmd->error = 1;
	data->exit_status = 1;
	ft_error_found(NULL, filename, 3);
	if (fd_to_close > 0)
	{
		close(fd_to_close);
		if (fd_to_close == cmd->fd_in)
			cmd->fd_in = 0;
		else if (fd_to_close == cmd->fd_out)
			cmd->fd_out = 0;
	}
}

int	ft_open_and_handle_input(t_data *data, t_cmd *cmd, t_tkn *tkn,
		char *filename)
{
	cmd->fd_in = open(filename, O_RDONLY);
	if (cmd->fd_in == -1)
	{
		ft_handle_open_error(data, cmd, filename, cmd->fd_out);
	}
	else
	{
		if (ft_another_input(tkn->next))
		{
			close(cmd->fd_in);
			cmd->fd_in = 0;
		}
	}
	return (0);
}

int	ft_open_output_file(t_data *data, t_cmd *cmd, char *filename,
		int open_flags)
{
	cmd->fd_out = open(filename, open_flags, 0664);
	if (cmd->fd_out == -1 || ft_is_a_directory(filename))
	{
		ft_handle_open_error(data, cmd, filename, cmd->fd_in);
		return (ERROR);
	}
	return (0);
}

int	ft_another_output(t_tkn *cursor_tkn)
{
	while (cursor_tkn)
	{
		if (cursor_tkn->type == PIPE_ID)
			break ;
		else if (cursor_tkn->type == OUT_ID || cursor_tkn->type == A_OUT_ID)
			return (1);
		cursor_tkn = cursor_tkn->next;
	}
	return (0);
}

int	ft_another_input(t_tkn *cursor_tkn)
{
	while (cursor_tkn)
	{
		if (cursor_tkn->type == PIPE_ID)
			break ;
		else if (cursor_tkn->type == IN_ID || cursor_tkn->type == HDOC_IN_ID)
			return (1);
		cursor_tkn = cursor_tkn->next;
	}
	return (0);
}
