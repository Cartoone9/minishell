/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:04:12 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

void	ft_what_type(t_tkn *tkn_list)
{
	t_tkn	*previous;
	size_t	cmd;
	int		loop;

	cmd = 0;
	loop = 1;
	previous = NULL;
	while (tkn_list)
	{
		if (ft_is_a_redirection(tkn_list))
			ft_assign_redirection_type(tkn_list, &cmd);
		else if (ft_no_delimiter(tkn_list->arg))
			ft_assign_main_type(tkn_list, previous, &cmd);
		else
			ft_handle_other_type(tkn_list, &loop);
		if (loop)
		{
			previous = tkn_list;
			tkn_list = tkn_list->next;
		}
		else
			loop = 1;
	}
}

int	ft_is_a_redirection(t_tkn *tkn_list)
{
	if (ft_strncmp(tkn_list->arg, "<", 2) == 0 || ft_strncmp(tkn_list->arg,
			"<<", 3) == 0 || ft_strncmp(tkn_list->arg, ">", 2) == 0
		|| ft_strncmp(tkn_list->arg, ">>", 3) == 0 || ft_strncmp(tkn_list->arg,
			"|", 3) == 0)
	{
		return (1);
	}
	return (0);
}

void	ft_assign_redirection_type(t_tkn *tkn_list, size_t *cmd)
{
	if (ft_strncmp(tkn_list->arg, "<", 2) == 0)
		tkn_list->type = IN_ID;
	else if (ft_strncmp(tkn_list->arg, "<<", 3) == 0)
		tkn_list->type = HDOC_IN_ID;
	else if (ft_strncmp(tkn_list->arg, ">", 2) == 0)
		tkn_list->type = OUT_ID;
	else if (ft_strncmp(tkn_list->arg, ">>", 3) == 0)
		tkn_list->type = A_OUT_ID;
	else if (ft_strncmp(tkn_list->arg, "|", 3) == 0)
	{
		tkn_list->type = PIPE_ID;
		*cmd = 0;
	}
}

void	ft_assign_main_type(t_tkn *tkn_list, t_tkn *previous, size_t *cmd)
{
	if (previous && previous->type == IN_ID)
		tkn_list->type = INFILE_ID;
	else if (previous && (previous->type == OUT_ID
			|| previous->type == A_OUT_ID))
		tkn_list->type = OUTFILE_ID;
	else if (previous && previous->type == HDOC_IN_ID)
		tkn_list->type = HEOF_ID;
	else if (*cmd == 0)
	{
		tkn_list->type = CMD_ID;
		*cmd = 1;
	}
	else if (previous && *cmd == 1)
		tkn_list->type = ARG_ID;
}

void	ft_handle_other_type(t_tkn *tkn_list, int *loop)
{
	if (ft_better_analysis(tkn_list) == ERROR)
		tkn_list->type = ERROR;
	*loop = 0;
}
