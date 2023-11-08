/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:46:23 by emeinert          #+#    #+#             */
/*   Updated: 2023/11/08 16:02:29 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

char	*check_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4) != 0)
		envp++;
	return (*envp + 5);
}

char	*access_path(t_pipex *pipex, char *cmd)
{
	char	*passing;
	char	*onepart;
	int		i;

	i = -1;
	while (pipex->myarg_path[++i] != NULL)
	{
		onepart = ft_strjoin(pipex->myarg_path[i], "/");
		passing = ft_strjoin(onepart, cmd);
		if (!passing || !onepart)
			return (0);
		free(onepart);
		if (access(passing, X_OK) == 0)
			return (passing);
		else
			free(passing);
	}
	return (cmd);
}

char	*find_path(char *cmd, char **envp, t_pipex *pipex)
{
	pipex->envp_path = ft_strdup(check_path(envp));
	pipex->myarg_path = ft_split(pipex->envp_path, ':');
	if (pipex->myarg_path != NULL)
		cmd = access_path(pipex, cmd);
	free(pipex->envp_path);
	freemystuff(pipex->myarg_path);
	return (cmd);
}

void	child_process(t_pipex *pipex, char **envp)
{
	close(pipex->end[0]);
	close(pipex->file2);
	if (dup2(pipex->end[1], 1) < 0 || dup2(pipex->file1, 0) < 0)
		exit(1);
	close(pipex->file1);
	close(pipex->end[1]);
	execve(pipex->path1, pipex->first, envp);
	write(2, "zsh: command not found: ", 25);
	write(2, pipex->first[0], ft_strlen(pipex->first[0]));
	write(2, "\n", 1);
	exit(1);
}

void	child_process2(t_pipex *pipex, char **envp)
{
	close(pipex->end[1]);
	close(pipex->file1);
	if (dup2(pipex->end[0], 0) < 0 || dup2(pipex->file2, 1) < 0)
		exit(1);
	close(pipex->end[0]);
	close(pipex->file2);
	execve(pipex->path2, pipex->second, envp);
	write(2, "zsh: command not found: ", 25);
	write(2, pipex->second[0], ft_strlen(pipex->second[0]));
	write(2, "\n", 1);
	exit(1);
}
