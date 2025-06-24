/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_cwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:24:26 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

char	*ft_build_cwd(t_data *data)
{
	char	*cwd_val;
	char	*pwd_env;
	char	*final_val;

	pwd_env = ft_getenv(data, "PWD");
	if (!pwd_env)
		return (NULL);
	if (pwd_env[0] == '\0')
	{
		ft_free_str(&pwd_env);
		cwd_val = ft_getcwd_alloc();
		if (!cwd_val)
			return (NULL);
	}
	else
		cwd_val = pwd_env;
	final_val = ft_remove_home(cwd_val, data);
	if (!final_val)
		return (cwd_val);
	else
	{
		ft_free_str(&cwd_val);
		return (final_val);
	}
}

char	*ft_getcwd_alloc(void)
{
	size_t	buffer_size;
	char	*cwd_buffer;
	char	*result_ptr;

	buffer_size = 32;
	cwd_buffer = malloc(sizeof(char) * buffer_size);
	if (!cwd_buffer)
		return (ft_error("malloc 0 failed in getcwd_alloc_safe"), NULL);
	while (1)
	{
		result_ptr = getcwd(cwd_buffer, buffer_size);
		if (result_ptr != NULL)
			return (cwd_buffer);
		if (errno != ERANGE)
			return (ft_free_str(&cwd_buffer),
				ft_error("getcwd failed with unexpected error"), NULL);
		ft_free_str(&cwd_buffer);
		if (buffer_size > (SIZE_MAX / 2))
			return (ft_error("getcwd buffer size overflow"), NULL);
		buffer_size *= 2;
		cwd_buffer = malloc(sizeof(char) * buffer_size);
		if (!cwd_buffer)
			return (ft_error("malloc 1 failed in getcwd_alloc_safe"), NULL);
	}
	return (NULL);
}

char	*ft_remove_home(char *full_cwd, t_data *data)
{
	char	*partial_cwd;
	char	*home;
	char	*ret;
	size_t	home_len;

	home = ft_getenv(data, "HOME");
	if (!home)
		return (NULL);
	home_len = ft_strlen(home);
	if (!ft_check_home_prefix(full_cwd, &home, home_len))
		return (NULL);
	partial_cwd = ft_strnstr_end(full_cwd, home, ft_strlen(full_cwd));
	if (!partial_cwd)
		return (ft_free_str(&home), NULL);
	ft_free_str(&home);
	ret = ft_build_tilde_path(partial_cwd);
	if (!ret)
		return (NULL);
	return (ret);
}

int	ft_check_home_prefix(char *full_cwd, char **home_ptr, size_t home_len)
{
	char	*home;

	home = *home_ptr;
	if (home[0] == '\0' || home[0] != '/'
		|| ((size_t)ft_strlen(full_cwd) < home_len)
		|| (full_cwd[home_len] != '\0' && full_cwd[home_len] != '/'))
	{
		ft_free_str(home_ptr);
		return (0);
	}
	return (1);
}

char	*ft_build_tilde_path(char *partial_cwd)
{
	size_t	partial_len;
	size_t	extra_char;
	char	*ret;

	partial_len = ft_strlen(partial_cwd);
	extra_char = 3;
	ret = malloc(sizeof(char) * (partial_len + extra_char));
	if (!ret)
	{
		ft_error("malloc failed build_tilde_path");
		return (NULL);
	}
	ret[0] = '~';
	ret[1] = '/';
	ret[2] = '\0';
	ft_strlcat(ret, partial_cwd, partial_len + extra_char);
	return (ret);
}
