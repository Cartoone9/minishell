/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:02:42 by *******           #+#    #+#             */
/*   Updated: 2025/04/11 18:31:25 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd, int clear)
{
	static char	buffer[FD_MAX][BUFFER_SIZE + 1];
	char		*stash;
	char		*ret;

	if (clear)
		return (ft_clear_buffer(buffer[fd]), NULL);
	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE
		+ 1 > SSIZE_MAX)
		return (NULL);
	ret = NULL;
	stash = ft_fill_stash(buffer[fd]);
	stash = gnl_read_and_stash(fd, buffer, &stash);
	if (!stash)
		return (NULL);
	ret = ft_fill_ret(&stash, buffer[fd]);
	if (!ret)
		return (ft_free_str(&stash), NULL);
	if (ret[0] == '\0')
		return (ft_free_str(&ret), NULL);
	return (ret);
}

char	*gnl_read_and_stash(int fd, char buffer[FD_MAX][BUFFER_SIZE + 1],
		char **stash)
{
	ssize_t	char_read;

	char_read = BUFFER_SIZE;
	while (!ft_full_line(*stash) && char_read == BUFFER_SIZE)
	{
		char_read = read(fd, buffer[fd], BUFFER_SIZE);
		if (char_read < 0)
			return (ft_free_str(stash), NULL);
		if (ft_stash_n_clean_buffer(stash, buffer[fd], char_read) == -1)
			return (ft_free_str(stash), NULL);
	}
	return (*stash);
}

char	*ft_fill_stash(char *buffer)
{
	char	*ret;
	size_t	buffer_len;
	size_t	i;

	if (buffer[0] == 0)
		return (NULL);
	i = 0;
	buffer_len = ft_strlen_gnl(buffer);
	ret = malloc(sizeof(char) * (buffer_len + 1));
	if (!ret)
		return (NULL);
	while (i < buffer_len)
	{
		ret[i] = buffer[i];
		buffer[i] = 0;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	ft_stash_n_clean_buffer(char **stash, char *buffer, ssize_t char_read)
{
	t_counter	counter;
	size_t		stash_len;
	char		*temp;

	counter.local = 0;
	counter.global = 0;
	stash_len = 0;
	if (*stash)
		stash_len = ft_strlen_gnl(*stash);
	temp = malloc(sizeof(char) * (stash_len + (size_t)char_read + 1));
	if (!temp)
		return (-1);
	while (counter.local < stash_len)
		temp[counter.global++] = (*stash)[counter.local++];
	counter.local = 0;
	while (counter.local < (size_t)char_read)
		temp[counter.global++] = buffer[counter.local++];
	temp[counter.global] = '\0';
	if (*stash)
		ft_free_str(stash);
	*stash = temp;
	counter.local = -1;
	while (buffer[++counter.local])
		buffer[counter.local] = 0;
	return (0);
}

char	*ft_fill_ret(char **stash, char *buffer)
{
	size_t	to_use;
	size_t	i;
	char	*ret;

	if (!(*stash))
		return (NULL);
	to_use = ft_find_next_return(*stash);
	if (to_use == 0)
		return (NULL);
	ret = malloc(sizeof(char) * (to_use + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < to_use)
		ret[i] = (*stash)[i];
	ret[i] = '\0';
	ft_clean_used_stash(stash, buffer, to_use);
	return (ret);
}
