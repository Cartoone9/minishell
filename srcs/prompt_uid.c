/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_uid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:24:26 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

char	*ft_get_validated_loginuid(void)
{
	char	buffer[PATH_MAX];
	char	*loginuid;
	int		char_read;
	int		fd;

	ft_init_buffer(buffer);
	fd = open("/proc/self/loginuid", O_RDONLY);
	if (fd == -1)
		return (ft_error("cannot access /proc/self/loginuid"), NULL);
	char_read = read(fd, buffer, PATH_MAX - 1);
	close(fd);
	if (char_read == -1)
		return (ft_error("cannot read /proc/self/loginuid"), NULL);
	loginuid = malloc(sizeof(char) * (char_read + 1));
	if (!loginuid)
		return (ft_error("ft_get_username malloc 1 failed"), NULL);
	ft_strlcpy(loginuid, buffer, char_read + 1);
	if (loginuid[0] == '\0' || (ft_strlen(loginuid) == 10
			&& ft_strncmp(loginuid, "4294967295", 10) == 0))
	{
		ft_free_str(&loginuid);
		if (ft_check_deeper_uid(&loginuid) == ERROR)
			return (ft_free_str(&loginuid), NULL);
	}
	return (loginuid);
}

int	ft_check_deeper_uid(char **loginuid)
{
	char	*buffer;
	int		fd;
	int		status;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
		return (ft_error("cannot access /proc/self/status"), ERROR);
	buffer = NULL;
	while (1)
	{
		buffer = get_next_line(fd, 0);
		if (!buffer)
			break ;
		status = ft_process_status_line(&buffer, loginuid, fd);
		if (status == 1)
			return (0);
		if (status == ERROR)
			return (ERROR);
	}
	get_next_line(fd, 1);
	close(fd);
	return (ERROR);
}

int	ft_process_status_line(char **buffer_ptr, char **loginuid, int fd)
{
	char	*extracted_uid;

	if (ft_strncmp(*buffer_ptr, "Uid:", 4) == 0)
	{
		get_next_line(fd, 1);
		close(fd);
		extracted_uid = ft_extract_uid_from_buffer(*buffer_ptr);
		ft_free_str(buffer_ptr);
		if (!extracted_uid)
			return (ft_error("malloc failed in proc_stat_line"), ERROR);
		*loginuid = extracted_uid;
		return (1);
	}
	else
	{
		ft_free_str(buffer_ptr);
		*buffer_ptr = NULL;
		return (0);
	}
}

char	*ft_extract_uid_from_buffer(char *buffer)
{
	char	*temp;
	size_t	loginuid_len;
	size_t	i;
	size_t	j;
	size_t	start_index;

	i = 0;
	loginuid_len = 0;
	while (buffer[i] && (buffer[i] < '0' || buffer[i] > '9'))
		i++;
	start_index = i;
	while (buffer[i] && (buffer[i] >= '0' && buffer[i] <= '9'))
	{
		i++;
		loginuid_len++;
	}
	temp = malloc(sizeof(char) * (loginuid_len + 1));
	if (!temp)
		return (NULL);
	i = start_index;
	j = 0;
	while (j < loginuid_len)
		temp[j++] = buffer[i++];
	temp[j] = '\0';
	return (temp);
}

char	*ft_extract_field_home(char *line)
{
	char	*ret;
	char	*pos;
	size_t	ret_len;
	int		i;

	ret = NULL;
	pos = line;
	i = 0;
	while (i < 5 && pos)
	{
		pos = ft_strchr(pos + 1, ':');
		i++;
	}
	if (pos)
	{
		pos++;
		ret_len = ft_strchr_int(pos, ':');
		ret = malloc(sizeof(char) * (ret_len + 1));
		if (!ret)
			return (ft_error("malloc failed in extract_field_username"), NULL);
		ft_strlcpy(ret, pos, ret_len + 1);
	}
	return (ret);
}
