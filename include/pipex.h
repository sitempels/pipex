/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:52:25 by stempels          #+#    #+#             */
/*   Updated: 2025/04/23 10:33:22 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <fcntl.h>
# include <sys/types.h>
# define _OPEN_SYS
# include <sys/wait.h>
/*---------------------------MACRO--------------------------------------------*/
/**/
/*---------------------------MACRO--------------------------------------------*/
/**/
/*---------------------------FUNCT--------------------------------------------*/
int		pipex(char ***arg, char **env, char *infile, char *outfile);
char	*path_cmd(char *cmd, char **env);
/**/
/*------------UTILS*/
char	*get_full_path(char const *s1, char const *s2);
/**/
#endif
