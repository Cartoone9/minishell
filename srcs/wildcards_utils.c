/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:19:15 by *******           #+#    #+#             */
/*   Updated: 2025/04/13 19:57:06 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

void	ft_free_the_rest(char ***strr, size_t pos, size_t total)
{
	size_t	i;

	i = 0;
	while (i < total)
	{
		if (strr[0][i + pos])
			ft_free_str(&strr[0][i + pos]);
		i++;
	}
	free(*strr);
}

char	*ft_wildcard_strr_to_str(char **strr)
{
	char	*result;
	int		should_add_space;
	size_t	i;

	result = malloc(1);
	if (!result)
		return (ft_error("malloc failed in wd_strr_to_str"), NULL);
	result[0] = '\0';
	i = 0;
	while (strr[i])
	{
		should_add_space = 0;
		if (strr[i + 1])
			should_add_space = 1;
		if (ft_append_and_space(&result, strr[i], should_add_space) == ERROR)
		{
			ft_free_str(&result);
			return (NULL);
		}
		i++;
	}
	return (result);
}

int	ft_append_and_space(char **current_res_ptr, char *str_to_add, int add_space)
{
	char	*temp_holder;
	char	*new_res;

	temp_holder = *current_res_ptr;
	new_res = ft_strjoin(temp_holder, str_to_add);
	ft_free_str(&temp_holder);
	if (!new_res)
		return (ft_error("strjoin 1 failed in helper"), ERROR);
	*current_res_ptr = new_res;
	if (add_space)
	{
		temp_holder = *current_res_ptr;
		new_res = ft_strjoin(temp_holder, " ");
		ft_free_str(&temp_holder);
		if (!new_res)
			return (ft_error("strjoin 2 failed in helper"), ERROR);
		*current_res_ptr = new_res;
	}
	return (0);
}
