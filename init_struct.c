/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:44:49 by badou             #+#    #+#             */
/*   Updated: 2025/05/26 17:40:35 by badou            ###   ########.fr       */
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
		error_and_exit("PATH not found in envp", 1);//PATH not found
	split_path = ft_split(unsplit_path, ':');
		error_and_exit(NULL, 1);//Split error
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
		full_path = ft_strjoin(tmp, cmd);//could protect this as well
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static void	init_cmds(t_pipex *pipex)//This is perfect
{
	char*	path;

	path = find_command_path(pipex->cmd_paths, pipex->cmds1[0]);
	if (!path)
	{
		write (2, pipex->cmds1[0], ft_strlen(pipex->cmds1[0]));
		write (2, ": command not found\n", 21);
		free_arr(pipex->cmd_paths);
		free_arr(pipex->cmds1);
		free_arr(pipex->cmds2);
		exit(0);
	}
	free(pipex->cmds1[0]);
	pipex->cmds1[0] = path;
	path = find_command_path(pipex->cmd_paths, pipex->cmds2[0]);
	if (!path)
	{
		write (2, pipex->cmds2[0], ft_strlen(pipex->cmds2[0]));
		write (2, ": command not found\n", 21);
		free_arr(pipex->cmd_paths);
		free_arr(pipex->cmds1);
		free_arr(pipex->cmds2);
		exit(127);
	}
	free(pipex->cmds2[0]);
	pipex->cmds2[0] = path;
	return ;
}

static void	init_input(t_pipex *pipex, char **av, char **envp)
{
	pipex->infile = av[1];
	pipex->infile_fd = open(av[1], O_RDONLY);
	if (pipex->infile_fd < 0)
		error_and_exit(NULL, 1);
	pipex->outfile = av[4];
	pipex->outfile_fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->outfile_fd < 0)
		error_and_exit("outfile", 1);//OK but free stuff
	pipex->cmd_paths = get_path_var(envp);//fails handled in the function
	pipex->cmds1 = ft_split(av[2], ' ');
	if (!pipex->cmds1)
		error_and_exit(NULL, 1);//Split error. custom error
	pipex->cmds2 = ft_split(av[3], ' ');
	if (!pipex->cmds2)
		error_and_exit(NULL, 1);//Split error. custom error
	return ;
}

void	init_struct(t_pipex *pipex, char **av, char **envp)
{
	init_input(pipex, av, envp);
	init_cmds(pipex);
	return ;
}
