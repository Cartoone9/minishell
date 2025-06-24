/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:56:36 by *******           #+#    #+#             */
/*   Updated: 2025/04/10 22:21:23 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_getenv_len(char **env)
{
	int	i;

	if (!env || !env[0])
		return (0);
	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_swap_env_value(char **env, int i, int j)
{
	char	*tmp;

	tmp = env[i];
	env[i] = env[j];
	env[j] = tmp;
}

void	ft_sort_env(char **env)
{
	int	i;
	int	j;
	int	env_len;

	env_len = ft_getenv_len(env);
	i = 0;
	while (i < env_len)
	{
		j = i + 1;
		while (j < env_len)
		{
			if (ft_strncmp(env[i], env[j], 2147483647) > 0)
				ft_swap_env_value(env, i, j);
			j++;
		}
		i++;
	}
}

char	**ft_append_env(t_data *data, char *arg)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (ft_getenv_len(data->env) + 2));
	if (!new_env)
		return (ft_error("malloc failed in ft_append_env"), NULL);
	i = 0;
	while (data->env[i])
	{
		new_env[i] = ft_strdup(data->env[i]);
		if (!new_env[i])
		{
			ft_free_strr(&new_env);
			return (ft_error("strdup failed in ft_append_env"), NULL);
		}
		i++;
	}
	new_env[i] = ft_strdup(arg);
	if (!new_env[i])
	{
		ft_free_strr(&new_env);
		return (ft_error("strdup failed in ft_append_env"), NULL);
	}
	new_env[++i] = NULL;
	return (ft_free_strr(&data->env), new_env);
}

int	ft_get_var_name_len(char *arg)
{
	int	vlen;

	vlen = 0;
	while (arg[vlen] && (ft_is_alphanum(arg[vlen]) || arg[vlen] == '_'))
		vlen++;
	return (vlen);
}
