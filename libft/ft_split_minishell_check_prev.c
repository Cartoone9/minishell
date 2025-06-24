/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell_check_prev.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:54:03 by *******           #+#    #+#             */
/*   Updated: 2025/04/14 03:29:17 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_previous_is_redirection(char *str)
{
	size_t	str_len;

	if (!str)
		return (0);
	str_len = ft_strlen(str);
	if (str_len >= 2 && ft_strncmp(&str[str_len - 2], "<<", 3) == 0)
		return (1);
	if (str_len >= 1 && ft_strncmp(&str[str_len - 1], "<", 2) == 0)
		return (1);
	if (str_len >= 2 && ft_strncmp(&str[str_len - 2], ">>", 3) == 0)
		return (1);
	if (str_len >= 1 && ft_strncmp(&str[str_len - 1], ">", 2) == 0)
		return (1);
	return (0);
}

int	ft_check_prev_wildcard(char ***strr, t_sizet *szt)
{
	int		wild;
	size_t	j;

	if (!strr || !*strr)
		return (ERROR);
	wild = 0;
	j = szt->j;
	if (j == 1)
	{
		wild = ft_replace_wildcards(strr, szt);
		if (wild == ERROR)
			return (ERROR);
	}
	else if (j >= 2 && (*strr)[j - 2])
	{
		if (!ft_previous_is_redirection((*strr)[j - 2]))
		{
			wild = ft_replace_wildcards(strr, szt);
			if (wild == ERROR)
				return (ERROR);
		}
	}
	return (wild);
}

int	ft_check_prev_placeholder(char ***strr, t_sizet *szt, t_data *data,
		int unquoted)
{
	int		placehd;
	size_t	j;

	if (!strr || !*strr || !szt || !data)
		return (ERROR);
	placehd = 0;
	j = szt->j;
	if (j == 1)
	{
		if (unquoted)
		{
			placehd = ft_replace_placeholders_unquoted(data, strr, j, szt);
		}
		else
		{
			if (ft_replace_placeholders(data, &((*strr)[j - 1])) == ERROR)
				return (ERROR);
		}
	}
	else if (j >= 2)
	{
		placehd = ft_check_prev_placeholder_suite(strr, szt, data, unquoted);
	}
	return (placehd);
}

int	ft_check_prev_placeholder_suite(char ***strr, t_sizet *szt, t_data *data,
		int unquoted)
{
	int		placehd;
	size_t	temp_len;
	int		check_prev;

	placehd = 0;
	check_prev = 0;
	if ((*strr)[szt->j - 2])
	{
		temp_len = ft_strlen((*strr)[szt->j - 2]);
		if (temp_len < 2 || (temp_len >= 2 && ft_strncmp(&((*strr)[szt->j
						- 2][temp_len - 2]), "<<", 3)))
			check_prev = 1;
	}
	if (check_prev)
	{
		if (unquoted)
			placehd = ft_replace_placeholders_unquoted(data, strr, szt->j, szt);
		else
		{
			if (ft_replace_placeholders(data, &((*strr)[szt->j - 1])) == ERROR)
				return (ERROR);
		}
	}
	return (placehd);
}
