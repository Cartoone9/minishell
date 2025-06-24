/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_shin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:29:35 by *******           #+#    #+#             */
/*   Updated: 2025/04/10 21:44:05 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

// FOR CD HOME ENV VARIABLE => REMOVED i < siz -1 in while (i < siz && src[i])
size_t	ft_strlcpy2(char *dst, const char *src, size_t siz)
{
	size_t	i;

	i = 0;
	if (siz <= 0)
		return (ft_strlen(src));
	while (i < siz && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	ft_is_alphanum(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (fd == -1)
		return ;
	if (s)
		write(fd, s, ft_strlen(s));
}
