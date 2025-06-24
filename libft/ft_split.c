/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:07:10 by *******           #+#    #+#             */
/*   Updated: 2025/04/11 18:06:41 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

static int	count_words(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] != c)
			count++;
		else if (str[i] == c && str[i + 1] && str[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

static int	split_word(char **split, const char *s, char c, int word)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (s[end])
	{
		if (s[end] == c || s[end] == 0)
			start = end + 1;
		if (s[end] != c && (s[end + 1] == c || s[end + 1] == 0))
		{
			split[word] = malloc(sizeof(char) * (end - start + 2));
			if (!split[word])
				return (ft_error("split_word malloc failed"),
					ft_free_strr(&split), -1);
			ft_strlcpy(split[word], s + start, end - start + 2);
			word++;
		}
		end++;
	}
	split[word] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		count;

	count = count_words(s, c);
	split = malloc(sizeof(char *) * (count + 1));
	if (!split)
		return (ft_error("ft_split malloc failed"), NULL);
	if (split_word(split, s, c, 0) == -1)
		return (NULL);
	return (split);
}
/*
int	main(void)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split("", ' ');
	// char **split = ft_split(".....test  la.fonction......", '.');
	//printf("%d\n", count_words("test  la fonction  ", ' '));
	//printf("%d\n", count_words(".....test  la.fonction......", '.')); 5  12
	// while (split[i])
	// 	printf("%s\n", split[i++]);
	//ft_split("xxxxxxxxhello!", 120:'x')
}
 */
