/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:56:36 by *******           #+#    #+#             */
/*   Updated: 2025/04/18 02:07:18 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_export_cd(t_data *data, char *env_name, char *arg_path)
{
	char	*full_env;

	full_env = ft_strjoin(env_name, arg_path);
	if (!full_env)
		return (ft_error("strjoin failed in export_cd"), ERROR);
	if (!ft_check_valid_arg(full_env))
	{
		ft_free_str(&full_env);
		return (ft_error_min("minishell: export: invalid identifier"), 1);
	}
	else if (ft_add_env(data, full_env) == ERROR)
	{
		ft_free_str(&full_env);
		return (ERROR);
	}
	ft_free_str(&full_env);
	return (0);
}

int	ft_check_valid_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg[i] || (arg[i] != '_' && !ft_isalpha(arg[i])))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] != '_' && !ft_is_alphanum(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_add_env(t_data *data, char *arg)
{
	int		ret;
	int		vlen;
	char	*var_name;

	if (!data || !arg)
		return (ft_error("data and/or arg missing in add_env"), ERROR);
	vlen = ft_get_var_name_len(arg);
	var_name = ft_substr(arg, 0, vlen);
	if (!var_name)
		return (ft_error("substr failed in add_env"), ERROR);
	ret = ft_update_existing_env(data, arg, var_name);
	if (ret == ERROR)
		return (ft_free_str(&var_name), ERROR);
	else if (ret)
		return (ft_free_str(&var_name), 0);
	ft_free_str(&var_name);
	data->env = ft_append_env(data, arg);
	if (!data->env)
		return (ERROR);
	return (0);
}

int	ft_update_existing_env(t_data *data, char *arg, char *var_name)
{
	size_t	var_len;
	int		i;

	i = 0;
	while (data->env[i])
	{
		var_len = ft_strlen(var_name);
		if (ft_strncmp(data->env[i], var_name, var_len) == 0
			&& (data->env[i][var_len] == '=' || data->env[i][var_len] == 0))
		{
			if (ft_strncmp(data->env[i], var_name, var_len) == 0
				&& data->env[i][var_len] == '=' && data->env[i][var_len + 1]
				&& !ft_strchr(arg, '='))
				return (1);
			ft_free_str(&data->env[i]);
			data->env[i] = ft_strdup(arg);
			if (!data->env[i])
				return (ft_error("strdup error in ft_add_env"), ERROR);
			return (1);
		}
		i++;
	}
	return (0);
}
