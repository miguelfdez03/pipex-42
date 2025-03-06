/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:53:03 by miguel-f          #+#    #+#             */
/*   Updated: 2025/03/04 16:51:30 by miguel-f         ###   ########.fr       */
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

int		open_file_handler(char *filepath, int mode);
char	*get_env_value(char *env_name, char **env);
char	*find_command_path(char *command, char **env);
void	free_string_array(char **array);
void	handle_error_exit(int exit_code);

#endif