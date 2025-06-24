/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:40:57 by *******           #+#    #+#             */
/*   Updated: 2025/04/14 20:49:54 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_replace_w_path(t_cmd *cursor_cmd, t_data *data)
{
	int	dot;
	int	dot_2;
	int	status;

	ft_init_dots(&dot, &dot_2, cursor_cmd);
	if (dot != 0 && dot_2 != 0)
	{
		status = ft_search_path(cursor_cmd, data->path, cursor_cmd->args[0]);
		if (status == 1)
			return (0);
		if (status == ERROR)
			return (ERROR);
	}
	if (ft_strncmp(cursor_cmd->args[0], "exit", 5) != 0)
	{
		cursor_cmd->path = ft_strdup("error");
		if (!cursor_cmd->path)
			return (ft_error("strdup failed in no_path_cmd"), ERROR);
	}
	return (0);
}

void	ft_init_dots(int *dot, int *dot_2, t_cmd *cmd)
{
	*dot = ft_strncmp(cmd->args[0], ".", 2);
	*dot_2 = ft_strncmp(cmd->args[0], "..", 3);
}

int	ft_search_path(t_cmd *cursor_cmd, char **paths, char *cmd_name)
{
	char	*temp;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin_path(paths[i], cmd_name);
		if (!temp)
		{
			ft_error("strjoin_path failed in ft_search_path");
			return (ERROR);
		}
		if (access(temp, F_OK) == 0)
		{
			cursor_cmd->path = temp;
			return (1);
		}
		ft_free_str(&temp);
		i++;
	}
	return (0);
}

int	ft_handle_non_builtin_no_path(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "exit", 5) != 0)
	{
		cmd->path = ft_strdup(cmd->args[0]);
		if (!cmd->path)
			return (ft_error("strdup no-path fail"), ERROR);
	}
	return (0);
}

int	ft_handle_non_builtin_with_path(t_cmd *cmd, t_data *data)
{
	if (cmd->args[0][0] == '\0' || ft_strchr(cmd->args[0], '/'))
	{
		cmd->path = ft_strdup(cmd->args[0]);
		if (!cmd->path)
			return (ft_error("strdup direct path fail"), ERROR);
	}
	else
	{
		if (ft_replace_w_path(cmd, data) == ERROR)
			return (ERROR);
	}
	return (0);
}
