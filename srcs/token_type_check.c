/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:04:12 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_only_delimiter(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] && (arg[i] == '>' || arg[i] == '<' || arg[i] == '|'))
		i++;
	if (arg[i] && (arg[i] != '>' && arg[i] != '<' && arg[i] != '|'))
		return (0);
	return (1);
}

int	ft_no_delimiter(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] && ((arg[i] != '>' && arg[i] != '<' && arg[i] != '|')
			|| (i > 0 && arg[i - 1] == '\\')))
		i++;
	if (arg[i] && (arg[i] == '>' || arg[i] == '<' || arg[i] == '|'))
	{
		if (i == 0 || (i > 0 && arg[i - 1] != '\\'))
			return (0);
	}
	return (1);
}

int	ft_better_analysis(t_tkn *tkn_list)
{
	char	*arg;
	int		ret;

	ret = 0;
	arg = tkn_list->arg;
	if (*arg == '>')
		ret = ft_cutoff_subtoken(tkn_list, arg, 0);
	else if (*arg == '<')
		ret = ft_cutoff_subtoken(tkn_list, arg, 1);
	else if (*arg == '|')
		ret = ft_cutoff_subtoken(tkn_list, arg, 2);
	else
		ret = ft_cutoff_subtoken(tkn_list, arg, 3);
	if (ret == ERROR)
		return (ERROR);
	return (0);
}
