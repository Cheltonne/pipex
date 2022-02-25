/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:05:18 by chajax            #+#    #+#             */
/*   Updated: 2022/02/25 14:59:50 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define _GNU_SOURCE
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

typedef struct s_data
{
	char	**possible_paths;
	char	**cmd_args;
	char	**av;
	char	**envp;
	char	*tmp;
	int		files[2];
	int		end[2];
	int		tmp_fw;
	int		tmp_fr;
	int		here_doc;
	int		cmd;
	pid_t	child1;
	pid_t	mid_child;
	pid_t	child2;
}				t_data;

void	pipex(int *files, t_data *data, int ac);
void	data_init(t_data *data, char **av, char **env);
void	open_pipe(t_data *data);
void	fork_wrapper(pid_t *child);
void	first_and_last(int *files, int *end, t_data *data);
void	mid_process(int *end, t_data *data);
void	middle_cmd(t_data *data);
void	transfer(int fd1, int fd2);
char	*find_path(t_data *data);
void	append_path(t_data *data);
int		grep_path(char **envp);
void	free_fct(t_data *data);
void	cmd_404(char *message);
void	free_and_null(char **to_free);
void	pipe_error(t_data *data);
void	execve_error(t_data *data, char *cmd);
void	here_doc(t_data *data, char *av, int *f1);
void	exit_error(t_data *data);
void	close_fds(t_data *data);
void	empty_and_destroy_pipe(t_data *data);
#endif
