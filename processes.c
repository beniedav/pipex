/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:40:19 by badou             #+#    #+#             */
/*   Updated: 2025/05/27 18:29:34 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	call_child_1_helper(t_pipex *pipex)
{
	if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
		error_and_exit(pipex->infile, 1);
	if (dup2(pipex->pipefd[1], STDOUT_FILENO) == -1)
		error_and_exit("pipe", 1);
	if (close(pipex->pipefd[0]) == -1)
		error_and_exit("pipe", 1);
	if (close(pipex->pipefd[1]) == -1)
		error_and_exit("pipe", 1);
	if (close(pipex->infile_fd) == -1)
		error_and_exit(pipex->infile, 1);
	if (close(pipex->outfile_fd) == -1)
		error_and_exit(pipex->outfile, 1);
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
		execve(pipex->cmds1[0], pipex->cmds1, envp);
		write(2, pipex->cmds2[0], ft_strlen(pipex->cmds2[0]));
		perror(NULL);
		free_arr(pipex->cmd_paths);
		free_arr(pipex->cmds1);
		free_arr(pipex->cmds2);
		exit(1);
	}
	return ;
}

static void	call_child_2_helper(t_pipex *pipex)
{
	if (dup2(pipex->pipefd[0], STDIN_FILENO) == -1)
		error_and_exit("pipe", 1);
	if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
		error_and_exit(pipex->outfile, 1);
	if (close(pipex->pipefd[1]) == -1)
		error_and_exit("pipe", 1);
	if (close(pipex->pipefd[0]) == -1)
		error_and_exit("pipe", 1);
	if (close(pipex->infile_fd) == -1)
		error_and_exit(pipex->infile, 1);
	if (close(pipex->outfile_fd) == -1)
		error_and_exit(pipex->outfile, 1);
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
		execve(pipex->cmds2[0], pipex->cmds2, envp);
		write(2, pipex->cmds2[0], ft_strlen(pipex->cmds2[0]));
		perror(NULL);
		free_arr(pipex->cmd_paths);
		free_arr(pipex->cmds1);
		free_arr(pipex->cmds2);
		exit(1);
	}
	return ;
}

void	exec_processes(t_pipex *pipex, char **envp)
{
	if (pipe(pipex->pipefd) == -1)
	{
		cleanup(pipex);
		error_and_exit("pipe", 1);
	}
	call_child_1(pipex, envp);
	call_child_2(pipex, envp);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	return ;
}
