/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:24:26 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

/*void	ft_tester_tkn(t_tkn *tkn_list)*/
/*{*/
/*	t_tkn	*cursor_tkn;*/
/*	int		i;*/
/**/
/*	if (!tkn_list)*/
/*		return ;*/
/*	i = 0;*/
/*	cursor_tkn = tkn_list;*/
/*	while (cursor_tkn)*/
/*	{*/
/*		if (i == 0)*/
/*			printf("\n");*/
/*		printf("[token %i] arg : %-10s", i, cursor_tkn->arg);*/
/*		printf(" | type : (%02i)", cursor_tkn->type);*/
/*		printf(" | next : (%p)", cursor_tkn->next);*/
/*		printf("\n\n");*/
/*		cursor_tkn = cursor_tkn->next;*/
/*		i++;*/
/*	}*/
/*}*/
/**/
/*void	ft_tester_cmd(t_data *data)*/
/*{*/
/*	t_cmd	*cursor_cmd;*/
/*	int		i;*/
/*	int		j;*/
/**/
/*	if (!data || !data->cmd_list)*/
/*		return ;*/
/*	i = 0;*/
/*	cursor_cmd = data->cmd_list;*/
/*	while (cursor_cmd)*/
/*	{*/
/*		if (i == 0)*/
/*			printf("\n");*/
/*		printf("[command %i] args  : ", i);*/
/*		j = 0;*/
/*		while (cursor_cmd->args[j])*/
/*		{*/
/*			printf("'%s'", cursor_cmd->args[j]);*/
/*			j++;*/
/*			if (cursor_cmd->args[j])*/
/*				printf(" ");*/
/*		}*/
/*		printf(" | path : '%s'", cursor_cmd->path);*/
/*		printf(" | pid : (%02i)", cursor_cmd->pid);*/
/*		printf(" | fd_in : (%02i)", cursor_cmd->fd_in);*/
/*		printf(" | fd_out : (%02i)", cursor_cmd->fd_out);*/
/*		printf(" | pipe : {%02i, %02i}", cursor_cmd->pipe[0],*/
/*			cursor_cmd->pipe[1]);*/
/*		printf(" | error : (%02li)", cursor_cmd->error);*/
/*		printf("\n\n");*/
/*		cursor_cmd = cursor_cmd->next;*/
/*		i++;*/
/*	}*/
/*}*/
/**/
/*void	ft_tester_strr(char **strr)*/
/*{*/
/*	size_t	i;*/
/**/
/*	i = 0;*/
/*	while (strr && strr[i])*/
/*	{*/
/*		printf("strr[%li] : %s\n", i, strr[i]);*/
/*		i++;*/
/*	}*/
/*	return ;*/
/*}*/
