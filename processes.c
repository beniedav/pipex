/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:40:19 by badou             #+#    #+#             */
/*   Updated: 2025/05/26 16:48:53 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	call_child_1(t_pipex *pipex, char **envp)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		error_and_exit("fork"); // cleanup
	if (pipex->pid1 == 0)       // CHILD 1
	{
		// Redirect stdin from infile
		if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
			error_and_exit("dup2 failed for stdin");
		// Redirect stdout to pipe write end
		if (dup2(pipex->pipefd[1], STDOUT_FILENO) == -1)
			error_and_exit("dup2");
		// if (close unused fds
		if (close(pipex->pipefd[0]) == -1) // don’t read from pipe
			perror("Close");
		if (close(pipex->pipefd[1]) == -1) // already duped
			perror("Close");
		if (close(pipex->infile_fd) == -1)
			perror("Close");
		if (close(pipex->outfile_fd) == -1)
			perror("Close");
		// execve
		execve(pipex->cmds1[0], pipex->cmds1, envp);
		error_and_exit("Command1 execve failed");
	}
	return ;
}

static void	call_child_2(t_pipex *pipex, char **envp)
{
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		error_and_exit("fork");
	if (pipex->pid2 == 0) // CHILD 2
	{
		// Redirect stdin from pipe read end
		if (dup2(pipex->pipefd[0], STDIN_FILENO) == -1)
			error_and_exit("dup2 fail");
		// Redirect stdout to oufile
		if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
			error_and_exit("dup2 fail");
		// if (close unused fds
		if (close(pipex->pipefd[1]) == -1) // don’t read from pipe
			perror("Close");
		if (close(pipex->pipefd[0]) == -1) // already duped
			perror("Close");
		if (close(pipex->infile_fd) == -1)
			perror("Close");
		if (close(pipex->outfile_fd) == -1)
			perror("Close");
		// execve
		execve(pipex->cmds2[0], pipex->cmds2, envp);
		error_and_exit("Command2 execve failed");
	}
	return ;
}

void	exec_processes(t_pipex *pipex, char **envp)
{
	if (pipe(pipex->pipefd) == -1)
		error_and_exit("Pipe"); // free arrays of the struct first.
	call_child_1(pipex, envp);
	call_child_2(pipex, envp);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
}
