/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:04:57 by chajax            #+#    #+#             */
/*   Updated: 2022/02/25 15:04:37 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_dir/pipex.h"

void	free_and_null(char **to_free)
{
	int	i;

	if (!to_free)
		return ;
	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		to_free[i] = NULL;
		i++;
	}
	free(to_free);
}

void	free_fct(t_data *data)
{
	free_and_null(data->possible_paths);
	free_and_null(data->cmd_args);
}

void	close_fds(t_data *data)
{
	close(data->tmp_fw);
	close(data->tmp_fr);
	close(data->end[0]);
	close(data->end[1]);
	close(data->files[0]);
	close(data->files[1]);
	unlink(".tmp");
	unlink(".here_doc");
}
