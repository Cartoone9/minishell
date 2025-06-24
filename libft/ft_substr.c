/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:54:04 by *******           #+#    #+#             */
/*   Updated: 2025/03/12 18:26:08 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t max)
{
	unsigned int	s_len;
	char			*ret;
	size_t			i;

	s_len = (unsigned int)(ft_strlen(s));
	if (s_len <= start)
		ret = malloc(sizeof(char) * 1);
	else if (s_len - start >= max)
		ret = malloc(sizeof(char) * max + 1);
	else
		ret = malloc(sizeof(char) * (s_len - start) + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	if (s_len > start)
	{
		while (i < max && s[start])
		{
			ret[i] = s[start];
			start++;
			i++;
		}
	}
	ret[i] = '\0';
	return (ret);
}
