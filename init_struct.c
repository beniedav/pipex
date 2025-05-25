/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:44:49 by badou             #+#    #+#             */
/*   Updated: 2025/05/25 19:03:03 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_path_var(char **envp)
{
	char	*unsplit_path;
	char	**split_path;
	int		i;

	unsplit_path = NULL;
	split_path = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			unsplit_path = (envp[i] + 5);
			break ;
		}
		i++;
	}
	if (!unsplit_path)
		error_and_exit("PATH not found in envp");
	split_path = ft_split(unsplit_path, ':');
	return (split_path);
}

static char	*find_command_path(char **paths, char *cmd)
{
	int		i;
	char	*full_path;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static void	init_cmds(t_pipex *pipex)
{
	pipex->cmds1[0] = find_command_path(pipex->cmd_paths, pipex->cmds1[0]);
	if (!pipex->cmds1[0])
	{
		free_arr(pipex->cmd_paths);
		free_arr(pipex->cmds1);
		free_arr(pipex->cmds2);
		error_and_exit("Command not found");
	}
	pipex->cmds2[0] = find_command_path(pipex->cmd_paths, pipex->cmds2[0]);
	if (!pipex->cmds2[0])
	{
		free_arr(pipex->cmd_paths);
		free_arr(pipex->cmds1);
		free_arr(pipex->cmds2);
		error_and_exit("Command not found");
	}
	return ;
}

static void	init_input(t_pipex *pipex, char **av, char **envp)
{
	pipex->infile = av[1];
	pipex->infile_fd = open(av[1], O_RDONLY);
	if (pipex->infile_fd < 0)
		error_and_exit(NULL);
	pipex->outfile = av[4];
	pipex->outfile_fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->outfile_fd < 0)
		error_and_exit(NULL);
	pipex->cmd_paths = get_path_var(envp);
	if (!pipex->cmd_paths)
		error_and_exit(NULL);
	pipex->cmds1 = ft_split(av[2], ' ');
	if (!pipex->cmds1)
		error_and_exit(NULL);
	pipex->cmds2 = ft_split(av[3], ' ');
	if (!pipex->cmds2)
		error_and_exit(NULL);
	return ;
}

void	init_struct(t_pipex *pipex, char **av, char **envp)
{
	init_input(pipex, av, envp);
	init_cmds(pipex);
	return ;
}
