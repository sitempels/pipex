/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:09:19 by stempels          #+#    #+#             */
/*   Updated: 2025/04/21 15:59:43 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char *path_cmd(char *cmd, char **env);
static char	**get_paths(char *name, char **env);

int	pipex(char **argv, int fd_out, char **env)
{
	int	pipefd[2];
	pid_t	pid;
	char	*path;
	char 	*test[3];

	path = path_cmd(argv[2], env);
	if (pipe(pipefd) == -1)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		test[0] = argv[2];
		test[1] = argv[1];
		test[2] = '\0';
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		execve(path, test, env);
		return (EXIT_FAILURE);
	}
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	path = path_cmd(argv[3], env);
	waitpid(pid, 0, 0);
	test[0] = argv[3];
	test[1] = '\0';
	test[2] = '\0';
	dup2(fd_out, 1);
	execve(path, test, env);
	return (0);
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

static char *path_cmd(char *cmd, char **env)
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
