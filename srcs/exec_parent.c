/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_parent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:41:14 by *******           #+#    #+#             */
/*   Updated: 2025/04/11 17:09:20 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_handle_parent_builtin(t_data *data, t_cmd *cursor_cmd, int prev_pipe[2])
{
	if (cursor_cmd->path == NULL)
		return (ft_builtin_parent_exec(data, cursor_cmd, prev_pipe, 0));
	if (ft_strncmp(cursor_cmd->path, "builtin_p_cd", 13) == 0)
		return (ft_builtin_parent_exec(data, cursor_cmd, prev_pipe, 1));
	else if (ft_strncmp(cursor_cmd->path, "builtin_p_export", 17) == 0)
		return (ft_builtin_parent_exec(data, cursor_cmd, prev_pipe, 2));
	else if (ft_strncmp(cursor_cmd->path, "builtin_p_unset", 16) == 0)
		return (ft_builtin_parent_exec(data, cursor_cmd, prev_pipe, 3));
	return (256);
}

int	ft_builtin_parent_exec(t_data *data, t_cmd *cursor_cmd,
		int prev_pipe[2], int which)
{
	cursor_cmd->pid = -1;
	if (which == 1)
		ft_cd(data, cursor_cmd);
	else if (which == 2)
		ft_export(data, cursor_cmd);
	else if (which == 3)
		ft_unset(data, cursor_cmd);
	ft_close_fd_in(cursor_cmd);
	ft_close_fd_out(cursor_cmd);
	ft_parent_process(cursor_cmd, prev_pipe, cursor_cmd->next != NULL);
	return (data->exit_status);
}

void	ft_parent_process(t_cmd *cursor_cmd, int prev_pipe[2], int has_next)
{
	if (prev_pipe[0] >= 0)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (has_next)
	{
		prev_pipe[0] = cursor_cmd->pipe[0];
		prev_pipe[1] = cursor_cmd->pipe[1];
	}
	ft_close_fd_in(cursor_cmd);
	ft_close_fd_out(cursor_cmd);
}
