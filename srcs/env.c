/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:50:30 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_init_woenv(t_data *data)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_error("getcwd failed in init_woenv"), ERROR);
	else
	{
		data->env = malloc(sizeof(char *) * 2);
		if (!data->env)
			return (ft_error("malloc failed in init_woenv"), ERROR);
		data->env[0] = ft_strjoin("PWD=", cwd);
		if (!data->env[0])
			return (ft_error("strjoin failed in init_woenv"),
				ft_free_strr(&data->env), ERROR);
		data->env[1] = NULL;
	}
	return (0);
}

int	ft_init_envcpy(char **envp, t_data *data)
{
	int		i;

	if (!(*envp))
	{
		data->envless = 1;
		return (ft_init_woenv(data));
	}
	i = 0;
	while (envp[i])
		i++;
	data->env = malloc(sizeof(char *) * (i + 1));
	if (!data->env)
		return (ft_error("malloc failed in init_envcpy"), ERROR);
	i = 0;
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
			return (ft_error("strdup 2 failed in init_envcpy"),
				ft_free_strr(&data->env), ERROR);
		i++;
	}
	data->env[i] = NULL;
	return (0);
}

int	ft_xterm_isset(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "TERM=xterm-256color", 20) == 0)
			return (1);
		else if (ft_strncmp(data->env[i], "TERM=xterm-kitty", 17) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_build_path(t_data *data)
{
	size_t	i;

	i = 0;
	if (!data || !data->env)
		return (ERROR);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0
			&& ft_strlen(data->env[i]) >= 6)
		{
			if (data->path)
				ft_free_strr(&data->path);
			data->path = ft_split(data->env[i] + 5, ':');
			if (!data->path)
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}
