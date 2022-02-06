/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:04:57 by chajax            #+#    #+#             */
/*   Updated: 2022/02/06 20:49:24 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_and_null(char **to_free)
{
	int i;

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
