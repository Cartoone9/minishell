/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:24:26 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

void	ft_free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	ft_free_strr(char ***strr)
{
	size_t	i;

	if (!(*strr))
		return ;
	i = 0;
	while ((*strr)[i])
	{
		free((*strr)[i]);
		(*strr)[i] = NULL;
		i++;
	}
	if ((*strr))
	{
		free((*strr));
		(*strr) = NULL;
	}
}

void	ft_free_tokens(t_tkn *tkn_list)
{
	t_tkn	*temp;

	if (!tkn_list)
		return ;
	while (tkn_list)
	{
		temp = NULL;
		ft_free_str(&tkn_list->arg);
		if (tkn_list->next)
			temp = tkn_list->next;
		free(tkn_list);
		tkn_list = NULL;
		if (temp)
			tkn_list = temp;
	}
}

void	ft_free_hdoc(t_hdoc *hdoc_list)
{
	t_hdoc	*temp;

	if (!hdoc_list)
		return ;
	while (hdoc_list)
	{
		ft_unlink_hdoc_file(hdoc_list->hdoc_filen);
		temp = NULL;
		ft_free_str(&hdoc_list->hdoc_eof);
		if (hdoc_list->next)
			temp = hdoc_list->next;
		free(hdoc_list);
		hdoc_list = NULL;
		if (temp)
			hdoc_list = temp;
	}
}

void	ft_free_cmds(t_cmd *cmd_list)
{
	t_cmd	*temp;

	while (cmd_list)
	{
		temp = NULL;
		if (cmd_list->next)
			temp = cmd_list->next;
		if (cmd_list->fd_in > 0)
		{
			close(cmd_list->fd_in);
			cmd_list->fd_in = 0;
		}
		if (cmd_list->fd_out > 0)
		{
			close(cmd_list->fd_out);
			cmd_list->fd_out = 0;
		}
		ft_free_strr(&cmd_list->args);
		ft_free_str(&cmd_list->path);
		free(cmd_list);
		cmd_list = NULL;
		if (temp)
			cmd_list = temp;
	}
}
