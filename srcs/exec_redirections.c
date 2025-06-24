/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:41:14 by *******           #+#    #+#             */
/*   Updated: 2025/04/11 17:01:48 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

void	ft_handle_input_redirection(t_cmd *cursor_cmd, int prev_pipe[2])
{
	if (cursor_cmd->fd_in > 0)
	{
		if (dup2(cursor_cmd->fd_in, STDIN_FILENO) == -1)
			ft_error("dup2 error with infile");
		if (prev_pipe[0] >= 0)
			ft_close_pipe(prev_pipe);
	}
	else if (prev_pipe[0] >= 0)
	{
		if (dup2(prev_pipe[0], STDIN_FILENO) == -1)
			ft_error("dup2 error with prev pipe");
		ft_close_pipe(prev_pipe);
	}
}

void	ft_handle_output_redirection(t_cmd *cursor_cmd)
{
	if (cursor_cmd->fd_out > 0)
	{
		if (dup2(cursor_cmd->fd_out, STDOUT_FILENO) == -1)
			ft_error("dup2 error with outfile");
		if (cursor_cmd->pipe[0] >= 0)
			ft_close_pipe(cursor_cmd->pipe);
	}
	else if (cursor_cmd->next)
	{
		if (dup2(cursor_cmd->pipe[1], STDOUT_FILENO) == -1)
			ft_error("dup2 error with curr pipe");
		ft_close_pipe(cursor_cmd->pipe);
	}
}

void	ft_child_redirections(t_cmd *cursor_cmd, int prev_pipe[2], t_data *data)
{
	ft_handle_input_redirection(cursor_cmd, prev_pipe);
	ft_handle_output_redirection(cursor_cmd);
	ft_close_all_fd(data);
}
