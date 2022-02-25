/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:16:34 by chajax            #+#    #+#             */
/*   Updated: 2022/02/25 15:03:24 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_dir/pipex.h"

void	exit_error(t_data *data)
{
	free_fct(data);
	free(data);
	exit(EXIT_FAILURE);
}

void	cmd_404(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	pipe_error(t_data *data)
{
	perror("Pipe creation");
	exit_error(data);
}

void	execve_error(t_data *data, char *cmd)
{
	if (!cmd || data->av[data->cmd][0] == ' ')
		cmd_404(data->cmd_args[0]);
	close(data->end[1]);
	close(data->end[0]);
	free(cmd);
	close_fds(data);
	exit_error(data);
}
