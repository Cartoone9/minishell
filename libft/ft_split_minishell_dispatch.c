/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell_dispatch.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:54:03 by *******           #+#    #+#             */
/*   Updated: 2025/04/18 02:05:31 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_handle_single_quote_case(char ***strr, const char *s, t_sizet *szt)
{
	if (ft_single_quotes(*strr, s, &szt->i, &szt->j) == ERROR)
	{
		ft_free_strr(strr);
		return (ERROR);
	}
	return (0);
}

int	ft_handle_double_quote_case(char ***strr, const char *s, t_sizet *szt,
		t_data *data)
{
	if (ft_double_quotes(*strr, s, &szt->i, &szt->j) == ERROR
		|| ft_check_prev_placeholder(strr, szt, data, 0) == ERROR)
	{
		ft_free_strr(strr);
		return (ERROR);
	}
	return (0);
}

int	ft_handle_non_quote_case(char ***strr, const char *s, t_sizet *szt,
		t_data *data)
{
	if (ft_process_non_quote_segment(strr, s, szt, data) == ERROR)
	{
		ft_free_strr(strr);
		return (ERROR);
	}
	return (0);
}

int	ft_process_non_quote_segment(char ***strr, const char *s, t_sizet *szt,
		t_data *data)
{
	if (ft_split_no_quotes(*strr, s, szt) == ERROR)
		return (ERROR);
	szt->placehd = ft_check_prev_placeholder(strr, szt, data, 1);
	if (szt->placehd == ERROR || szt->strr_len == 0)
		return (ERROR);
	if (szt->space == 1 || (szt->j > 0
			&& szt->i == (size_t)ft_strlen((*strr)[szt->j - 1])))
	{
		if (s[szt->i] != '$')
		{
			szt->wild = ft_check_prev_wildcard(strr, szt);
			if (szt->wild == ERROR)
				return (ERROR);
		}
	}
	return (0);
}

int	ft_replace_strr_by_empty(char ***strr, int which)
{
	if (which == 0)
		ft_error_min("minishell: syntax: missing a single quote");
	else
		ft_error_min("minishell: syntax: missing a double quote");
	ft_free_strr(strr);
	(*strr) = malloc(sizeof(char *) * 2);
	if (!(*strr))
		return (ft_error("malloc 0 failed missing "
				"replace_strr_by_empty"), ERROR);
	(*strr)[0] = malloc(sizeof(char) * 1);
	if (!(*strr)[0])
		return (ft_error("malloc 1 failed missing "
				"replace_strr_by_empty"), ERROR);
	(*strr)[0][0] = '\0';
	(*strr)[1] = NULL;
	return (0);
}
