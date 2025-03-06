/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:25:42 by miguel-f          #+#    #+#             */
/*   Updated: 2025/03/06 15:06:48 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Muestra mensajes de error cuando algo sale mal
 * Por ahora solo maneja el error de número incorrecto de argumentos
 * Termina el programa después de mostrar el mensaje
 */
void	handle_error_exit(int exit_code)
{
	if (exit_code == 1)
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit(exit_code);
}

/*
 * Abre archivos de forma segura
 * Si mode es 0: Abre para lectura (archivos de entrada)
 * Si mode es 1: Crea o sobrescribe el archivo (archivos de salida)
 * Si hay algún error (ej: archivo no existe), muestra el error y termina
 */
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

/*
 * Libera la memoria de un array de strings
 * Es necesario liberar cada string y luego el array completo
 * para evitar pérdidas de memoria
 */
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

/*
 * Busca una variable de entorno y obtiene su valor
 * Ejemplo: Si tienes una variable "USER=miguel"
 * Al buscar "USER" te devuelve "miguel"
 * 
 * Se usa principalmente para encontrar PATH
 */
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

/*
 * Encuentra la ruta completa de un comando
 * 
 * 1. Busca la variable PATH en el entorno
 * 2. Divide PATH en diferentes directorios
 * 3. Busca el comando en cada directorio
 * 4. Devuelve la primera ruta donde encuentra el comando
 * 
 * Ejemplo: Si buscas "ls", puede devolver "/bin/ls"
 * 
 * Si no encuentra el comando o no se puede ejecutar, devuelve NULL
 */
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
