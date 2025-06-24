/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:02:20 by *******           #+#    #+#             */
/*   Updated: 2025/04/18 13:55:05 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_check_exit(char *full_input, t_data *data)
{
	if (!data || !full_input)
		return (ERROR);
	while (*full_input && (*full_input == ' ' || *full_input == '\t'))
		full_input++;
	if (ft_strncmp(full_input, "exit", 5) == 0)
		return (ft_exit_seq(data, data->exit_status), data->exit_status);
	else if (!ft_strchr(full_input, '|'))
	{
		if (ft_strncmp(full_input, "exit", 4) == 0 && (full_input[4] == ' '
				|| full_input[4] == '\t'))
		{
			ft_handle_exit_with_args(full_input, data);
			data->exit_status = 1;
			return (ERROR);
		}
	}
	return (ERROR);
}

int	ft_handle_exit_with_args(char *full_input, t_data *data)
{
	char	**t_args;

	t_args = ft_split_minishell(full_input, data);
	if (!t_args || !t_args[0] || !t_args[1])
		return (ft_free_strr(&t_args), ft_exit_seq(data, data->exit_status), 0);
	else if (t_args[0] && t_args[1] && ft_str_is_a_redirection(t_args[1]))
		return (ft_free_strr(&t_args), ft_exit_seq(data, data->exit_status), 0);
	else if (t_args[0] && t_args[1] && !ft_has_only_digit(t_args[1]))
	{
		data->exit_status = 2;
		return (ft_error_found(NULL, t_args[1], 12),
			ft_free_strr(&t_args), ft_exit_seq(data, data->exit_status),
			ERROR);
	}
	else if (t_args[0] && t_args[1] && t_args[2])
	{
		data->exit_status = 1;
		return (ft_free_strr(&t_args),
			ft_error_min("minishell: exit: too many arguments"), ERROR);
	}
	else if (t_args[0] && ft_strncmp(t_args[0], "exit", 5) == 0
		&& t_args[1] && !t_args[2])
		return (ft_handle_valid_exit_arg(t_args, data));
	return (ft_free_strr(&t_args), ERROR);
}

int	ft_str_is_a_redirection(char *str)
{
	if (ft_strncmp(str, "<", 2) == 0 || ft_strncmp(str,
			"<<", 3) == 0 || ft_strncmp(str, ">", 2) == 0
		|| ft_strncmp(str, ">>", 3) == 0 || ft_strncmp(str,
			"|", 3) == 0)
	{
		return (1);
	}
	return (0);
}

int	ft_handle_valid_exit_arg(char **temp_args, t_data *data)
{
	long long	ret;

	if (ft_atoll_safe(temp_args[1], &ret) == ERROR)
	{
		data->exit_status = 1;
		return (ft_free_strr(&temp_args), ft_exit_seq(data, 2), 2);
	}
	else
		return (ft_free_strr(&temp_args), ft_exit_seq(data, (unsigned char)ret),
			(int)ret);
}
