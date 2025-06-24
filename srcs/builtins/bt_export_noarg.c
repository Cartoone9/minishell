/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export_noarg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:56:36 by *******           #+#    #+#             */
/*   Updated: 2025/04/10 22:21:10 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_export_no_args(t_data data)
{
	char	**env_copy;
	int		i;

	env_copy = malloc(sizeof(char *) * (ft_getenv_len(data.env) + 1));
	if (!env_copy)
		return (ERROR);
	i = 0;
	while (data.env[i])
	{
		env_copy[i] = ft_strdup(data.env[i]);
		if (!env_copy[i])
			return (ft_error("strdup error in ft_export_no_args"),
				ft_free_strr(&env_copy), ERROR);
		i++;
	}
	env_copy[i] = 0;
	ft_sort_env(env_copy);
	i = 0;
	while (env_copy[i])
	{
		ft_print_export_env(env_copy[i]);
		i++;
	}
	ft_free_strr(&env_copy);
	return (0);
}

void	ft_print_export_env(char *env_var)
{
	int	j;

	printf("declare -x ");
	j = 0;
	while (env_var[j] && env_var[j] != '=')
		printf("%c", env_var[j++]);
	if (env_var[j] && env_var[j] == '=')
		printf("=\"%s\"\n", &env_var[j + 1]);
	else
		printf("\n");
}
