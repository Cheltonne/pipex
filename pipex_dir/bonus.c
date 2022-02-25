/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <chajax@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:26:55 by chajax            #+#    #+#             */
/*   Updated: 2022/02/24 14:29:26 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_dir/pipex.h"

void	query_user(char *limiter, int *buf_fd)
{
	char	*buf;

	while (1)
	{
		write(1, "> ", 2);
			buf = get_next_line(0);
		if (buf == NULL)
			exit (EXIT_SUCCESS);
		if (ft_strncmp(limiter, buf, ft_strlen(limiter)) == 0)
			break ;
		ft_putstr_fd(buf, *buf_fd);
		free(buf);
	}
	free(buf);
}

void	here_doc(t_data *data, char *limiter, int *f1)
{
	int		buf_fd;

	buf_fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (buf_fd < 0)
		exit(EXIT_FAILURE);
	query_user(limiter, &buf_fd);
	close(buf_fd);
	*f1 = open(".here_doc", O_RDONLY);
	data->cmd++;
	data->here_doc = 1;
	if (*f1 < 0)
	{
		unlink(".here_doc");
		exit(EXIT_FAILURE);
	}
}
