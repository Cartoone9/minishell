/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell_strcnt.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:04:32 by *******           #+#    #+#             */
/*   Updated: 2025/04/14 02:25:14 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

size_t	ft_strcnt_spe(const char *str, char c, char c_2)
{
	size_t	str_len;
	size_t	sum;
	size_t	i;

	str_len = ft_strlen(str);
	sum = 0;
	i = 0;
	while (i < str_len)
	{
		while (i < str_len && (str[i] == c || str[i] == c_2))
			i++;
		if (i < str_len)
			sum++;
		else
			break ;
		if (ft_is_separator_nospace(str[i]))
			ft_strcnt_dispatch(str, &i, str_len);
		else
		{
			while (i < str_len && !ft_is_separator(str[i], c, c_2))
				i++;
		}
	}
	return (sum);
}

void	ft_strcnt_dispatch(const char *str, size_t *i_ptr, size_t str_len)
{
	if (str[*i_ptr] == '\'' || str[*i_ptr] == '"')
		ft_strcnt_handle_quotes(str, i_ptr, str_len);
	else if (str[*i_ptr] == '|' || str[*i_ptr] == '<' || str[*i_ptr] == '>')
		ft_strcnt_handle_operator(str, i_ptr, str_len);
	else if (str[*i_ptr] == '$')
		ft_strcnt_handle_dollar(str, i_ptr, str_len);
	else if (str[*i_ptr] == '*')
		ft_strcnt_handle_star(str, i_ptr, str_len);
}
