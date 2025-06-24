/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_unquoted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:52:45 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_replace_placeholders_unquoted(t_data *data, char ***strr, size_t j,
		t_sizet *szt)
{
	char	*placehd_full;
	char	*placehd_name;
	size_t	placehd_len;

	if (!data || !strr || !*strr)
	{
		ft_error("missing data/strr in replace_placeholders_unquoted");
		return (ERROR);
	}
	placehd_full = strr[0][j - 1];
	if (!placehd_full || !placehd_full[0] || placehd_full[0] != '$')
		return (0);
	placehd_name = placehd_full + 1;
	placehd_len = ft_strlen_placeholder(placehd_name);
	if (placehd_len == 0)
		return (0);
	if (placehd_name[0] == '?')
	{
		return (ft_handle_dollar_question(data, strr, j));
	}
	else
	{
		return (ft_handle_other_case(data, strr, szt));
	}
}

int	ft_handle_dollar_question(t_data *data, char ***strr, size_t j)
{
	char	*new_arg;

	new_arg = ft_itoa(data->exit_status);
	if (!new_arg)
	{
		ft_error("itoa failed in handle_dollar_question");
		return (ERROR);
	}
	ft_free_str(&strr[0][j - 1]);
	strr[0][j - 1] = new_arg;
	return (0);
}

int	ft_handle_other_case(t_data *data, char ***strr, t_sizet *szt)
{
	char	*new_arg;
	char	*placehd_name;

	placehd_name = strr[0][szt->j - 1] + 1;
	new_arg = ft_getenv(data, placehd_name);
	if (!new_arg)
	{
		ft_error("getenv failed in handle_other_case");
		return (ERROR);
	}
	if (new_arg[0] == '\0')
	{
		return (ft_handle_empty_case(strr, szt->j, szt, new_arg));
	}
	else if ((szt->j >= 2 && strr[0][szt->j - 2]
		&& ft_previous_is_redirection(strr[0][szt->j - 2])) || (szt->j
		>= 3 && strr[0][szt->j - 2][ft_strlen(strr[0][szt->j - 2]) - 1] == '='
		&& ft_strncmp(strr[0][szt->j - 3], "export", 7) == 0))
	{
		ft_free_str(&strr[0][szt->j - 1]);
		strr[0][szt->j - 1] = new_arg;
		return (0);
	}
	else
		return (ft_handle_split_and_merge(strr, szt, new_arg));
}

int	ft_handle_empty_case(char ***strr, size_t j, t_sizet *szt,
		char *new_arg)
{
	if (j >= 2 && strr[0][j - 2] && ft_previous_is_redirection(strr[0][j - 2]))
	{
		free(new_arg);
		return (0);
	}
	ft_free_str(&strr[0][j - 1]);
	if (szt->strr_len > 1)
	{
		ft_free_str(&new_arg);
		szt->strr_len--;
		szt->j--;
	}
	else
	{
		strr[0][j - 1] = new_arg;
	}
	return (0);
}

int	ft_handle_split_and_merge(char ***strr, t_sizet *szt,
		char *new_arg)
{
	char	**new_arg_strr;
	size_t	ret;

	new_arg_strr = ft_split(new_arg, ' ');
	ft_free_str(&new_arg);
	if (!new_arg_strr)
		return (ERROR);
	if (new_arg_strr[0] && !new_arg_strr[1])
	{
		ft_free_str(&strr[0][szt->j - 1]);
		strr[0][szt->j - 1] = new_arg_strr[0];
		ft_free_str(&new_arg_strr[1]);
		free(new_arg_strr);
		return (0);
	}
	else
	{
		if (ft_merge_strr(strr, new_arg_strr, szt) == ERROR)
			return (ft_free_strr(&new_arg_strr), ERROR);
		ret = ft_strrlen(new_arg_strr);
		ft_free_strr(&new_arg_strr);
		return (ret);
	}
}
