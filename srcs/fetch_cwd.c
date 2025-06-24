/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_cwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:29:44 by *******           #+#    #+#             */
/*   Updated: 2025/04/13 18:05:06 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

static ssize_t	ft_count_matching_entries(int which);
static int		ft_entry_matches(struct dirent *entry, int which);
static int		ft_fill_entry_array(char **ret, int which);
static char		*ft_create_entry_string(struct dirent *entry, int which);

char	**ft_fetch_cwd(int which)
{
	char	**ret;
	ssize_t	n_signed;
	size_t	n;

	n_signed = ft_count_matching_entries(which);
	if (n_signed == ERROR)
		return (NULL);
	n = (size_t)n_signed;
	ret = malloc(sizeof(char *) * (n + 1));
	if (!ret)
		return (ft_error("malloc failed in fetch_cwd_data"), NULL);
	if (ft_fill_entry_array(ret, which) != 0)
	{
		ft_free_strr(&ret);
		return (NULL);
	}
	return (ret);
}

static ssize_t	ft_count_matching_entries(int which)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			n;

	dir = opendir(".");
	if (!dir)
		return (ft_error("opendir failed in fetch_cwd"), ERROR);
	n = 0;
	errno = 0;
	entry = readdir(dir);
	if (!entry && errno != 0)
	{
		closedir(dir);
		return (ft_error("readdir failed in fetch_cwd"), ERROR);
	}
	while (entry)
	{
		if (ft_entry_matches(entry, which))
			n++;
		entry = readdir(dir);
	}
	closedir(dir);
	return ((ssize_t)n);
}

static int	ft_entry_matches(struct dirent *entry, int which)
{
	if (!entry)
		return (0);
	if (which == 0)
	{
		if (entry->d_name[0] != '.')
			return (1);
	}
	else if (which == 1)
	{
		if (entry->d_name[0] == '.')
			return (1);
	}
	else if (which == 2)
	{
		if (entry->d_name[0] != '.' && ft_is_a_directory(entry->d_name))
			return (1);
	}
	else if (which == 3)
	{
		if (entry->d_name[0] == '.' && ft_is_a_directory(entry->d_name))
			return (1);
	}
	return (0);
}

static int	ft_fill_entry_array(char **ret, int which)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			i;

	dir = opendir(".");
	if (!dir)
		return (ft_error("opendir fail in fetch_cwd"), ERROR);
	i = 0;
	errno = 0;
	entry = readdir(dir);
	if (!entry && errno != 0)
		return (closedir(dir), ft_error("rddir fail fetch_cwd"), ERROR);
	while (entry)
	{
		if (ft_entry_matches(entry, which))
		{
			ret[i] = ft_create_entry_string(entry, which);
			if (!ret[i])
				return (closedir(dir), ERROR);
			i++;
		}
		entry = readdir(dir);
	}
	ret[i] = NULL;
	return (closedir(dir), 0);
}

static char	*ft_create_entry_string(struct dirent *entry, int which)
{
	char	*name;
	char	*temp;

	name = NULL;
	if (which == 0 || which == 1)
	{
		name = ft_strdup(entry->d_name);
		if (!name)
			ft_error("strdup 0 failed in fetch_cwd");
	}
	else if (which == 2 || which == 3)
	{
		temp = ft_strdup(entry->d_name);
		if (!temp)
			return (ft_error("strdup 1 failed in fetch_cwd"), NULL);
		name = ft_strjoin(temp, "/");
		ft_free_str(&temp);
		if (!name)
			ft_error("strjoin failed in fetch_cwd");
	}
	return (name);
}
