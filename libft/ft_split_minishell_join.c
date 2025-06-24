/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell_join.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:54:03 by *******           #+#    #+#             */
/*   Updated: 2025/04/15 19:06:27 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_join_adjacent_words(char ***strr, t_sizet *szt, int placehd)
{
	char	*temp;

	if (placehd > 0 && (size_t)placehd < szt->j)
	{
		return (ft_join_with_placeholder(strr, szt, placehd));
	}
	temp = ft_strjoin((*strr)[szt->j - 2], (*strr)[szt->j - 1]);
	if (!temp)
		return (ft_error("strjoin 1 failed in join_adj_words"), ERROR);
	ft_free_str(&(*strr)[szt->j - 1]);
	ft_free_str(&(*strr)[szt->j - 2]);
	(*strr)[szt->j - 2] = temp;
	szt->j--;
	return (0);
}

int	ft_join_with_placeholder(char ***strr, t_sizet *szt, int placehd)
{
	char	*temp;
	size_t	i;

	temp = ft_strjoin((*strr)[szt->j - placehd - 1], (*strr)[szt->j - placehd]);
	if (!temp)
		return (ft_error("strjoin 0 failed in join_with_placehd"), ERROR);
	ft_free_str(&(*strr)[szt->j - placehd - 1]);
	ft_free_str(&(*strr)[szt->j - placehd]);
	(*strr)[szt->j - placehd - 1] = temp;
	i = 0;
	while (szt->j - placehd + i < szt->strr_len)
	{
		(*strr)[szt->j - placehd + i] = (*strr)[szt->j - placehd + i + 1];
		i++;
	}
	szt->j--;
	return (0);
}
