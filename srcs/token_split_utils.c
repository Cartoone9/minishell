/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:04:12 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_cutoff_pos(char *arg, int which)
{
	int	i;

	i = 0;
	if (which == 0)
	{
		if (arg[i] && arg[i + 1] && arg[i + 1] == '>')
			return (2);
		else
			return (1);
	}
	else if (which == 1)
	{
		if (arg[i] && arg[i + 1] && arg[i + 1] == '<')
			return (2);
		else
			return (1);
	}
	else if (which == 2)
		return (1);
	while (arg[i] && ((arg[i] != '>' && arg[i] != '<' && arg[i] != '|')
			|| (i > 0 && arg[i - 1] == '\\')))
	{
		i++;
	}
	return (i);
}

char	*ft_make_old_token_arg(char *arg, size_t cutoff)
{
	char	*old_tkn_arg;
	size_t	j;

	old_tkn_arg = malloc(sizeof(char) * cutoff + 1);
	if (!old_tkn_arg)
		return (ft_error("old_tkn_arg malloc failed"), NULL);
	j = 0;
	while (j < cutoff && arg[j])
	{
		old_tkn_arg[j] = arg[j];
		j++;
	}
	old_tkn_arg[j] = '\0';
	return (old_tkn_arg);
}

int	ft_insert_new_token(t_tkn **tkn_list, char *new_arg)
{
	t_tkn	*save_tkn;

	save_tkn = *tkn_list;
	if (ft_add_token(tkn_list, new_arg) == ERROR)
		return (ft_free_str(&new_arg), ERROR);
	*tkn_list = save_tkn;
	return (0);
}
