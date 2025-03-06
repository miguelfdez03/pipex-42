/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:25:42 by miguel-f          #+#    #+#             */
/*   Updated: 2025/03/04 19:17:58 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error_exit(int exit_code)
{
	if (exit_code == 1)
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit(exit_code);
}

int	open_file_handler(char *filepath, int mode)
{
	int	file_fd;

	if (mode == 0)
		file_fd = open(filepath, O_RDONLY);
	if (mode == 1)
		file_fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd == -1)
	{
		perror(filepath);
		exit(1);
	}
	return (file_fd);
}

void	free_string_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*get_env_value(char *env_name, char **env)
{
	int		i;
	int		name_len;
	char	*env_var_name;

	i = 0;
	while (env[i])
	{
		name_len = 0;
		while (env[i][name_len] && env[i][name_len] != '=')
			name_len++;
		env_var_name = ft_substr(env[i], 0, name_len);
		if (ft_strcmp(env_var_name, env_name) == 0)
		{
			free(env_var_name);
			return (env[i] + name_len + 1);
		}
		free(env_var_name);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *command, char **env)
{
	int		i;
	char	*executable_path;
	char	**path_directories;
	char	*directory_with_slash;
	char	**command_parts;

	if (!command || !env || !get_env_value("PATH", env))
		return (NULL);
	path_directories = ft_split(get_env_value("PATH", env), ':');
	command_parts = ft_split(command, ' ');
	i = -1;
	while (path_directories && path_directories[++i])
	{
		directory_with_slash = ft_strjoin(path_directories[i], "/");
		executable_path = ft_strjoin(directory_with_slash, command_parts[0]);
		free(directory_with_slash);
		if (access(executable_path, F_OK | X_OK) == 0)
			break ;
		free(executable_path);
		executable_path = NULL;
	}
	free_string_array(path_directories);
	free_string_array(command_parts);
	return (executable_path);
}
