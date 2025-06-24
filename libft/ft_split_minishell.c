/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:54:03 by *******           #+#    #+#             */
/*   Updated: 2025/04/17 20:14:10 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

char	**ft_split_minishell(char const *s, t_data *data)
{
	char	**strr;
	t_sizet	szt;

	ft_init_szt(s, &szt);
	strr = malloc(sizeof(char *) * (szt.strr_len + 1));
	if (strr == NULL)
		return (NULL);
	ft_init_strr(&strr, szt.strr_len + 1);
	if (ft_split_suite(&strr, s, &szt, data) == ERROR)
		return (NULL);
	return (strr);
}

int	ft_init_szt(const char *s, t_sizet *szt)
{
	szt->i = 0;
	szt->j = 0;
	szt->k = 0;
	szt->space = 0;
	szt->wild = 0;
	szt->placehd = 0;
	szt->strr_len = ft_strcnt_spe(s, ' ', '\t');
	return (0);
}

int	ft_split_suite(char ***strr, const char *s, t_sizet *szt, t_data *data)
{
	int	ret;

	while (s[szt->i])
	{
		while (s[szt->i] == ' ' || s[szt->i] == '\t')
		{
			szt->space = 1;
			szt->i++;
		}
		if (!s[szt->i])
			break ;
		ret = ft_process_word_loop(strr, s, szt, data);
		if (ret == ERROR)
			return (ERROR);
		else if (ret == 1)
		{
			data->exit_status = 1;
			return (0);
		}
	}
	(*strr)[szt->j] = NULL;
	return (0);
}

int	ft_process_word_loop(char ***strr, const char *s, t_sizet *szt,
		t_data *data)
{
	size_t	j_save;
	int		status;

	while (s[szt->i] && s[szt->i] != ' ' && s[szt->i] != '\t')
	{
		j_save = szt->j;
		if (s[szt->i] == '\'')
			status = ft_handle_single_quote_case(strr, s, szt);
		else if (s[szt->i] == '"')
			status = ft_handle_double_quote_case(strr, s, szt, data);
		else
			status = ft_handle_non_quote_case(strr, s, szt, data);
		if (status == ERROR)
			return (ERROR);
		if (status == 1)
			return (1);
		if (szt->space == 1 && szt->j > j_save)
			szt->space = 0;
		else if (szt->j > 1 && szt->wild == 0 && szt->j > j_save && j_save > 0)
		{
			if (ft_join_adjacent_words(strr, szt, szt->placehd) == ERROR)
				return (ERROR);
		}
	}
	return (0);
}
