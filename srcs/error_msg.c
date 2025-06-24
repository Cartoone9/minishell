/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:38:37 by *******           #+#    #+#             */
/*   Updated: 2025/04/11 18:36:43 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

void	ft_error_found(t_tkn *tkn_list, char *source, int which)
{
	if (tkn_list)
		tkn_list->type = -1;
	ft_handle_initial_error(tkn_list, source, which);
}

void	ft_handle_initial_error(t_tkn *tkn_list, char *source, int which)
{
	char	*error_msg;

	if (which == 0)
		error_msg = ft_syntax_error_msg(tkn_list->arg);
	else if (which == 1)
		error_msg = ft_syntax_error_msg(tkn_list->next->arg);
	else if (which == 2)
		error_msg = ft_syntax_error_msg("newline");
	else if (which == 3)
		error_msg = ft_strjoin_error("minishell: ", source, strerror(errno));
	else if (which == 4)
		error_msg = ft_strjoin_error("minishell: ", source,
				"command not found");
	else if (which == 5)
		error_msg = ft_strjoin_error("minishell: ", "cd", "HOME not set");
	else if (which == 6)
		error_msg = ft_strjoin_error("minishell: exit: ", source,
				"numeric argument required");
	else
		return (ft_handle_errors_suite(source, which));
	if (!error_msg)
		error_msg = "missing error";
	ft_error_min(error_msg);
	ft_free_str(&error_msg);
}

void	ft_handle_errors_suite(char *source, int which)
{
	char	*error_msg;

	if (which == 7)
		error_msg = ft_strjoin_three("minishell: export: `", source,
				"': not a valid identifier");
	else if (which == 8)
		error_msg = ft_strjoin_error("minishell: cd: ", source,
				"No such file or directory");
	else if (which == 9)
		error_msg = ft_strjoin_error("minishell: cd: ", source,
				"Permission denied");
	else if (which == 10)
		error_msg = ft_strjoin_error("minishell: cd: ", source,
				"Not a directory");
	else if (which == 11)
		error_msg = ft_strjoin_three(
				"minishell: warning: "
				"here-document delimited by end-of-file (wanted `",
				source, "')");
	else
		return (ft_handle_errors_suite_two(source, which));
	if (!error_msg)
		error_msg = "missing error";
	ft_error_min(error_msg);
	ft_free_str(&error_msg);
}

void	ft_handle_errors_suite_two(char *source, int which)
{
	char	*error_msg;

	if (which == 12)
		error_msg = ft_strjoin_three("minishell: exit: ", source,
				": numeric argument required");
	else if (which == 13)
		error_msg = ft_strjoin_three("minishell: ", source,
				": ambiguous redirect");
	else if (which == 14)
		error_msg = ft_strjoin_error("minishell: ", source, "Is a directory");
	else if (which == 15)
		error_msg = ft_strjoin_error("minishell: ", source,
				"No such file or directory");
	if (!error_msg)
		error_msg = "missing error";
	ft_error_min(error_msg);
	ft_free_str(&error_msg);
}

char	*ft_syntax_error_msg(char *arg)
{
	char	*ret;
	char	*syntax;
	char	*end;

	syntax = "minishell: syntax error near unexpected token `";
	end = "'";
	ret = ft_strjoin_three(syntax, arg, end);
	if (!ret)
		return (NULL);
	return (ret);
}
