/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:25:16 by miguel-f          #+#    #+#             */
/*   Updated: 2025/03/06 15:06:38 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Ejecuta un comando del sistema
 * Ejemplo: Si recibe "ls -l", lo divide en partes y lo ejecuta
 * Si el comando no existe o no se puede ejecutar, termina con error
 */
void	execute_command(char *command, char **env)
{
	char	**command_args;
	char	*command_path;

	command_args = ft_split(command, ' ');
	command_path = find_command_path(command_args[0], env);
	if (!command_path || access(command_path, X_OK) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(command_args[0], 2);
		free_string_array(command_args);
		if (command_path)
			free(command_path);
		exit(127);
	}
	if (execve(command_path, command_args, env) == -1)
	{
		free_string_array(command_args);
		free(command_path);
		exit(127);
	}
}

/*
 * Proceso hijo: maneja el primer comando del pipe
 * 1. Abre el archivo de entrada y lo conecta a la entrada estándar
 * 2. Conecta la salida al pipe
 * 3. Ejecuta el primer comando
 * 
 * Ejemplo: En "< entrada.txt ls | wc > salida.txt"
 * Este proceso maneja el "ls"
 */
void	child_process(char **argv, int *pipe_fd, char **env)
{
	int	input_fd;

	input_fd = open_file_handler(argv[1], 0);
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_command(argv[2], env);
}

/*
 * Proceso padre: maneja el segundo comando del pipe
 * 1. Abre el archivo de salida
 * 2. Lee del pipe lo que escribió el hijo
 * 3. Ejecuta el segundo comando y escribe el resultado en el archivo
 * 
 * Ejemplo: En "< entrada.txt ls | wc > salida.txt"
 * Este proceso maneja el "wc"
 */
void	parent_process(char **argv, int *pipe_fd, char **env)
{
	int	output_fd;

	output_fd = open_file_handler(argv[4], 1);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_command(argv[3], env);
}

/*
 * Función principal que simula el comportamiento de un pipe en shell
 * 
 * Uso: ./pipex archivo1 comando1 comando2 archivo2
 * Equivale a: < archivo1 comando1 | comando2 > archivo2
 * 
 * Ejemplo: ./pipex entrada.txt "ls -l" "wc -l" salida.txt
 * Equivale a: < entrada.txt ls -l | wc -l > salida.txt
 */
int	main(int argc, char **argv, char **env)
{
	int		pipe_fd[2];
	pid_t	child_pid;
	int		status;

	if (argc != 5)
		handle_error_exit(1);
	if (pipe(pipe_fd) == -1)
		exit(1);
	child_pid = fork();
	if (child_pid == -1)
		exit((close(pipe_fd[0]),close(pipe_fd[1]), 1));
	if (child_pid == 0)
		child_process(argv, pipe_fd, env);
	else
	{
		parent_process(argv, pipe_fd, env);
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (127);
}
