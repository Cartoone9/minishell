/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:40:57 by *******           #+#    #+#             */
/*   Updated: 2025/04/14 20:43:25 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_convert_first_arg(t_data *data)
{
	t_cmd	*cursor_cmd;
	size_t	pipeline;

	if (!data || !data->env)
		return (ft_error("missing data / data->env in convert_first_arg"),
			ERROR);
	cursor_cmd = data->cmd_list;
	pipeline = 0;
	while (cursor_cmd)
	{
		if (ft_process_command_node(cursor_cmd, data, pipeline) == ERROR)
			return (ERROR);
		pipeline = 1;
		cursor_cmd = cursor_cmd->next;
	}
	return (0);
}

int	ft_process_command_node(t_cmd *cmd, t_data *data, size_t pipeline)
{
	if (cmd->error)
	{
		cmd->path = ft_strdup("s_error");
		if (!cmd->path)
			return (ft_error("strdup error node fail"), ERROR);
	}
	else if (cmd->args && !cmd->args[0])
	{
		cmd->args[0] = ft_strdup("");
		if (!cmd->args[0])
			return (ft_error("strdup empty arg fail"), ERROR);
	}
	else if (cmd->args && cmd->args[0] && !cmd->error)
	{
		if (ft_handle_valid_command_arg(cmd, data, pipeline) == ERROR)
			return (ERROR);
	}
	return (0);
}

int	ft_handle_valid_command_arg(t_cmd *cmd, t_data *data,
		size_t pipeline)
{
	int	builtin;

	builtin = ft_is_builtin_path(cmd->args[0]);
	if (builtin >= 1)
	{
		if (ft_set_builtin_path(cmd, builtin, pipeline) == ERROR)
			return (ERROR);
		return (0);
	}
	else if (data->path)
	{
		return (ft_handle_non_builtin_with_path(cmd, data));
	}
	else
	{
		return (ft_handle_non_builtin_no_path(cmd));
	}
}

int	ft_set_builtin_path(t_cmd *cmd, int builtin, size_t pipeline)
{
	if (builtin >= 1 && builtin <= 3 && pipeline == 0 && !cmd->next)
	{
		if (builtin == 1)
			cmd->path = ft_strdup("builtin_p_cd");
		else if (builtin == 2)
			cmd->path = ft_strdup("builtin_p_export");
		else if (builtin == 3)
			cmd->path = ft_strdup("builtin_p_unset");
		if (!cmd->path)
			return (ft_error("strdup builtin parent fail"), ERROR);
	}
	else if (builtin >= 1)
	{
		cmd->path = ft_strdup("builtin");
		if (!cmd->path)
			return (ft_error("strdup builtin fail"), ERROR);
	}
	return (0);
}

int	ft_is_builtin_path(char *arg)
{
	if (!arg)
		return (ERROR);
	if (ft_strncmp("cd", arg, 3) == 0)
		return (1);
	if (ft_strncmp("export", arg, 7) == 0)
		return (2);
	if (ft_strncmp("unset", arg, 6) == 0)
		return (3);
	if (ft_strncmp("env", arg, 4) == 0)
		return (4);
	if (ft_strncmp("echo", arg, 5) == 0)
		return (5);
	if (ft_strncmp("pwd", arg, 4) == 0)
		return (6);
	if (ft_strncmp("exit", arg, 5) == 0)
		return (7);
	return (0);
}
