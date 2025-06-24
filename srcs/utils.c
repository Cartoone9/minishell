/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:27:03 by *******           #+#    #+#             */
/*   Updated: 2025/04/11 17:18:27 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_is_a_directory(char *pathname)
{
	struct stat	pathname_stats;

	if (stat(pathname, &pathname_stats) != 0)
		return (ft_error("stat failed in is_a_directory"), ERROR);
	if (S_ISDIR(pathname_stats.st_mode))
		return (1);
	return (0);
}

int	ft_is_a_pipe(int fd)
{
	struct stat	buffer;

	if (fstat(fd, &buffer) == -1)
		return (ft_error("fstat failed in is_a_pipe"), ERROR);
	if (S_ISFIFO(buffer.st_mode))
		return (1);
	return (0);
}

int	ft_is_a_file(int fd)
{
	struct stat	buffer;

	if (fstat(fd, &buffer) == -1)
		return (ft_error("fstat failed in is_a_file"), ERROR);
	if (S_ISREG(buffer.st_mode))
		return (1);
	return (0);
}

int	ft_empty_str(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	ft_lookslike_directory(char *str)
{
	if (str[0] == '/' || (str[0] == '.' && str[1] == '/'))
		return (1);
	else
		return (0);
}
