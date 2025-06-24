/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:52:45 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

// Joins src to *dst. Frees previous *dst and src. Updates *dst.
int	ft_join_and_update(char **dst, char *src)
{
	char	*temp_join;

	if (!src)
		return (ERROR);
	if (!*dst)
		*dst = src;
	else
	{
		temp_join = ft_strjoin(*dst, src);
		ft_free_str(dst);
		ft_free_str(&src);
		if (!temp_join)
			return (ERROR);
		*dst = temp_join;
	}
	return (0);
}

size_t	ft_strlen_placeholder(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '?' || str[0] == '*')
		return (1);
	while (str[i] && (ft_is_alphanum(str[i]) || str[i] == '_'))
	{
		i++;
	}
	return (i);
}
