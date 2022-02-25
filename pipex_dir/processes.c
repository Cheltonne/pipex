/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:26:05 by chajax            #+#    #+#             */
/*   Updated: 2022/02/25 14:59:24 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_dir/pipex.h"

char	*try_cmd(t_data *data)
{
	int		i;
	char	*tmp;
	char	*cmd;

	i = -1;
	if (data->cmd_args[0] == NULL)
	{	
		ft_putstr_fd("Command ' ' not found\n", 2);
		return (NULL);
	}
	while (data->possible_paths[++i])
	{
		tmp = ft_strjoin(data->possible_paths[i], "/");
		cmd = ft_strjoin(tmp, data->cmd_args[0]);
		free(tmp);
		if (!access(cmd, X_OK))
			return (cmd);
		free(cmd);
	}
	return (NULL);
}

void	first_and_last(int *files, int *end, t_data *data)
{
	char	*cmd;

	if (data->cmd == 2 || (data->cmd == 3 && data->here_doc))
	{
		close(data->end[0]);
		if (dup2(files[0], STDIN_FILENO) < 0)
			exit_error(data);
		if (dup2(end[1], STDOUT_FILENO) < 0)
			exit_error(data);
		close(data->end[1]);
	}
	else
	{
		if (dup2(data->tmp_fr, STDIN_FILENO))
			exit_error(data);
		if (dup2(files[1], STDOUT_FILENO) < 0)
			exit_error(data);
	}
	data->cmd_args = ft_split(data->av[data->cmd], ' ');
	cmd = try_cmd(data);
	execve(cmd, data->cmd_args, data->envp);
	execve_error(data, cmd);
}

void	mid_process(int *end, t_data *data)
{
	char	*cmd;

	close(data->end[0]);
	if (dup2(data->tmp_fr, STDIN_FILENO) < 0)
		exit_error(data);
	if (dup2(end[1], STDOUT_FILENO) < 0)
		exit_error(data);
	data->cmd_args = ft_split(data->av[data->cmd], ' ');
	cmd = try_cmd(data);
	execve(cmd, data->cmd_args, data->envp);
	execve_error(data, cmd);
}
