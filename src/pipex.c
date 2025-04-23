/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:09:19 by stempels          #+#    #+#             */
/*   Updated: 2025/04/23 15:15:00 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_paths(char *name, char **env);

int	pipex(char ***arg, char **env, char *infile, char *outfile)
{
	int	pipefd[2];
	int	fd_in;
	int	fd_out;
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		fd_in = open(infile, O_RDONLY, O_CLOEXEC);
		close(pipefd[0]);
		dup2(pipefd[1], 1);
//		close(pipefd[1]);
		dup2(fd_in, 0);
		execve(arg[1][0], arg[0], env);
		return (free(arg[1][0]), ft_free_arr(arg[0]), -1);
	}
	close(pipefd[1]);
	dup2(pipefd[0], 0);
//	close(pipefd[0]);
	fd_out = open(outfile, O_WRONLY, O_CLOEXEC);
	dup2(fd_out, 1);
	execve(arg[3][0], arg[2], env);
	return (free(arg[1][0]), ft_free_arr(arg[0]), -1);
}

static char	**get_paths(char *name, char **env)
{
	int	i;
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

char	*path_cmd(char *cmd, char **env)
{
	int	i;
	int	error;
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
