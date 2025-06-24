/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:06:59 by *******           #+#    #+#             */
/*   Updated: 2025/04/11 18:31:14 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_MAX
#  define FD_MAX 512
# endif

typedef struct s_counter
{
	size_t	local;
	size_t	global;
}			t_counter;

char		*get_next_line(int fd, int clear);
char		*ft_fill_ret(char **stash, char *buffer);
char		*ft_fill_stash(char *buffer);
size_t		ft_find_next_return(char *str);
size_t		ft_full_line(char *str);
size_t		ft_strlen_gnl(char *str);
void		ft_clean_used_stash(char **stash, char *buffer, size_t end);
int			ft_stash_n_clean_buffer(char **stash, char *buffer,
				ssize_t char_read);
void		ft_clear_buffer(char buffer[BUFFER_SIZE + 1]);
char		*gnl_read_and_stash(int fd, char buffer[FD_MAX][BUFFER_SIZE + 1],
				char **stash);
void		ft_free_str(char **str);

#endif
