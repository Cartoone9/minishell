/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_spe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:54:04 by *******           #+#    #+#             */
/*   Updated: 2025/04/11 18:16:33 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

char	*ft_strjoin_input(char *s1, char *s2)
{
	char	*ret;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = 0;
	s2_len = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		s1_len = ft_strlen(s1);
	if (s2)
		s2_len = ft_strlen(s2);
	ret = malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (ret == NULL)
		return (NULL);
	return (ft_strjoin_input_copy(ret, s1, s2));
}

char	*ft_strjoin_input_copy(char *ret, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	if (s1 && s2)
		ret[i++] = ' ';
	j = 0;
	while (s2 && s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin_error(char const *s1, char const *s2, char const *s3)
{
	char	*ret;
	size_t	i;
	size_t	j;

	ret = malloc(sizeof(char) * (ft_strlen(s1)+ft_strlen(s2)+ft_strlen(s3)+3));
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		ret[i++] = s1[j++];
	j = 0;
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i++] = ':';
	ret[i++] = ' ';
	j = 0;
	while (s3[j])
		ret[i++] = s3[j++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*ret;
	size_t	i;
	size_t	j;

	ret = malloc(sizeof(char) * (ft_strlen(s1)+ft_strlen(s2)+ft_strlen(s3)+1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		ret[i++] = s1[j++];
	j = 0;
	while (s2[j])
		ret[i++] = s2[j++];
	j = 0;
	while (s3[j])
		ret[i++] = s3[j++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin_path(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;

	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i++] = '/';
	j = 0;
	while (s2[j])
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	return (ret);
}
