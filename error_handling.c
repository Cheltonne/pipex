/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:16:34 by chajax            #+#    #+#             */
/*   Updated: 2022/02/06 21:59:49 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_404(char *cmd)
{
	char *message;

	message = ft_strjoin(cmd, ": command not found\n");
	ft_putstr_fd(message, 2);
	free(message);
}
