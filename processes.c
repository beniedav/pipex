/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:40:19 by badou             #+#    #+#             */
/*   Updated: 2025/05/30 20:25:11 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	call_child_1_helper(t_pipex *pipex)
{
	int	null_fd;

	if (pipex->infile_fd >= 0)
		dup2(pipex->infile_fd, STDIN_FILENO);
	else
	{
		null_fd = open("/dev/null", O_RDONLY);
		dup2(null_fd, STDIN_FILENO);
		safe_close(null_fd);
	}
	dup2(pipex->pipefd[1], STDOUT_FILENO);
	safe_close(pipex->pipefd[0]);
	safe_close(pipex->pipefd[1]);
	safe_close(pipex->infile_fd);
	safe_close(pipex->outfile_fd);
	return ;
}

static void	call_child_1(t_pipex *pipex, char **envp)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		error_and_exit("fork", 1);
	if (pipex->pid1 == 0)
	{
		call_child_1_helper(pipex);
		if (pipex->cmds1[0])
			execve(pipex->cmds1[0], pipex->cmds1, envp);
		cleanup(pipex);
		exit(127);
	}
	return ;
}

static void	call_child_2_helper(t_pipex *pipex)
{
	int	null_fd;

	if (pipex->outfile_fd >= 0)
		dup2(pipex->outfile_fd, STDOUT_FILENO);
	else
	{
		if (!pipex->permission_denied)
			perror(pipex->outfile);
		cleanup(pipex);
		exit(1);
		null_fd = open("/dev/null", O_WRONLY);
		dup2(null_fd, STDOUT_FILENO);
		safe_close(null_fd);
	}
	dup2(pipex->pipefd[0], STDIN_FILENO);
	dup2(pipex->outfile_fd, STDOUT_FILENO);
	safe_close(pipex->pipefd[1]);
	safe_close(pipex->pipefd[0]);
	safe_close(pipex->infile_fd);
	safe_close(pipex->outfile_fd);
	return ;
}

static void	call_child_2(t_pipex *pipex, char **envp)
{
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		error_and_exit("fork", 1);
	if (pipex->pid2 == 0)
	{
		call_child_2_helper(pipex);
		if (pipex->cmds2[0])
			execve(pipex->cmds2[0], pipex->cmds2, envp);
		cleanup(pipex);
		exit(127);
	}
	return ;
}

void	exec_processes(t_pipex *pipex, char **envp)
{
	int	status1;
	int	status2;

	if (pipe(pipex->pipefd) == -1)
	{
		cleanup(pipex);
		error_and_exit("pipe", 1);
	}
	call_child_1(pipex, envp);
	call_child_2(pipex, envp);
	safe_close(pipex->pipefd[0]);
	safe_close(pipex->pipefd[1]);
	waitpid(pipex->pid1, &status1, 0);
	waitpid(pipex->pid2, &status2, 0);
	cleanup(pipex);
	if (pipex->permission_denied == 1)
		exit(1);
	if (WIFEXITED(status2))
		exit(WEXITSTATUS(status2));
	else
		exit(1);
	return ;
}
