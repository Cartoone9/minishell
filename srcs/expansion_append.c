/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:52:45 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

// Appends the prefix before a '$' to new_arg
int	ft_append_prefix(char **new_arg, char *prefix_start, int len)
{
	char	*prefix_part;

	prefix_part = ft_substr(prefix_start, 0, len);
	if (!prefix_part)
		return (ft_error("substr prefix failed"), ERROR);
	if (ft_join_and_update(new_arg, prefix_part) != 0)
		return (ft_error("join prefix failed"), ERROR);
	return (0);
}

// Appends just '$'
int	ft_append_dollar_sign(char **new_arg)
{
	char	*dollar;

	dollar = ft_strdup("$");
	if (!dollar)
		return (ft_error("strdup $ failed"), ERROR);
	if (ft_join_and_update(new_arg, dollar) != 0)
		return (ft_error("join $ failed"), ERROR);
	return (0);
}

// Appends string representation of exit status
int	ft_append_exit_status(t_data *data, char **new_arg)
{
	char	*status_str;

	status_str = ft_itoa(data->exit_status);
	if (!status_str)
		return (ft_error("itoa exit status failed"), ERROR);
	if (ft_join_and_update(new_arg, status_str) != 0)
		return (ft_error("join exit status failed"), ERROR);
	return (0);
}

// Appends the value of an environment variable
int	ft_append_env_case(t_data *data, char **new_arg, char *start,
		size_t len)
{
	char	*name;
	char	*env_ret;

	name = ft_substr(start, 0, len);
	if (!name)
		return (ft_error("substr failed in append_env_case"), ERROR);
	env_ret = ft_getenv(data, name);
	ft_free_str(&name);
	if (!env_ret)
		return (ft_error("getenv failed in append_env_case"), ERROR);
	if (ft_join_and_update(new_arg, env_ret) != 0)
		return (ft_error("join env case failed"), ERROR);
	return (0);
}

// Appends the literal placeholder ($VAR)
int	ft_append_literal_placeholder(char **new_arg,
		char *placeholder_start, size_t placeholder_len)
{
	char	*literal_part;

	literal_part = ft_substr(placeholder_start, 0, placeholder_len + 1);
	if (!literal_part)
		return (ft_error("substr literal placeholder failed"), ERROR);
	if (ft_join_and_update(new_arg, literal_part) != 0)
		return (ft_error("join literal placeholder failed"), ERROR);
	return (0);
}
