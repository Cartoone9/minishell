/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:02:31 by *******           #+#    #+#             */
/*   Updated: 2025/04/10 22:21:33 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_unset(t_data *data, t_cmd *cmd)
{
	int	n;

	if (!data || !cmd)
	{
		data->exit_status = 1;
		return (ft_error("missing data/cmd in ft_unset"), ERROR);
	}
	if (!cmd->args || !cmd->args[0] || !cmd->args[1])
	{
		data->exit_status = 0;
		return (1);
	}
	n = 1;
	while (cmd->args[n])
	{
		ft_unset_env_var(data, cmd->args[n]);
		n++;
	}
	data->exit_status = 0;
	return (0);
}

void	ft_unset_env_var(t_data *data, char *arg)
{
	int		i;
	int		arg_len;
	char	*temp_env;

	arg_len = ft_strlen(arg);
	i = 0;
	while (data->env[i])
	{
		temp_env = data->env[i];
		if (ft_strncmp(temp_env, arg, arg_len) == 0 && (temp_env[arg_len] == '='
				|| temp_env[arg_len] == '\0'))
		{
			if (ft_strncmp(arg, "PATH", 5) == 0)
			{
				ft_free_strr(&data->path);
				data->path = NULL;
			}
			data->env = ft_apply_unset(data, arg);
			break ;
		}
		i++;
	}
}

char	**ft_apply_unset(t_data *data, char *arg)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = malloc(sizeof(char *) * ft_getenv_len(data->env));
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (ft_should_skip(data->env[i], arg))
		{
			i++;
			continue ;
		}
		new_env[j] = ft_strdup(data->env[i]);
		if (!new_env[j])
			return (ft_error("strdup error in apply_unset"),
				ft_free_strr(&new_env), data->env);
		i++;
		j++;
	}
	new_env[j] = 0;
	return (ft_free_strr(&data->env), new_env);
}

int	ft_should_skip(char *env_var, char *arg)
{
	int	arg_len;

	arg_len = ft_strlen(arg);
	if ((ft_strncmp(env_var, arg, arg_len) == 0 && env_var[arg_len] == '=')
		|| (ft_strncmp(env_var, arg, arg_len) == 0 && env_var[arg_len] == 0))
	{
		return (1);
	}
	return (0);
}
