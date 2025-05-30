/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:14:51 by badou             #+#    #+#             */
/*   Updated: 2025/05/28 18:19:35 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void pipex_init(t_pipex *pipex)
{
    if (!pipex)
        return;

    pipex->infile = NULL;
    pipex->outfile = NULL;

    pipex->infile_fd = -1;
    pipex->outfile_fd = -1;

    pipex->pipefd[0] = -1;
    pipex->pipefd[1] = -1;

    pipex->pid1 = -1;
    pipex->pid2 = -1;

    pipex->cmds1 = NULL;
    pipex->cmds2 = NULL;
    pipex->cmd_paths = NULL;
    pipex->permission_denied = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		custom_exit("Expected 4 arguments", 1);
	pipex_init(&pipex);
	init_struct(&pipex, av, envp);
	exec_processes(&pipex, envp);
	return (1);
}
