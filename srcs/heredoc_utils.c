/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:52:45 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_isthere_hdoc(t_data *data)
{
	t_tkn	*cursor;
	size_t	already_c;
	size_t	isthere;
	char	*eof;

	if (!data || !data->tkn_list)
		return (ft_error("missing param in isthere_hdoc"), ERROR);
	isthere = 0;
	cursor = data->tkn_list;
	already_c = ft_how_manyhdoc(data);
	while (cursor && cursor->next && cursor->next->type != ERROR)
	{
		if (cursor->type == 2 && already_c > 0)
			already_c--;
		else if (cursor->type == 2 && already_c == 0)
		{
			eof = cursor->next->arg;
			if (ft_clean_eof(&eof) == ERROR || ft_make_hdoc_node(data,
					eof) == ERROR)
				return (ERROR);
			isthere = 1;
		}
		cursor = cursor->next;
	}
	return (isthere);
}

size_t	ft_how_manyhdoc(t_data *data)
{
	t_hdoc	*cursor_hdoc;
	size_t	i;

	if (!data->hdoc_list)
		return (0);
	i = 0;
	cursor_hdoc = data->hdoc_list;
	while (cursor_hdoc)
	{
		i++;
		cursor_hdoc = cursor_hdoc->next;
	}
	return (i);
}

int	ft_make_hdoc_node(t_data *data, char *eof)
{
	t_hdoc	*cursor_hdoc;
	t_hdoc	*new_hdoc;

	if (!data || !eof)
		return (ft_error("missing parameter in make_hdoc_node"), ERROR);
	new_hdoc = malloc(sizeof(t_hdoc));
	if (!new_hdoc)
		return (ft_error("malloc 1 failed in make_hdoc_node"), ERROR);
	new_hdoc->saved = 0;
	new_hdoc->hdoc_filen = 0;
	new_hdoc->next = NULL;
	new_hdoc->hdoc_eof = ft_strdup(eof);
	if (!new_hdoc->hdoc_eof)
		return (ft_error("malloc 2 failed in make_hdoc_node"), free(new_hdoc),
			ERROR);
	if (data && !data->hdoc_list)
		data->hdoc_list = new_hdoc;
	else
	{
		cursor_hdoc = data->hdoc_list;
		while (cursor_hdoc && cursor_hdoc->next)
			cursor_hdoc = cursor_hdoc->next;
		cursor_hdoc->next = new_hdoc;
	}
	return (0);
}

// Appends the processed input line to the main heredoc buffer.
int	ft_append_to_hdoc_buffer(char **buffer, char **line_ptr)
{
	char	*temp_join;

	if (*line_ptr && *buffer)
	{
		temp_join = ft_strjoin(*buffer, *line_ptr);
		ft_free_str(line_ptr);
		ft_free_str(buffer);
		if (!temp_join)
			return (ft_error("strjoin 2 failed in ft_temp_file"), ERROR);
		*buffer = temp_join;
	}
	else if (*line_ptr && !*buffer)
	{
		*buffer = *line_ptr;
		*line_ptr = NULL;
	}
	return (0);
}
