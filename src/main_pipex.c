/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:01:02 by stempels          #+#    #+#             */
/*   Updated: 2025/04/23 15:11:31 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_arg(char ***arg, char **env);
static int	handle_file(char **arg);

int	main(int argc, char **argv)
{
	char	*infile;
	char	*outfile;
	char	**new_arg[5];
	extern char	**environ;

	if (argc != 5)
		return (-1);
	if (!handle_file(argv))
		return (-1);
	infile = argv[1];
	outfile = argv[4];
	new_arg[0] = &argv[2];
	new_arg[1] = &argv[1];
	new_arg[2] = &argv[3];
	new_arg[3] = &argv[4];
	new_arg[4] = NULL;
	if (!check_arg(new_arg, environ))
		return (-1);
	pipex(new_arg, environ, infile, outfile);
	return (0);
}

static int	handle_file(char **arg)
{
	if (access(arg[4], F_OK) != -1)
	{
		unlink(arg[4]);
		open(arg[4], O_CREAT, 00777);
	}
	if (access(arg[1], F_OK | W_OK) == -1
		|| access(arg[4], F_OK | R_OK) == -1)
		return (0);
	return (1);
}

static int	check_arg(char ***arg, char **env)
{
	int	fd;
	char	*path_cmd1;
	char	*path_cmd2;

	arg[0] = ft_split(arg[0][0], ' ');
	if (!arg[0])
		return (0);
	arg[2] = ft_split(arg[2][0], ' ');
	if (!arg[2])
		return (ft_free_arr(arg[0]), 0);
	path_cmd1 = path_cmd(arg[0][0], env);
	if (!path_cmd1)
		return (ft_free_arr(arg[0]), ft_free_arr(arg[2]), 0);
	path_cmd2 = path_cmd(arg[2][0], env);
	if (!path_cmd2)
		return (free(path_cmd1), ft_free_arr(arg[0]),
			ft_free_arr(arg[2]), 0);
	arg[1][0] = path_cmd1;
	arg[3][0] = path_cmd2;
	return (1);
}
