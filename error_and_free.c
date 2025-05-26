/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:01:25 by badou             #+#    #+#             */
/*   Updated: 2025/05/26 17:39:34 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_and_exit(char *string)
{
	perror(string);
	exit(1);
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

void	cleanup(t_pipex* pipex)
{
	free_arr(pipex->cmd_paths);
	free_arr(pipex->cmds1);
	free_arr(pipex->cmds2);
	close(pipex->outfile_fd);
	close(pipex->infile_fd);
}
