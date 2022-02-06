/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:04:59 by chajax            #+#    #+#             */
/*   Updated: 2022/02/06 21:59:03 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int	f1;
	int	f2;
	t_data	*data; /// ATTENTION LE MAKEFILE RELINK

	if (ac != 5 || !env)
		return (EXIT_FAILURE);
	f1 = open(av[1], O_RDONLY);
	f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0)
		perror(av[1]);
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (-1);
	data->av = av;
	data->envp = env;
	pipex(f1, f2, data);
	free_fct(data);
	free(data);
}

void	pipex(int f1, int f2, t_data *data)
{
	int		end[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	if(pipe(end) < 0)
	{
		perror("Error with the pipe creation");
		return ;
	}
	append_path(data);
	child1 = fork();
	if (child1 < 0)
		return (perror("Child 1 fork"));
	if (child1 == 0)
		child1_process(f1, end[1], data);
	close(end[1]);
	if (child1)
		child2 = fork();
	if (child2 < 0)
		return (perror("Child 2 fork"));
	if (child2 == 0)
		child2_process(f2, end[0], data);
	close(end[0]);
	waitpid(child1, &status, WNOHANG);
	waitpid(child2, &status, WNOHANG);
}
