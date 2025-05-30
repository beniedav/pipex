/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:44:49 by badou             #+#    #+#             */
/*   Updated: 2025/05/30 20:22:07 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_input_fds(t_pipex *pipex, char **av)
{
	pipex->infile = av[1];
	pipex->infile_fd = open(av[1], O_RDONLY);
	if (pipex->infile_fd < 0)
	{
		perror(pipex->infile);
		if (errno == EACCES)
			pipex->permission_denied = 1;
	}
	pipex->outfile = av[4];
	pipex->outfile_fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->outfile_fd < 0)
	{
		perror(pipex->outfile);
		if (errno == EACCES)
			pipex->permission_denied = 1;
	}
	return ;
}

void	init_input_cmds(t_pipex *pipex, char **av, char **envp)
{
	pipex->cmds1 = ft_split(av[2], ' ');
	if (!pipex->cmds1)
	{
		cleanup(pipex);
		custom_exit("ft_split: malloc failed", 1);
	}
	pipex->cmds2 = ft_split(av[3], ' ');
	if (!pipex->cmds2)
	{
		free_arr(pipex->cmds1);
		cleanup(pipex);
		custom_exit("ft_split: malloc failed", 1);
	}
	pipex->cmd_paths = get_path_var(envp);
	if (!pipex->cmd_paths)
	{
		write(2, pipex->cmds1[0], ft_strlen(pipex->cmds1[0]));
		write(2, ": command not found\n", 21);
		cleanup(pipex);
		exit(0);
	}
	return ;
}

void	init_cmds(t_pipex *pipex)
{
	char	*path;

	path = find_command_path(pipex->cmd_paths, pipex->cmds1[0]);
	if (!path)
	{
		if (pipex->cmds1[0])
			write(2, pipex->cmds1[0], ft_strlen(pipex->cmds1[0]));
		write(2, ": command not found\n", 21);
	}
	free(pipex->cmds1[0]);
	pipex->cmds1[0] = path;
	path = find_command_path(pipex->cmd_paths, pipex->cmds2[0]);
	if (!path)
	{
		if (pipex->cmds2[0])
			write(2, pipex->cmds2[0], ft_strlen(pipex->cmds2[0]));
		write(2, ": command not found\n", 21);
	}
	free(pipex->cmds2[0]);
	pipex->cmds2[0] = path;
	return ;
}
