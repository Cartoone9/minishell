/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:52:45 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

char	*ft_getenv(t_data *data, char *key)
{
	char	*ret;
	char	*full_key;
	size_t	key_len;

	if (!data || !key || !data->env)
		return (ft_error("missing param in ft_getenv"), NULL);
	key_len = ft_strlen(key);
	if (key_len == 0)
		return (ft_error("key is empty in ft_getenv"), NULL);
	full_key = ft_strjoin(key, "=");
	if (!full_key)
		return (ft_error("strjoin failed in ft_getenv"), NULL);
	ret = ft_search_env_for_key(data, full_key, key_len);
	if (ret != NULL)
	{
		ft_free_str(&full_key);
		return (ret);
	}
	ft_free_str(&full_key);
	ret = malloc(1);
	if (!ret)
		return (ft_error("malloc failed in ft_getenv"), NULL);
	ret[0] = '\0';
	return (ret);
}

char	*ft_search_env_for_key(t_data *data, const char *full_key,
		size_t key_len)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(full_key, data->env[i], key_len + 1) == 0)
		{
			ret = ft_extract_env_value(data->env[i], key_len);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	*ft_extract_env_value(const char *env_str, size_t key_len)
{
	char	*ret;
	size_t	value_start_index;
	size_t	value_len;
	size_t	j;

	value_start_index = key_len + 1;
	value_len = ft_strlen(&env_str[value_start_index]);
	ret = malloc(sizeof(char) * (value_len + 1));
	if (!ret)
	{
		ft_error("malloc failed in extract_env_value helper");
		return (NULL);
	}
	j = 0;
	while (j < value_len)
	{
		ret[j] = env_str[value_start_index + j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
