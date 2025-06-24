/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_merge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:24:26 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

// There's 7 colors in the prompt so we multiply the '\001' and '\002' by 7.
// '\001' and '\002' are used (only by readline)
// to say "here are non printable characters" which is the case for colors.
// It's used so the prompt is not buggy and doesn't write over itself.
// The +5 is for : +4 char fixed and +1 for the null terminator.

char	*ft_strjoin_prompt(char const *s1, char const *s2, char const *s3)
{
	size_t	color_len;
	size_t	ret_size;
	char	*ret;

	if (!s1 || !s2 || !s3)
		return (ft_error("missing str in ft_strjoin_prompt"), NULL);
	color_len = ft_strlen(RED) + ft_strlen(ORANGE) + ft_strlen(YELLOW)
		+ ft_strlen(GREEN) + ft_strlen(TEAL) + ft_strlen(BLUE)
		+ ft_strlen(RESET) + (ft_strlen("\001") * 7) + (ft_strlen("\002") * 7);
	ret_size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + color_len + 5;
	ret = malloc(sizeof(char) * ret_size);
	if (ret == NULL)
		return (ft_error("ft_strjoin_prompt malloc failed"), NULL);
	ret[0] = '\0';
	ft_append_user(ret, ret_size, s1);
	ft_append_host(ret, ret_size, s2);
	ft_append_cwd(ret, ret_size, s3);
	ft_append_end(ret, ret_size);
	return (ret);
}

void	ft_append_user(char *ret, size_t ret_size, const char *s1)
{
	ft_strlcat(ret, "\001", ret_size);
	ft_strlcat(ret, RED, ret_size);
	ft_strlcat(ret, "\002", ret_size);
	ft_strlcat(ret, s1, ret_size);
}

void	ft_append_host(char *ret, size_t ret_size, const char *s2)
{
	ft_strlcat(ret, "\001", ret_size);
	ft_strlcat(ret, ORANGE, ret_size);
	ft_strlcat(ret, "\002", ret_size);
	ft_strlcat(ret, "@", ret_size);
	ft_strlcat(ret, "\001", ret_size);
	ft_strlcat(ret, YELLOW, ret_size);
	ft_strlcat(ret, "\002", ret_size);
	ft_strlcat(ret, s2, ret_size);
}

void	ft_append_cwd(char *ret, size_t ret_size, const char *s3)
{
	ft_strlcat(ret, "\001", ret_size);
	ft_strlcat(ret, GREEN, ret_size);
	ft_strlcat(ret, "\002", ret_size);
	ft_strlcat(ret, ":", ret_size);
	ft_strlcat(ret, "\001", ret_size);
	ft_strlcat(ret, TEAL, ret_size);
	ft_strlcat(ret, "\002", ret_size);
	ft_strlcat(ret, s3, ret_size);
}

void	ft_append_end(char *ret, size_t ret_size)
{
	ft_strlcat(ret, "\001", ret_size);
	ft_strlcat(ret, BLUE, ret_size);
	ft_strlcat(ret, "\002", ret_size);
	ft_strlcat(ret, "$ ", ret_size);
	ft_strlcat(ret, "\001", ret_size);
	ft_strlcat(ret, RESET, ret_size);
	ft_strlcat(ret, "\002", ret_size);
}
