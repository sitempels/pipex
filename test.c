/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:34:25 by stempels          #+#    #+#             */
/*   Updated: 2025/04/17 15:45:57 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/include/libft.h"

char	**get_paths(char *name, char **env);

int	main(void)
{
	int			i;
	char		**paths;
	extern char	**environ;

	paths = get_paths("PATH", environ);
	i = 0;
	while (paths[i])
	{
		printf("%s\n", paths[i]);
		i++;
	}
	return (0);
}

