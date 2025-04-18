/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:52:04 by stempels          #+#    #+#             */
/*   Updated: 2025/04/17 15:54:15 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_full_path(char const *s1, char const *s2)
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
