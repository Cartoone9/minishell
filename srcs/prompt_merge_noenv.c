/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_merge_noenv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:24:26 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

char	*ft_strjoin_prompt_noenv(char const *s1, char const *s2, char const *s3)
{
	size_t	ret_size;
	char	*ret;

	if (!s1 || !s2 || !s3)
		return (ft_error("missing str in ft_strjoin_prompt"), NULL);
	ret_size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 4 + 1;
	ret = malloc(sizeof(char) * ret_size);
	if (ret == NULL)
		return (ft_error("ft_strjoin_prompt malloc failed"), NULL);
	ret[0] = '\0';
	ft_strlcat(ret, s1, ret_size);
	ft_strlcat(ret, "@", ret_size);
	ft_strlcat(ret, s2, ret_size);
	ft_strlcat(ret, ":", ret_size);
	ft_strlcat(ret, s3, ret_size);
	ft_strlcat(ret, "$ ", ret_size);
	return (ret);
}
