/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:38:37 by *******           #+#    #+#             */
/*   Updated: 2025/04/11 00:26:15 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

void	ft_error(char *error_msg)
{
	write(2, "\033[1;38;2;233;0;36mError\033[0m\n", 28);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
}

// the full_error_msg is used to avoid a buffer issue
// when multiple child returned error messages,
// the multiple write would get out of order
void	ft_error_min(char *error_msg)
{
	char	*full_error_msg;

	full_error_msg = ft_strjoin(error_msg, "\n");
	if (!full_error_msg)
	{
		write(2, error_msg, ft_strlen(error_msg));
		write(2, "\n", 1);
	}
	else
	{
		write(2, full_error_msg, ft_strlen(full_error_msg));
		free(full_error_msg);
	}
}

int	ft_check_tkn_error(t_tkn *tkn_list)
{
	if (!tkn_list)
		return (0);
	if (tkn_list->type == 5)
		return (ft_error_found(tkn_list, NULL, 0), 1);
	return (ft_check_tkn_error_loop(tkn_list));
}

int	ft_check_tkn_error_loop(t_tkn *tkn_list)
{
	int	type;
	int	type_n;

	while (tkn_list && tkn_list->next)
	{
		type = tkn_list->type;
		type_n = tkn_list->next->type;
		if (((type >= IN_ID && type <= A_OUT_ID) && (type_n >= IN_ID
					&& type_n <= PIPE_ID)) || (type == PIPE_ID
				&& type_n == PIPE_ID))
		{
			tkn_list->type = ERROR;
			return (ft_error_found(tkn_list, NULL, 1), 1);
		}
		tkn_list = tkn_list->next;
	}
	return (ft_check_tkn_error_end(tkn_list));
}

int	ft_check_tkn_error_end(t_tkn *tkn_list)
{
	int	type;

	if (tkn_list && !tkn_list->next)
	{
		type = tkn_list->type;
		if (type == IN_ID || type == HDOC_IN_ID || type == OUT_ID
			|| type == A_OUT_ID)
		{
			tkn_list->type = ERROR;
			return (ft_error_found(tkn_list, NULL, 2), 1);
		}
	}
	return (0);
}
