/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:04:59 by chajax            #+#    #+#             */
/*   Updated: 2022/02/25 15:02:41 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_dir/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	if (ac < 5 || env[0] == NULL)
		return (EXIT_FAILURE);
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		exit_error(data);
	data_init(data, av, env);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		here_doc(data, av[2], &data->files[0]);
		data->files[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else
	{
		data->files[0] = open(av[1], O_RDONLY);
		data->files[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	if (data->files[0] < 0)
		perror(av[1]);
	if (data->files[1] < 0)
		perror(av[ac]);
	pipex(data->files, data, ac);
	free_fct(data);
	free(data);
}

void	open_pipe(t_data *data)
{
	if (pipe(data->end) < 0)
		pipe_error(data);
}

void	transfer(int fd1, int fd2)
{
	char	*buf;

	while (1)
	{
		buf = get_next_line(fd1);
		if (buf == NULL)
			break ;
		ft_putstr_fd(buf, fd2);
		free(buf);
	}
	free(buf);
}

void	pipex(int *files, t_data *data, int ac)
{
	int		status;

	open_pipe(data);
	append_path(data);
	fork_wrapper(&data->child1);
	data->cmd += 2;
	if (data->child1 == 0)
		first_and_last(files, data->end, data);
	data->tmp_fw = open(".tmp", O_APPEND | O_RDWR | O_TRUNC | O_CREAT, 0777);
	data->tmp_fr = open(".tmp", O_RDONLY);
	while (data->cmd < ac - 3)
		middle_cmd(data);
	empty_and_destroy_pipe(data);
	if (data-> child1 > 0)
		fork_wrapper(&data->child2);
	data->cmd++;
	if (data->child2 == 0)
		first_and_last(files, data->end, data);
	waitpid(data->child1, &status, WNOHANG);
	waitpid(data->mid_child, &status, 0);
	waitpid(data->child2, &status, 0);
	close_fds(data);
}
