/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:54:04 by *******           #+#    #+#             */
/*   Updated: 2025/03/02 19:56:03 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

char	*ft_strnstr(const char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	loc;

	if (src[0] == '\0')
		return ((char *)dest);
	i = 0;
	while (i < n && dest[i])
	{
		j = 0;
		while (i < n && dest[i] && dest[i] != src[j])
			i++;
		if (i < n && dest[i] && dest[i] == src[j])
		{
			loc = i;
			while (i < n && dest[i] && dest[i++] == src[j])
				j++;
			if (src[j] == '\0')
				return ((char *)&dest[loc]);
			i = loc + 1;
		}
	}
	return (NULL);
}

char	*ft_strnstr_end(const char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	loc;

	if (src[0] == '\0')
		return ((char *)dest);
	i = 0;
	while (i < n && dest[i])
	{
		j = 0;
		while (i < n && dest[i] && dest[i] != src[j])
			i++;
		if (i < n && dest[i] && dest[i] == src[j])
		{
			loc = i;
			while (i < n && dest[i] && dest[i++] == src[j])
				j++;
			if (src[j] == '\0')
				return ((char *)&dest[i]);
			i = loc + 1;
		}
	}
	return (NULL);
}
