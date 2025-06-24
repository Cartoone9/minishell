/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:54:03 by *******           #+#    #+#             */
/*   Updated: 2025/04/09 23:53:03 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	c_uc;
	size_t			i;

	c_uc = (unsigned char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == c_uc)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	if (c_uc == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

int	ft_strchr_int(const char *str, int c)
{
	unsigned char	c_uc;
	int				i;

	c_uc = (unsigned char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == c_uc)
		{
			return (i);
		}
		i++;
	}
	if (c_uc == '\0')
		return (i);
	return (-1);
}

char	*ft_strchr_second(const char *str, int c)
{
	unsigned char	c_uc;
	size_t			once;
	size_t			i;

	c_uc = (unsigned char)c;
	once = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c_uc)
		{
			if (once == 0)
				once = 1;
			else
				return ((char *)&str[i]);
		}
		i++;
	}
	if (c_uc == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strchr_d_quote(const char *str)
{
	unsigned char	c;
	size_t			i;

	c = '"';
	i = 0;
	while (str[i])
	{
		if (str[i] == c && (i == 0 || str[i - 1] != '\\'))
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
