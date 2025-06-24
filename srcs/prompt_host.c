/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_host.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:24:26 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

char	*ft_make_hostname(t_data *data)
{
	char	buffer[PATH_MAX];
	char	*hostname;
	int		char_read;
	int		short_char_read;
	int		fd;

	hostname = ft_getenv(data, "HOSTNAME");
	if (!hostname)
		return (NULL);
	if (hostname[0] != '\0')
		return (hostname);
	ft_free_str(&hostname);
	ft_init_buffer(buffer);
	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return (ft_error("cannot access /etc/hostname"), NULL);
	char_read = read(fd, buffer, PATH_MAX);
	close(fd);
	if (char_read == -1)
		return (ft_error("cannot read /etc/hostname"), NULL);
	short_char_read = ft_short_hostname(buffer);
	hostname = malloc(sizeof(char) * short_char_read + 1);
	if (!hostname)
		return (ft_error("ft_make_hostname malloc failed"), NULL);
	return (ft_strlcpy(hostname, buffer, short_char_read + 1), hostname);
}

size_t	ft_short_hostname(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] && (ft_is_alphanum(buffer[i]) || buffer[i] == '_'
			|| buffer[i] == '-'))
		i++;
	return (i);
}
