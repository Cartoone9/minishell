/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_match_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:19:15 by *******           #+#    #+#             */
/*   Updated: 2025/04/13 19:56:14 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_handle_start_segment(char **f_name_ptr, char *buffer, size_t buffer_len)
{
	if (ft_strncmp(buffer, *f_name_ptr, buffer_len) != 0)
		return (0);
	*f_name_ptr += buffer_len;
	return (1);
}

int	ft_handle_middle_segment(char **f_name_ptr, char *buffer, size_t buffer_len,
		char *original_f_name)
{
	*f_name_ptr = ft_strnstr(original_f_name, buffer,
			ft_strlen(original_f_name));
	if (!*f_name_ptr)
		return (0);
	*f_name_ptr += buffer_len;
	return (1);
}

int	ft_handle_end_segment(char **f_name_ptr, char *buffer, size_t buffer_len)
{
	size_t	f_name_len;

	f_name_len = ft_strlen(*f_name_ptr);
	if (buffer_len > f_name_len)
		return (0);
	if (ft_strncmp(*f_name_ptr + f_name_len - buffer_len, buffer,
			buffer_len) != 0)
		return (0);
	return (1);
}
