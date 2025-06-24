/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:04:12 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

t_tkn	*ft_build_tkn_list(char *input, t_data *data)
{
	char	**strr_input;
	t_tkn	*tkn_list;

	strr_input = ft_split_minishell(input, data);
	if (!strr_input)
		return (NULL);
	tkn_list = ft_strr_to_list(strr_input);
	free(strr_input);
	if (!tkn_list)
		return (NULL);
	ft_what_type(tkn_list);
	return (tkn_list);
}

t_tkn	*ft_strr_to_list(char **strr)
{
	t_tkn	*cursor;
	t_tkn	*ret;
	size_t	i;

	if (!strr || !strr[0])
		return (NULL);
	ret = malloc(sizeof(t_tkn));
	if (!ret)
		return (NULL);
	ft_init_token(ret);
	ret->arg = strr[0];
	cursor = ret;
	i = 1;
	while (strr[i])
	{
		if (ft_add_token(&cursor, strr[i]) == ERROR)
			return (ft_free_tokens(ret), NULL);
		i++;
	}
	return (ret);
}

int	ft_add_token(t_tkn **tkn_list, char *str)
{
	t_tkn	*save_tkn;
	t_tkn	*temp;

	temp = malloc(sizeof(t_tkn));
	if (!temp)
		return (ft_error("ft_add_token malloc failed"), ERROR);
	ft_init_token(temp);
	temp->arg = str;
	save_tkn = NULL;
	if ((*tkn_list)->next)
		save_tkn = (*tkn_list)->next;
	(*tkn_list)->next = temp;
	*tkn_list = (*tkn_list)->next;
	if (save_tkn)
		(*tkn_list)->next = save_tkn;
	return (0);
}

void	ft_init_token(t_tkn *token)
{
	token->type = 0;
	token->arg = NULL;
	token->next = NULL;
}
