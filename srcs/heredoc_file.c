/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:52:45 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

// Creates a temporary file and writes the heredoc buffer content to it.
// Associates the filename with the correct heredoc node.
// Frees the buffer upon successful write or on error.
int	ft_temp_file(t_data *data, char **buffer_ptr)
{
	t_hdoc	*cursor_hdoc;
	char	*filename;
	int		fd;

	if (!data || !data->hdoc_list || !buffer_ptr || !*buffer_ptr)
		return (ft_free_str(buffer_ptr),
			ft_error("missing hdoc_list or buffer"), ERROR);
	cursor_hdoc = ft_find_hdoc_node(data->hdoc_list);
	if (!cursor_hdoc)
		return (ft_free_str(buffer_ptr),
			ft_error("suitable hdoc node not found"), ERROR);
	filename = ft_generate_hdoc_filename(cursor_hdoc, buffer_ptr);
	if (!filename)
		return (ERROR);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_free_str(&filename);
	if (fd == -1)
		return (ft_free_str(buffer_ptr),
			ft_error("open failed in ft_temp_file"), ERROR);
	write(fd, *buffer_ptr, ft_strlen(*buffer_ptr));
	ft_free_str(buffer_ptr);
	close(fd);
	cursor_hdoc->saved = 1;
	return (0);
}

t_hdoc	*ft_find_hdoc_node(t_hdoc *list)
{
	t_hdoc	*cursor;

	if (!list)
		return (NULL);
	cursor = list;
	while (cursor->hdoc_filen != 0 && cursor->next)
		cursor = cursor->next;
	if (cursor->hdoc_filen != 0)
		return (NULL);
	return (cursor);
}

char	*ft_generate_hdoc_filename(t_hdoc *node, char **buf_ptr)
{
	char	*filename;
	char	*temp_filen;

	node->hdoc_filen++;
	while (1)
	{
		temp_filen = ft_itoa(node->hdoc_filen);
		if (!temp_filen)
			return (ft_error("itoa failed in ft_temp_file"),
				ft_free_str(buf_ptr), NULL);
		filename = ft_strjoin(HDOC_FILE, temp_filen);
		ft_free_str(&temp_filen);
		if (!filename)
			return (ft_error("strjoin failed in ft_temp_file"),
				ft_free_str(buf_ptr), NULL);
		if (access(filename, F_OK) != 0)
			break ;
		free(filename);
		node->hdoc_filen++;
	}
	return (filename);
}
