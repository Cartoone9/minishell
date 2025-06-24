/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell_unquote.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:54:03 by *******           #+#    #+#             */
/*   Updated: 2025/04/18 02:13:24 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_split_no_quotes(char **strr, const char *s, t_sizet *szt)
{
	size_t	malloc_size;

	if (s[szt->i] == '<' || s[szt->i] == '>' || s[szt->i] == '|'
		|| s[szt->i] == '$')
	{
		if (s[szt->i] == '<' && s[szt->i + 1] && s[szt->i + 1] == '<')
			malloc_size = 2;
		else if (s[szt->i] == '<')
			malloc_size = 1;
		else if (s[szt->i] == '>' && s[szt->i + 1] && s[szt->i + 1] == '>')
			malloc_size = 2;
		else if (s[szt->i] == '>')
			malloc_size = 1;
		else if (s[szt->i] == '|')
			malloc_size = 1;
		else if (s[szt->i] == '$')
			malloc_size = ft_strlen_placeholder((char *)&s[szt->i + 1]) + 1;
	}
	else
	{
		malloc_size = ft_nextch_noquote(&s[(szt->i)], '"', '\'');
	}
	return (ft_allocate_and_copy_token(strr, s, szt, malloc_size));
}

int	ft_allocate_and_copy_token(char **strr, const char *s, t_sizet *szt,
		size_t malloc_size)
{
	strr[szt->j] = malloc(sizeof(char) * (malloc_size + 1));
	if (!strr[szt->j])
		return (ft_error("malloc failed in alloc_and_cpy_tkn"), ERROR);
	szt->k = 0;
	while (szt->k < malloc_size)
	{
		if (s[szt->i] == '\\' && s[(szt->i) + 1] && (s[(szt->i) + 1] == '"'))
			(szt->i)++;
		else if (s[szt->i] == '\\' && s[(szt->i) + 1]
			&& (s[(szt->i) + 1] == '\''))
			(szt->i)++;
		strr[szt->j][szt->k] = s[szt->i];
		(szt->i)++;
		(szt->k)++;
	}
	strr[szt->j][szt->k] = '\0';
	(szt->j)++;
	return (0);
}

int	ft_check_missing_quotes(char *str)
{
	size_t	i;
	int		s_quote;
	int		d_quote;
	int		increment;
	char	next_char;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (str[i])
	{
		if (str[i + 1] != '\0')
			next_char = str[i + 1];
		else
			next_char = '\0';
		increment = ft_update_quote_state(str[i], next_char, &s_quote,
				&d_quote);
		i += increment;
	}
	if (s_quote)
		ft_error_min("minishell: syntax: missing a single quote");
	if (d_quote)
		ft_error_min("minishell: syntax: missing a double quote");
	return (s_quote || d_quote);
}

int	ft_update_quote_state(char c, char next_c, int *s_quote, int *d_quote)
{
	if (c == '\\' && next_c != '\0')
	{
		return (2);
	}
	if (c == '\'')
	{
		if (*d_quote == 0)
			*s_quote = !*s_quote;
	}
	else if (c == '"')
	{
		if (*s_quote == 0)
			*d_quote = !*d_quote;
	}
	return (1);
}
