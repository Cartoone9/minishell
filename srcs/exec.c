/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:41:14 by *******           #+#    #+#             */
/*   Updated: 2025/04/18 14:05:49 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_start_execution(t_data *data)
{
	int		prev_pipe[2];
	t_cmd	*cursor_cmd;
	int		ret;

	if (!data || !data->cmd_list)
		return (ft_error("missing data and/or cmd_list in start_execution"),
			ERROR);
	ret = 0;
	prev_pipe[0] = -1;
	prev_pipe[1] = -1;
	cursor_cmd = data->cmd_list;
	while (cursor_cmd)
	{
		ret = ft_pipe_n_fork(data, cursor_cmd, prev_pipe);
		if (ret == ERROR)
			return (ERROR);
		cursor_cmd = cursor_cmd->next;
	}
	return (ret);
}

int	ft_pipe_n_fork(t_data *data, t_cmd *cursor_cmd, int prev_pipe[2])
{
	int	ret;
	int	parent_builtin_ret;

	ret = 0;
	if (ft_setup_pipe(cursor_cmd) == ERROR)
		return (ft_exit_seq(data, errno), ERROR);
	parent_builtin_ret = ft_handle_parent_builtin(data, cursor_cmd, prev_pipe);
	if (parent_builtin_ret != 256)
		return (parent_builtin_ret);
	cursor_cmd->pid = fork();
	g_signal = cursor_cmd->pid;
	if (cursor_cmd->pid < 0)
	{
		ft_error("fork failed in pipe_n_fork");
		return (ft_exit_seq(data, errno), ERROR);
	}
	if (cursor_cmd->pid == 0)
		ret = ft_handle_child_process(data, cursor_cmd, prev_pipe);
	else
		ft_parent_process(cursor_cmd, prev_pipe, cursor_cmd->next != NULL);
	return (ret);
}

int	ft_setup_pipe(t_cmd *cursor_cmd)
{
	if (cursor_cmd->next != NULL)
	{
		if (pipe(cursor_cmd->pipe) == -1)
		{
			ft_error("pipe failed in pipe_n_fork");
			return (ERROR);
		}
	}
	return (0);
}

int	ft_wait(t_data *data)
{
	t_cmd	*cursor_cmd;
	int		status;
	int		ret;

	ret = 0;
	ft_wait_signals();
	cursor_cmd = data->cmd_list;
	while (cursor_cmd)
	{
		if (cursor_cmd->pid != 0)
		{
			if (waitpid(cursor_cmd->pid, &status, 0) == -1)
				return (data->exit_status);
			if (WIFEXITED(status))
				ret = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					write(2, "Quit (core dumped)\n", 19);
				ret = 128 + WTERMSIG(status);
			}
		}
		cursor_cmd = cursor_cmd->next;
	}
	return (ft_signals(), ret);
}
