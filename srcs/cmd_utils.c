/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:40:57 by *******           #+#    #+#             */
/*   Updated: 2025/04/14 20:51:37 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_clean_filename(char **str)
{
	char	*buffer;
	size_t	buffer_len;
	size_t	j;
	size_t	ret;

	if (!str || !*str)
		return (ERROR);
	buffer_len = ft_strlen((*str));
	buffer = malloc(sizeof(char) * (buffer_len + 1));
	if (!buffer)
	{
		return (ft_error("malloc fail in clean_filename"), ERROR);
	}
	ret = 0;
	j = ft_process_escapes(*str, buffer, &ret);
	buffer[j] = '\0';
	(*str) = buffer;
	return (ret);
}

int	ft_clean_eof(char **str)
{
	size_t	i;
	size_t	j;

	if (!str || !*str)
		return (ERROR);
	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\' && (*str)[i + 1] && ((*str)[i + 1] == '<'
				|| (*str)[i + 1] == '>' || (*str)[i + 1] == '|' || (*str)[i
				+ 1] == '*'))
		{
			j = i;
			while ((*str)[j])
			{
				(*str)[j] = (*str)[j + 1];
				j++;
			}
		}
		i++;
	}
	return (0);
}

size_t	ft_process_escapes(const char *orig, char *buf, size_t *ret)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (orig[i])
	{
		if (orig[i] == '\\' && orig[i + 1] && (orig[i + 1] == '<'
				|| orig[i + 1] == '>' || orig[i + 1] == '|'
				|| orig[i + 1] == '*'))
		{
			i++;
			*ret = 1;
		}
		else
			buf[j++] = orig[i++];
	}
	return (j);
}

char	*ft_filename_hdoc(t_hdoc *cursor_hdoc)
{
	char	*itoa_filen;
	char	*filename;

	itoa_filen = ft_itoa(cursor_hdoc->hdoc_filen);
	if (cursor_hdoc->next)
		cursor_hdoc = cursor_hdoc->next;
	if (!itoa_filen)
		return (ft_error("itoa failed in filename_hdoc"), NULL);
	filename = ft_strjoin(HDOC_FILE, itoa_filen);
	ft_free_str(&itoa_filen);
	if (!filename)
		return (ft_error("strjoin failed in filename_hdoc"),
			ft_free_str(&itoa_filen), NULL);
	return (filename);
}
