/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:04:12 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_cutoff_subtoken(t_tkn *tkn_list, char *arg, int which)
{
	char	*new_tkn_arg;
	size_t	cutoff_pos;
	size_t	i;
	size_t	j;

	if (!arg | !tkn_list)
		return (ft_error("missing arg or tkn_list in cutoff_subtoken"), ERROR);
	cutoff_pos = ft_cutoff_pos(arg, which);
	tkn_list->arg = ft_make_old_token_arg(arg, cutoff_pos);
	if (!tkn_list->arg)
		return (ERROR);
	i = 0;
	j = cutoff_pos;
	while (arg[j++])
		i++;
	new_tkn_arg = malloc(sizeof(char) * i + 1);
	if (!new_tkn_arg)
		return (ft_error("new_tkn_arg malloc failed"), ERROR);
	i = 0;
	j = cutoff_pos;
	while (arg[j])
		new_tkn_arg[i++] = arg[j++];
	new_tkn_arg[i] = '\0';
	ft_free_str(&arg);
	return (ft_insert_new_token(&tkn_list, new_tkn_arg));
}
