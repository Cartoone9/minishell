/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:48:38 by *******           #+#    #+#             */
/*   Updated: 2025/04/11 18:29:24 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_find_next_return(char *str)
{
	size_t	sum;

	sum = 0;
	while (str[sum] && str[sum] != '\n')
		sum++;
	if (str[sum] == '\n')
		return (sum + 1);
	return (sum);
}

size_t	ft_strlen_gnl(char *str)
{
	size_t	sum;

	sum = 0;
	while (str[sum])
		sum++;
	return (sum);
}

void	ft_clean_used_stash(char **stash, char *buffer, size_t used)
{
	t_counter	counter;

	counter.local = 0;
	counter.global = used;
	while ((*stash)[counter.global])
	{
		buffer[counter.local] = (*stash)[counter.global];
		counter.global++;
		counter.local++;
	}
	buffer[counter.local] = '\0';
	ft_free_str(stash);
}

void	ft_clear_buffer(char buffer[BUFFER_SIZE + 1])
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		buffer[i] = '\0';
		i++;
	}
}

size_t	ft_full_line(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}
