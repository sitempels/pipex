/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:07:05 by stempels          #+#    #+#             */
/*   Updated: 2025/04/22 13:22:32 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_arr(char **array)
{
	int	j;

	j = 0;
	while (array[j])
	{
		if (array[j])
			free(array[j]);
		j++;
	}
	free(array);
	array = NULL;
	return ;
}
