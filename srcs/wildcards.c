/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:19:15 by *******           #+#    #+#             */
/*   Updated: 2025/04/13 19:57:38 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_replace_wildcards(char ***old_strr, t_sizet *szt)
{
	char	**f_all;
	char	**f_valid;
	char	*wildcard;
	size_t	at_least;

	if (!(*old_strr) || !(*old_strr)[szt->j - 1] || ft_strchr((*old_strr)[szt->j
			- 1], '*') == NULL)
		return (0);
	wildcard = (*old_strr)[szt->j - 1];
	f_all = ft_fetch_files_based_on_wildcard(wildcard);
	if (!f_all)
		return (ERROR);
	f_valid = ft_filter_valid_files(f_all, wildcard, &at_least);
	if (!f_valid)
		return (ERROR);
	if (!at_least)
	{
		return (ft_free_strr(&f_valid), 0);
	}
	if (ft_merge_strr(old_strr, f_valid, szt) == ERROR)
	{
		return (ft_free_strr(&f_valid), ERROR);
	}
	return (ft_free_strr(&f_valid), 1);
}

char	**ft_fetch_files_based_on_wildcard(char *wildcard)
{
	char	**f_all;
	size_t	len;

	len = ft_strlen(wildcard);
	if (wildcard[0] == '.' && wildcard[len - 1] == '/')
	{
		f_all = ft_fetch_cwd(3);
	}
	else if (wildcard[len - 1] == '/')
	{
		f_all = ft_fetch_cwd(2);
	}
	else if (wildcard[0] == '.')
	{
		f_all = ft_fetch_cwd(1);
	}
	else
		f_all = ft_fetch_cwd(0);
	return (f_all);
}

char	**ft_filter_valid_files(char **f_all, char *wildcard, size_t *at_least)
{
	char	**f_valid;
	size_t	all_len;
	size_t	i;

	all_len = ft_strrlen(f_all);
	f_valid = malloc(sizeof(char *) * (all_len + 1));
	if (!f_valid)
		return (ft_error("malloc failed in ft_filter_valid_files"), NULL);
	i = 0;
	while (i < all_len + 1)
	{
		f_valid[i] = NULL;
		i++;
	}
	ft_perform_filtering_loop(f_all, f_valid, wildcard, at_least);
	return (f_valid);
}

void	ft_perform_filtering_loop(char **f_all, char **f_valid, char *wildcard,
		size_t *at_least)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	*at_least = 0;
	while (f_all[i])
	{
		if (ft_matching_wildcard(f_all[i], wildcard))
		{
			*at_least = 1;
			f_valid[j] = f_all[i];
			j++;
		}
		else
		{
			ft_free_str(&f_all[i]);
		}
		i++;
	}
	free(f_all);
}
