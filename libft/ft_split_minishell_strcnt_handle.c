/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell_strcnt_handle.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:04:32 by *******           #+#    #+#             */
/*   Updated: 2025/04/14 04:06:08 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

void	ft_strcnt_handle_quotes(const char *str, size_t *i_ptr, size_t str_len)
{
	char	quote_char;
	size_t	i;

	i = *i_ptr;
	quote_char = str[i];
	i++;
	while (i < str_len && str[i] != quote_char)
	{
		i++;
	}
	if (i < str_len)
	{
		i++;
	}
	*i_ptr = i;
}

void	ft_strcnt_handle_operator(const char *str, size_t *i_ptr,
		size_t str_len)
{
	size_t	i;

	i = *i_ptr;
	if (str[i] == '|')
	{
		i++;
	}
	else if (str[i] == '<' || str[i] == '>')
	{
		if (i + 1 < str_len && str[i + 1] == str[i])
		{
			i += 2;
		}
		else
		{
			i++;
		}
	}
	*i_ptr = i;
}

void	ft_strcnt_handle_dollar(const char *str, size_t *i_ptr, size_t str_len)
{
	size_t	i;

	i = *i_ptr;
	i++;
	if (i < str_len && (str[i] == '*' || str[i] == '?'))
	{
		i++;
	}
	else if (i < str_len && (ft_is_alphanum(str[i]) || str[i] == '_'))
	{
		while (i < str_len && (ft_is_alphanum(str[i]) || str[i] == '_'))
		{
			i++;
		}
	}
	*i_ptr = i;
}

void	ft_strcnt_handle_star(const char *str, size_t *i_ptr, size_t str_len)
{
	size_t	i;

	i = *i_ptr;
	while (i < str_len && str[i] == '*')
	{
		i++;
	}
	*i_ptr = i;
}
