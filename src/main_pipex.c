/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:01:02 by stempels          #+#    #+#             */
/*   Updated: 2025/04/21 15:55:03 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int	fd_out;
	extern char	**environ;

	if (argc < 1)
		return (-1);
	fd_out = open(argv[4], O_WRONLY);
	pipex(argv, fd_out, environ);
	return (0);
}
