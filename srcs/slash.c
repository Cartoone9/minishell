/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:52:45 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_remove_slash(t_data *data)
{
	t_cmd	*cursor_cmd;
	int		status;

	if (!data || !data->cmd_list)
		return (ft_error("missing data in remove_slash"), ERROR);
	cursor_cmd = data->cmd_list;
	while (cursor_cmd)
	{
		status = ft_process_command_args(cursor_cmd);
		if (status != 0)
			return (status);
		cursor_cmd = cursor_cmd->next;
	}
	return (0);
}

int	ft_process_command_args(t_cmd *cmd)
{
	char	**cursor_args;
	size_t	i;

	if (!cmd || !cmd->args)
		return (0);
	cursor_args = cmd->args;
	i = 0;
	while (cursor_args[i])
	{
		if (ft_process_single_arg(&cursor_args[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (0);
}

int	ft_process_single_arg(char **arg_ptr)
{
	char	*temp_arg;
	size_t	l_slash;
	size_t	j;
	size_t	k;

	l_slash = ft_count_slash(*arg_ptr);
	if (l_slash > 0)
	{
		temp_arg = malloc(sizeof(char) * (ft_strlen(*arg_ptr) - l_slash + 1));
		if (!temp_arg)
			return (ft_error("malloc failed in proc_single_arg"), ERROR);
		j = 0;
		k = 0;
		while ((*arg_ptr)[j])
		{
			if (ft_slash_matching(arg_ptr, j))
				j++;
			else
				temp_arg[k++] = (*arg_ptr)[j++];
		}
		temp_arg[k] = '\0';
		ft_free_str(arg_ptr);
		*arg_ptr = temp_arg;
	}
	return (0);
}

int	ft_slash_matching(char **arg_ptr, size_t j)
{
	if ((*arg_ptr)[j] == '\\' && ((*arg_ptr)[j + 1] == '<'
		|| (*arg_ptr)[j + 1] == '>' || (*arg_ptr)[j + 1] == '|'
		|| (*arg_ptr)[j + 1] == '*'))
		return (1);
	return (0);
}

size_t	ft_count_slash(char *str)
{
	size_t	i;
	size_t	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '\\' && (str[i + 1] == '<' || str[i + 1] == '>'
				|| str[i + 1] == '|' || str[i + 1] == '*'))
			ret++;
		i++;
	}
	return (ret);
}
