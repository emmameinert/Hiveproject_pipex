/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:01:20 by emeinert          #+#    #+#             */
/*   Updated: 2023/11/08 16:02:31 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	freemystuff(char **str)
{
	int		i;
	char	*input;

	i = 0;
	if (str == NULL)
		exit(1);
	while (str[i])
	{
		input = str[i];
		free(input);
		i++;
	}
	free(str);
}

void	free_my_struct(t_pipex *pipex)
{
	free(pipex->path2);
	free(pipex->path1);
}

void	close_my_stuff(t_pipex *pipex)
{
	close(pipex->file1);
	close(pipex->file2);
	close(pipex->end[0]);
	close(pipex->end[1]);
}

void	errorhandling(int number)
{
	if (number == 1)
	{
		perror("error");
		exit(1);
	}
	if (number == 2)
		perror("error");
}

void	check_input(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_printf("error: Unexpected number of arguments \n");
		exit (0);
	}
}
