/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:24:26 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

char	*ft_get_username(t_data *data)
{
	char	*temp;
	char	*ret;

	temp = ft_getenv(data, "USER");
	if (!temp)
		return (NULL);
	if (temp[0] == '\0')
	{
		ft_free_str(&temp);
		ret = ft_extract_from_etcpass(0);
		if (!ret)
			return (NULL);
	}
	else
		ret = temp;
	return (ret);
}

char	*ft_extract_from_etcpass(int which)
{
	char	*loginuid;
	char	*ret;
	int		fd;

	loginuid = ft_get_validated_loginuid();
	if (!loginuid)
		return (NULL);
	fd = open("/etc/passwd", O_RDONLY);
	if (fd == -1)
		return (ft_error("cannot access /etc/passwd"), NULL);
	ret = ft_find_and_extract(fd, loginuid, which);
	ft_free_str(&loginuid);
	get_next_line(fd, 1);
	close(fd);
	return (ret);
}

char	*ft_find_and_extract(int fd, char *loginuid, int which)
{
	char	*temp;
	char	*ret;
	char	*uid_pos_in_line;
	size_t	loginuid_len;

	ret = NULL;
	loginuid_len = ft_strlen(loginuid);
	temp = get_next_line(fd, 0);
	while (temp)
	{
		uid_pos_in_line = ft_strchr_second(temp, ':');
		if (uid_pos_in_line)
		{
			uid_pos_in_line++;
			if (ft_strncmp(uid_pos_in_line, loginuid, loginuid_len) == 0
				&& uid_pos_in_line[loginuid_len] == ':')
			{
				return (ft_matching_uid(temp, which));
			}
		}
		ft_free_str(&temp);
		temp = get_next_line(fd, 0);
	}
	return (ret);
}

char	*ft_matching_uid(char *temp, int which)
{
	char	*ret;

	ret = ft_extract_field(temp, which);
	ft_free_str(&temp);
	return (ret);
}

// 0 extract username from /etc/passwd, 1 extract home
char	*ft_extract_field(char *line, int which)
{
	char	*ret;
	size_t	ret_len;

	ret = NULL;
	if (which == 0)
	{
		ret_len = ft_strchr_int(line, ':');
		ret = malloc(sizeof(char) * (ret_len + 1));
		if (!ret)
			return (ft_error("malloc failed in extract_field"), NULL);
		ft_strlcpy(ret, line, ret_len + 1);
	}
	else if (which == 1)
	{
		ret = ft_extract_field_home(line);
	}
	return (ret);
}
