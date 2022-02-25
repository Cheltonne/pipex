/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <chajax@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:37:52 by chajax            #+#    #+#             */
/*   Updated: 2022/02/25 14:53:54 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	empty_and_destroy_pipe(t_data *data)
{
	close(data->end[1]);
	transfer(data->end[0], data->tmp_fw);
	close(data->end[0]);
}

void	data_init(t_data *data, char **av, char **env)
{
	data->here_doc = 0;
	data->av = av;
	data->envp = env;
	data->cmd = 0;
	data->child1 = 0;
	data->child2 = 0;
}

void	fork_wrapper(pid_t *child)
{
	*child = fork();
	if (*child < 0)
		(perror("Fork"));
}

void	middle_cmd(t_data *data)
{
	data->cmd++;
	if (data->child1 > 0)
	{
		empty_and_destroy_pipe(data);
		open_pipe(data);
		fork_wrapper(&data->mid_child);
	}
	if (data->mid_child == 0)
		mid_process(data->end, data);
	unlink(".tmp");
	close(data->tmp_fw);
	close(data->tmp_fr);
	data->tmp_fw = open(".tmp", O_APPEND | O_RDWR | O_TRUNC | O_CREAT, 0777);
	data->tmp_fr = open(".tmp", O_RDONLY);
}
