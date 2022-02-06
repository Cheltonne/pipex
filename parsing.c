/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 21:53:56 by chajax            #+#    #+#             */
/*   Updated: 2022/02/06 18:43:05 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(t_data *data)
{
	char	**envp;
	size_t	path_i;

	path_i = 0;
	envp = data->envp;
	while (ft_strncmp("PATH", data->envp[path_i], 4))
		path_i++;
	return (ft_substr(envp[path_i], 5, ft_strlen(envp[path_i]) - 5));
}

void	append_path(t_data *data)
{
	char	*env_pwd;
	char	*env_path;
	char	*complete_path;
	size_t	pwd_i;

	env_path = find_path(data);
	pwd_i = 0;
	while (ft_strncmp("PWD", data->envp[pwd_i], 3))
		pwd_i++;
	env_pwd = ft_substr(data->envp[pwd_i], 4, ft_strlen(data->envp[pwd_i]) - 4);
	complete_path = ft_strjoin(env_path, ":");
	free(env_path);
	data->tmp = ft_strjoin(complete_path, env_pwd);
	free(env_pwd);
	free(complete_path);
	data->possible_paths = ft_split(data->tmp, ':');
	free(data->tmp);
}
