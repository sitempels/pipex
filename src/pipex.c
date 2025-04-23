/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:09:19 by stempels          #+#    #+#             */
/*   Updated: 2025/04/23 16:35:15 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	child(char ***arg, char **env, char *infile, int pipefd);

int	pipex(char ***arg, char **env, char *infile, char *outfile)
{
	int		pipefd[2];
	int		fd_out;
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		close(pipefd[0]);
		if (child(arg, env, infile, pipefd[1]) == -1)
			return (-1);
	}
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	fd_out = open(outfile, O_WRONLY, O_CLOEXEC);
	dup2(fd_out, 1);
	close(fd_out);
	execve(arg[3][0], arg[2], env);
	return (free(arg[3][0]), ft_free_arr(arg[0]), -1);
}

static int	child(char ***arg, char **env, char *infile, int pipefd)
{
	int	fd_in;

	fd_in = open(infile, O_RDONLY, O_CLOEXEC);
	dup2(pipefd, 1);
	close(pipefd);
	dup2(fd_in, 0);
	close(fd_in);
	execve(arg[1][0], arg[0], env);
	return (close(fd_in), free(arg[1][0]), ft_free_arr(arg[0]), -1);
}
