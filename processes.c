/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:26:05 by chajax            #+#    #+#             */
/*   Updated: 2022/02/06 22:09:41 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*exec_cmd(t_data *data)
{
	int		i;
	char	*tmp;
	char	*cmd;

	i = -1;
	while (data->possible_paths[++i])
	{
		tmp  = ft_strjoin(data->possible_paths[i], "/");
		cmd	= ft_strjoin(tmp, data->cmd_args[0]);
		free(tmp);
		if (!access(cmd, X_OK))
			return (cmd);
		free(cmd);
	}
	free_fct(data);
	return (NULL);
}

int	child1_process(int f1, int end, t_data *data)
{
	char	*cmd;

	if (dup2(f1, STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	if (dup2(end, STDOUT_FILENO) < 0)
		perror("dup2 error");
	close(f1);
	data->cmd_args = ft_split(data->av[2], ' ');
	cmd = exec_cmd(data);
	if (!cmd)
		cmd_404(data->cmd_args[0]);
	execve(cmd, data->cmd_args, data->envp);
	free(cmd);
	free_fct(data);
	exit(EXIT_FAILURE);
}

int	child2_process(int f2, int end, t_data *data)
{
	char	*cmd;

	if (dup2(f2, STDOUT_FILENO) < 0)
		perror("dup2 error");
	if(dup2(end, STDIN_FILENO) < 0)
		perror("dup2 error");
	close(f2);
	data->cmd_args = ft_split(data->av[3], ' '); 
	cmd = exec_cmd(data);
	if (!cmd)
		cmd_404(data->cmd_args[0]);
	execve(cmd, data->cmd_args, data->envp);
	free(cmd);
	free_fct(data);
	exit(EXIT_FAILURE);
}
