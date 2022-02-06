/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:05:18 by chajax            #+#    #+#             */
/*   Updated: 2022/02/06 19:38:28 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct s_data
{
	char 	**possible_paths;
	char 	**cmd_args;
	char 	**av;
	char 	**envp;
	char	*tmp;
}				t_data;

void	pipex(int f1, int f2, t_data *data);
int		child1_process(int f1, int cmd1, t_data *data);
int		child2_process(int f2, int cmd2, t_data *data);
char	*find_path(t_data *data);
void	append_path(t_data *data);
int		grep_path(char **envp);
void	free_fct(t_data *data);
void	cmd_404(char *message);
void    free_and_null(char **to_free);
#endif
