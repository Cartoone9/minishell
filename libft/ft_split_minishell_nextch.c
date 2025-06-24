/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell_nextch.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:04:32 by *******           #+#    #+#             */
/*   Updated: 2025/04/14 04:06:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

size_t	ft_nextch_s_quote(const char *str, char c)
{
	size_t	sum;
	size_t	spe;

	sum = 0;
	spe = 0;
	while (str[sum] && str[sum] != c)
	{
		if (str[sum] == '>' || str[sum] == '<' || str[sum] == '|'
			|| str[sum] == '*')
			spe++;
		sum++;
	}
	return (sum + spe);
}

size_t	ft_nextch_d_quote(const char *str, char c)
{
	size_t	sum;
	size_t	spe;

	sum = 0;
	spe = 0;
	while (str[sum] && (str[sum] != c || (sum > 0 && str[sum - 1] == '\\')))
	{
		if (str[sum] == '>' || str[sum] == '<' || str[sum] == '|'
			|| str[sum] == '*')
			spe++;
		sum++;
	}
	return (sum + spe);
}

size_t	ft_nextch_spe(const char *str)
{
	size_t	backslash;
	size_t	sum;
	char	c;
	char	c_2;

	c = ' ';
	c_2 = '\t';
	sum = 0;
	backslash = 0;
	while (str[sum] && ((str[sum] != c && str[sum] != c_2) || (sum > 0
				&& str[sum - 1] == '\\')))
	{
		if (str[sum] == '\\' && str[sum + 1] && (str[sum + 1] == '"'
				|| str[sum + 1] == '\''))
		{
			backslash++;
		}
		sum++;
	}
	return (sum - backslash);
}

size_t	ft_nextch_noquote(const char *str, char d, char e)
{
	size_t	backslash;
	size_t	sum;
	char	c;
	char	c_2;

	c = ' ';
	c_2 = '\t';
	sum = 0;
	backslash = 0;
	while (str[sum] && str[sum] != c && str[sum] != c_2 && str[sum] != '<'
		&& str[sum] != '>' && str[sum] != '|' && str[sum] != '$'
		&& str[sum] != d && str[sum] != e)
	{
		sum++;
	}
	return (sum - backslash);
}
