/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_match.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:19:15 by *******           #+#    #+#             */
/*   Updated: 2025/04/13 19:55:58 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_matching_wildcard(char *f_name, char *wildcard)
{
	size_t	i;
	int		result;
	int		start;

	if (!f_name || !wildcard || ft_strlen(wildcard) >= PATH_MAX)
		return (ft_error("invalid parameter in matching_wildcard"), ERROR);
	start = 1;
	i = 0;
	while (wildcard[i])
	{
		if (wildcard[i] == '*')
		{
			if (ft_handle_wildcard_stars(wildcard, &i, &start))
				return (1);
		}
		result = ft_process_segment(&f_name, &start, wildcard, &i);
		if (result == 0)
			return (0);
		if (result == 2)
			return (1);
	}
	return (1);
}

int	ft_handle_wildcard_stars(char *wildcard, size_t *i_ptr, int *start_ptr)
{
	if (*start_ptr)
		*start_ptr = 0;
	while (wildcard[*i_ptr] && wildcard[*i_ptr] == '*')
	{
		(*i_ptr)++;
	}
	if (!wildcard[*i_ptr])
	{
		return (1);
	}
	return (0);
}

int	ft_process_segment(char **f_name_ptr, int *start_ptr, char *wildcard,
		size_t *i_ptr)
{
	char	buffer[PATH_MAX];
	int		current_start;
	int		end;

	current_start = *start_ptr;
	ft_fill_buffer_wpattern(buffer, wildcard, i_ptr);
	end = 0;
	if (!wildcard[*i_ptr])
		end = 1;
	if (!ft_match_segment(f_name_ptr, buffer, current_start, end))
		return (0);
	if (current_start)
		*start_ptr = 0;
	if (end)
		return (2);
	else
		return (1);
}

int	ft_match_segment(char **f_name_ptr, char *buffer, int is_start_segment,
		int is_end_segment)
{
	size_t	buffer_len;
	char	*original_f_name;

	original_f_name = *f_name_ptr;
	buffer_len = ft_strlen(buffer);
	if (is_start_segment)
	{
		return (ft_handle_start_segment(f_name_ptr, buffer, buffer_len));
	}
	else if (!is_end_segment)
	{
		return (ft_handle_middle_segment(f_name_ptr, buffer, buffer_len,
				original_f_name));
	}
	else
	{
		return (ft_handle_end_segment(f_name_ptr, buffer, buffer_len));
	}
}

void	ft_fill_buffer_wpattern(char buffer[PATH_MAX], char *wildcard,
		size_t *i)
{
	size_t	n;

	ft_init_buffer(buffer);
	n = 0;
	while (wildcard[*i] && wildcard[*i] != '*')
	{
		buffer[n] = wildcard[*i];
		(*i)++;
		n++;
	}
	buffer[n] = '\0';
}
