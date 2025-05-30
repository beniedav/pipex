/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:01:25 by badou             #+#    #+#             */
/*   Updated: 2025/05/30 19:57:26 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_and_exit(char *string, int exit_code)
{
	perror(string);
	exit(exit_code);
}

void	custom_exit(char *string, int exit_code)
{
	write(2, string, ft_strlen(string));
	exit(exit_code);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	safe_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	cleanup(t_pipex *pipex)
{
	safe_close(pipex->infile_fd);
	safe_close(pipex->outfile_fd);
	safe_close(pipex->pipefd[0]);
	safe_close(pipex->pipefd[1]);
	free_arr(pipex->cmd_paths);
	free_arr(pipex->cmds1);
	free_arr(pipex->cmds2);
}
