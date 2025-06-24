/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_replace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:52:45 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"
//
// Main function orchestrating the placeholder replacement within *str
int	ft_replace_placeholders(t_data *data, char **str)
{
	char	*arg_orig;
	char	*new_arg;
	size_t	i;
	int		seg_len;

	if (!str || !*str)
		return (0);
	arg_orig = *str;
	new_arg = NULL;
	i = 0;
	while (arg_orig[i])
	{
		seg_len = ft_process_segment_placehd(data, &new_arg, arg_orig, i);
		if (seg_len == ERROR)
			return (ft_free_str(&new_arg), ERROR);
		if (seg_len == 0)
			break ;
		i += seg_len;
	}
	if (!new_arg)
		return (0);
	if (ft_finalize_replacement(&new_arg, str, arg_orig, i) != 0)
		return (ERROR);
	return (0);
}

// Processes one segment (prefix + placeholder) of the original string
// Returns length processed, 0 if no '$', or ERROR on failure
int	ft_process_segment_placehd(t_data *data, char **new_arg, char *arg,
		size_t current_i)
{
	int		pos;
	size_t	placehd_len;
	size_t	processed_len;

	pos = ft_strchr_int(&arg[current_i], '$');
	if (pos == -1)
		return (0);
	if (pos > 0)
		if (ft_append_prefix(new_arg, &arg[current_i], pos) != 0)
			return (ERROR);
	if (ft_handle_placeholder_part(data, new_arg, arg, current_i + pos) != 0)
		return (ERROR);
	placehd_len = ft_strlen_placeholder(&arg[current_i + pos + 1]);
	processed_len = pos + 1 + placehd_len;
	return (processed_len);
}

// Determines which placeholder type it is and calls the correct append function
int	ft_handle_placeholder_part(t_data *data, char **new_arg, char *arg,
		size_t dollar_idx)
{
	size_t	placehd_len;
	char	*placeholder_start;

	placeholder_start = arg + dollar_idx;
	placehd_len = ft_strlen_placeholder(placeholder_start + 1);
	if (placehd_len == 0)
		return (ft_append_dollar_sign(new_arg));
	else if (placeholder_start[1] == '?')
		return (ft_append_exit_status(data, new_arg));
	else if (dollar_idx > 1 && arg[dollar_idx - 1] == '<'
		&& arg[dollar_idx - 2] == '<')
		return (ft_append_literal_placeholder(new_arg, placeholder_start,
				placehd_len));
	else
		return (ft_append_env_case(data, new_arg, placeholder_start + 1,
				placehd_len));
}

// Finalizes the replacement after the loop: appends suffix or assigns new_arg
int	ft_finalize_replacement(char **new_arg_ptr, char **str_ptr,
		char *arg_orig, size_t suffix_idx)
{
	if (arg_orig[suffix_idx])
	{
		if (ft_append_suffix(new_arg_ptr, str_ptr, &arg_orig[suffix_idx]) != 0)
			return (ERROR);
	}
	else
	{
		ft_free_str(str_ptr);
		*str_ptr = *new_arg_ptr;
		*new_arg_ptr = NULL;
	}
	return (0);
}

// Appends the final suffix and updates the original string pointer *str_ptr
int	ft_append_suffix(char **new_arg_ptr, char **str_ptr,
		char *suffix_start)
{
	char	*temp_join;

	if (!*new_arg_ptr)
		return (0);
	temp_join = ft_strjoin(*new_arg_ptr, suffix_start);
	ft_free_str(new_arg_ptr);
	ft_free_str(str_ptr);
	if (!temp_join)
		return (ft_error("strjoin suffix failed"), ERROR);
	*str_ptr = temp_join;
	return (0);
}
