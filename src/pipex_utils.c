/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:52:04 by stempels          #+#    #+#             */
/*   Updated: 2025/04/23 16:32:51 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_paths(char *name, char **env);
static char	*get_full_path(char const *s1, char const *s2);

char	*path_cmd(char *cmd, char **env)
{
	int		i;
	int		error;
	char	*path_full;
	char	**paths;

	paths = get_paths("PATH", env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path_full = get_full_path(paths[i], cmd);
		error = access(path_full, F_OK | X_OK);
		if (error == 0)
			return (path_full);
		free(path_full);
		path_full = NULL;
		i++;
	}
	return (NULL);
}

static char	**get_paths(char *name, char **env)
{
	int		i;
	char	**paths;
	size_t	n_size;

	n_size = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_memcmp(env[i], name, n_size) == 0)
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	paths = ft_split(&env[i][n_size + 1], ':');
	return (paths);
}

static char	*get_full_path(char const *s1, char const *s2)
{
	char	*s3;
	size_t	lens1;
	size_t	lens2;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	s3 = (char *) malloc (sizeof(char) * (lens1 + lens2 + 2));
	if (!s3)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		s3[j++] = s1[i++];
	s3[j++] = '/';
	i = 0;
	while (s2[i])
		s3[j++] = s2[i++];
	s3[j] = 0;
	return (s3);
}
