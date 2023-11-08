/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:11:52 by emeinert          #+#    #+#             */
/*   Updated: 2023/11/08 16:03:30 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../sources/libft/libft.h"

# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_pipex
{
	pid_t	pid[2];
	int		file1;
	int		file2;
	int		end[2];
	char	*path1;
	char	*path2;
	char	**first;
	char	**second;
	char	*envp_path;
	char	**myarg_path;
}t_pipex;

void	check_input(int argc, char **argv);
char	*check_path(char **envp);
void	errorhandling(int number);
void	child_process(t_pipex *pipex, char **envp);
void	child_process2(t_pipex *pipex, char **envp);
void	freemystuff(char **str);
char	*find_path(char *cmd, char **envp, t_pipex *pipex);
void	free_my_struct(t_pipex *pipex);
void	close_my_stuff(t_pipex *pipex);
void	get_path(t_pipex *pipex, char **envp, char **argv);
void	first_function(int argc, char **argv, t_pipex *pipex);

#endif
