/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell_quote.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:54:03 by *******           #+#    #+#             */
/*   Updated: 2025/04/18 02:13:23 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_single_quotes(char **strr, const char *s, size_t *i, size_t *j)
{
	size_t	k;

	(*i)++;
	strr[*j] = malloc(sizeof(char) * (ft_nextch_s_quote(&s[*i], '\'') + 1));
	if (!strr[*j])
		return (-1);
	k = 0;
	while (s[*i] && s[*i] != '\'')
	{
		if (s[*i] == '>' || s[*i] == '<' || s[*i] == '|' || s[*i] == '*')
			strr[*j][k++] = '\\';
		strr[*j][k] = s[*i];
		k++;
		(*i)++;
	}
	strr[*j][k] = '\0';
	(*i)++;
	(*j)++;
	return (0);
}

int	ft_double_quotes(char **strr, const char *s, size_t *i, size_t *j)
{
	size_t	k;

	(*i)++;
	strr[*j] = malloc(sizeof(char) * (ft_nextch_d_quote(&s[*i], '"') + 1));
	if (!strr[*j])
		return (-1);
	k = 0;
	while (s[*i] && (s[*i] != '"' || (*i > 0 && s[(*i) - 1] == '\\')))
	{
		if (s[*i] == '\\' && s[(*i) + 1] && s[(*i) + 1] == '"')
			(*i)++;
		else
		{
			if (s[*i] == '>' || s[*i] == '<' || s[*i] == '|' || s[*i] == '*')
				strr[*j][k++] = '\\';
			strr[*j][k] = s[*i];
			k++;
			(*i)++;
		}
	}
	strr[*j][k] = '\0';
	(*i)++;
	(*j)++;
	return (0);
}
