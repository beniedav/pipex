/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:14:51 by badou             #+#    #+#             */
/*   Updated: 2025/05/25 19:01:45 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		error_and_exit("Expected 4 arguments");
		
	init_struct(&pipex, av, envp);
	ft_printf("Struct initialized successfully\n");

	if (pipe(pipex.pipefd) == -1)
    		error_and_exit("Pipe");

	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		error_and_exit("fork");
	if (pipex.pid1 == 0) // CHILD 1
	{
 	  	// Redirect stdin from infile	
		dup2(pipex.infile_fd, STDIN_FILENO);

    		// Redirect stdout to pipe write end
	  	dup2(pipex.pipefd[1], STDOUT_FILENO);

		// Close unused fds
		close(pipex.pipefd[0]); // don’t read from pipe
		close(pipex.pipefd[1]); // already duped
		close(pipex.infile_fd);
	   	close(pipex.outfile_fd);
    		// execve
		execve(pipex.cmds1[0], pipex.cmds1, envp);
		error_and_exit("Command1 execve failed");
	}
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		error_and_exit("fork");
	if (pipex.pid2 == 0) // CHILD 1
	{
 	  	// Redirect stdin from pipe read end
		dup2(pipex.pipefd[0], STDIN_FILENO);

    		// Redirect stdout to oufile 
	  	dup2(pipex.outfile_fd, STDOUT_FILENO);

		// Close unused fds
		close(pipex.pipefd[1]); // don’t read from pipe
		close(pipex.pipefd[0]); // already duped
		close(pipex.infile_fd);
	   	close(pipex.outfile_fd);
    		// execve
		execve(pipex.cmds2[0], pipex.cmds2, envp);
		error_and_exit("Command2 execve failed");
	}
	free_arr(pipex.cmd_paths);
	free_arr(pipex.cmds1);
	free_arr(pipex.cmds2);
	close(pipex.outfile_fd);
	close(pipex.infile_fd);
	return (0);
}
