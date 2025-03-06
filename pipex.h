/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:53:03 by miguel-f          #+#    #+#             */
/*   Updated: 2025/03/06 15:06:43 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "libft/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

/* Declaración de funciones */

/* Abre archivos para lectura o escritura
 * @param filepath: Ruta del archivo que queremos abrir
 * @param mode: 0 para leer, 1 para escribir (creará el archivo si no existe)
 * @return: Identificador del archivo abierto
 */
int		open_file_handler(char *filepath, int mode);

/* Busca una variable de entorno y devuelve su valor
 * Por ejemplo: busca "PATH" y devuelve su contenido
 * @param env_name: Nombre de la variable que buscamos (ej: "PATH")
 * @param env: Lista de variables de entorno
 * @return: Valor de la variable o NULL si no la encuentra
 */
char	*get_env_value(char *env_name, char **env);

/* Busca la ruta completa de un comando (ej: de "ls" obtiene "/bin/ls")
 * @param command: Nombre del comando a buscar
 * @param env: Lista de variables de entorno
 * @return: Ruta completa del comando o NULL si no lo encuentra
 */
char	*find_command_path(char *command, char **env);

/* Libera la memoria de un array de strings
 * @param array: Array de strings a liberar
 */
void	free_string_array(char **array);

/* Muestra mensaje de error y termina el programa
 * @param exit_code: Código de error para terminar el programa
 */
void	handle_error_exit(int exit_code);

#endif