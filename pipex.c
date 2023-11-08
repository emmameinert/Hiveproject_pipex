/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:46:32 by emeinert          #+#    #+#             */
/*   Updated: 2023/11/08 16:03:17 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/pipex.h"

void	first_function(int argc, char **argv, t_pipex *pipex)
{
	pipex->file1 = open(argv[1], O_RDONLY);
	pipex->file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (access(argv[1], F_OK) != 0)
		errorhandling(2);
	else if (pipex->file2 < 0)
		errorhandling(1);
	else if (pipex->file1 < 0)
		errorhandling(2);
}

void	get_path(t_pipex *pipex, char **envp, char **argv)
{
	pipex->first = ft_split(argv[2], ' ');
	pipex->second = ft_split(argv[3], ' ');
	pipex->path1 = find_path(pipex->first[0], envp, pipex);
	pipex->path2 = find_path(pipex->second[0], envp, pipex);
}

t_pipex	*make_pipex(void)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		exit(1);
	return (pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = make_pipex();
	check_input(argc, argv);
	if (pipe(pipex->end) == -1)
		errorhandling(1);
	first_function(argc, argv, pipex);
	get_path(pipex, envp, argv);
	pipex->pid[0] = fork();
	if (pipex->pid[0] < 0)
		return (0);
	if (pipex->pid[0] == 0)
		child_process(pipex, envp);
	pipex->pid[1] = fork();
	if (pipex->pid[1] < 0)
		return (0);
	if (pipex->pid[1] == 0)
		child_process2(pipex, envp);
	close_my_stuff(pipex);
	waitpid(pipex->pid[0], NULL, 0);
	waitpid(pipex->pid[1], NULL, 0);
	free_my_struct(pipex);
	return (0);
}
