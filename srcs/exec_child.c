/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:41:14 by *******           #+#    #+#             */
/*   Updated: 2025/04/15 22:35:25 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_handle_child_process(t_data *data, t_cmd *cursor_cmd, int prev_pipe[2])
{
	int	ret;

	ret = 0;
	close(g_stdin_save);
	ft_child_signals();
	ft_child_redirections(cursor_cmd, prev_pipe, data);
	if (ft_strncmp(cursor_cmd->path, "builtin", 8) == 0)
		ret = ft_builtin_child_exec(cursor_cmd, data);
	else if (ft_strncmp(cursor_cmd->path, "s_error", 8) == 0)
		ft_exit_seq_silent(data, data->exit_status);
	else
		ret = ft_execute(data, cursor_cmd, data->env);
	return (ret);
}

int	ft_execute(t_data *data, t_cmd *cursor_cmd, char **env)
{
	if (cursor_cmd->args && cursor_cmd->args[0])
	{
		if (ft_strncmp(cursor_cmd->path, ":", 2) == 0
			|| ft_strncmp(cursor_cmd->path, "!", 2) == 0)
			ft_handle_execute_errors(data, cursor_cmd, 0);
		if (access(cursor_cmd->path, F_OK) != 0)
		{
			if (ft_lookslike_directory(cursor_cmd->args[0]))
				ft_handle_execute_errors(data, cursor_cmd, 1);
			else
				ft_handle_execute_errors(data, cursor_cmd, 2);
		}
		if (access(cursor_cmd->path, X_OK) != 0)
			ft_handle_execute_errors(data, cursor_cmd, 3);
		if (ft_is_a_directory(cursor_cmd->path))
			ft_handle_execute_errors(data, cursor_cmd, 4);
		execve(cursor_cmd->path, cursor_cmd->args, env);
		ft_error_found(NULL, cursor_cmd->args[0], 4);
	}
	ft_exit_seq_silent(data, 1);
	return (1);
}

int	ft_handle_execute_errors(t_data *data, t_cmd *cursor_cmd, int which)
{
	int	return_value;

	if (which == 0)
		return_value = 0;
	else if (which == 1)
	{
		ft_error_found(NULL, cursor_cmd->args[0], 15);
		return_value = 127;
	}
	else if (which == 2)
	{
		ft_error_found(NULL, cursor_cmd->args[0], 4);
		return_value = 127;
	}
	else if (which == 3)
	{
		ft_error_found(NULL, cursor_cmd->args[0], 3);
		return_value = 126;
	}
	else if (which == 4)
	{
		ft_error_found(NULL, cursor_cmd->args[0], 14);
		return_value = 126;
	}
	return (ft_exit_seq_silent(data, return_value), return_value);
}

int	ft_builtin_child_exec(t_cmd *cursor_cmd, t_data *data)
{
	char	*arg;

	if (!data || !cursor_cmd || !cursor_cmd->args)
		return (errno);
	arg = cursor_cmd->args[0];
	if (ft_strncmp("echo", arg, 5) == 0)
		ft_echo(data, cursor_cmd);
	else if (ft_strncmp("pwd", arg, 4) == 0)
		ft_pwd(data);
	else if (ft_strncmp("export", arg, 7) == 0)
		ft_export(data, cursor_cmd);
	else if (ft_strncmp("env", arg, 4) == 0)
		ft_env(data, data->env);
	else if (ft_strncmp("cd", arg, 3) == 0)
		ft_cd(data, cursor_cmd);
	ft_exit_seq_silent(data, data->exit_status);
	return (data->exit_status);
}
