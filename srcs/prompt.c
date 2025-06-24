/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:24:26 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

char	*ft_make_prompt(t_data *data)
{
	char	*cwd;
	char	*host;
	char	*user;
	char	*ret;
	size_t	which;

	which = 0;
	user = ft_set_user(data, &which);
	host = ft_set_host(data, &which);
	cwd = ft_set_cwd(data, &which);
	if (!ft_xterm_isset(data) || data->envless)
	{
		ret = ft_strjoin_prompt_noenv(user, host, cwd);
	}
	else
		ret = ft_strjoin_prompt(user, host, cwd);
	if (which < 7)
		ft_free_prompt_elem(user, host, cwd, which);
	if (!ret)
		return (NULL);
	return (ret);
}

char	*ft_set_user(t_data *data, size_t *which)
{
	char	*user;

	user = ft_get_username(data);
	if (!user)
	{
		*which = 1;
		user = "user";
	}
	return (user);
}

char	*ft_set_host(t_data *data, size_t *which)
{
	char	*host;

	host = ft_make_hostname(data);
	if (!host)
	{
		if (*which == 1)
			*which = 4;
		else
			*which = 2;
		host = "host";
	}
	return (host);
}

char	*ft_set_cwd(t_data *data, size_t *which)
{
	char	*cwd;

	cwd = ft_build_cwd(data);
	if (!cwd)
	{
		if (*which == 0)
			*which = 3;
		else if (*which == 1)
			*which = 5;
		else if (*which == 2)
			*which = 6;
		else if (*which == 4)
			*which = 7;
		cwd = "cwd";
	}
	return (cwd);
}

void	ft_free_prompt_elem(char *user, char *host, char *cwd, int which)
{
	if (user && (which != 1 && which != 4 && which != 5))
		ft_free_str(&user);
	if (host && (which != 2 && which != 4 && which != 6))
		ft_free_str(&host);
	if (cwd && (which != 3 && which != 5 && which != 6))
		ft_free_str(&cwd);
}
