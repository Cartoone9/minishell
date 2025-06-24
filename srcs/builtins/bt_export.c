/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:56:36 by *******           #+#    #+#             */
/*   Updated: 2025/04/10 23:53:05 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_export(t_data *data, t_cmd *cmd)
{
	if (!cmd->args[1])
	{
		if (ft_export_no_args(*data) == ERROR)
		{
			data->exit_status = 1;
			return (ERROR);
		}
		data->exit_status = 0;
		return (0);
	}
	else
	{
		if (ft_check_env_size_overflow(data->env, &cmd->args[1]))
			return (ft_error_min("minishell: \
				export would overflow environment size limit"), 1);
		return (ft_process_export_args(data, cmd));
	}
}

int	ft_check_env_size_overflow(char **env, char **args)
{
	if (ft_strr_full_len(env) + ft_strr_full_len(args) > ARG_MAX_SIZE)
		return (1);
	return (0);
}

int	ft_process_export_args(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (!ft_check_valid_arg(cmd->args[i]))
		{
			data->exit_status = 1;
			return (ft_error_found(NULL, cmd->args[i], 7), ERROR);
		}
		else if (ft_add_env(data, cmd->args[i]) == ERROR)
		{
			data->exit_status = 1;
			return (ft_error("malloc error in ft_export"), ERROR);
		}
		if (ft_strncmp(cmd->args[i], "PATH=", 5) == 0)
			ft_build_path(data);
		i++;
	}
	data->exit_status = 0;
	return (0);
}
