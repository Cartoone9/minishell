/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:17:43 by *******           #+#    #+#             */
/*   Updated: 2025/04/11 18:19:15 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

size_t	ft_strlcat(char *dest, const char *src, size_t buf)
{
	size_t	i;
	size_t	src_len;
	size_t	dest_len;
	size_t	available;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (buf <= dest_len)
		return (src_len + buf);
	i = 0;
	available = buf - dest_len - 1;
	while (i < available && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (src_len + dest_len);
}
