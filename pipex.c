/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:14:51 by badou             #+#    #+#             */
/*   Updated: 2025/05/25 18:12:40 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_and_exit(char *string)
{
	ft_printf("Error\n");
	if (string)
		ft_printf("%s\n", string);
	else
		ft_printf("%s\n", strerror(errno));
	exit(1);
}

void free_arr(char **arr)
{
    int i = 0;
    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

char	**get_path_var(char **envp)
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
	if (!split_path)
		error_and_exit(NULL);
	return (split_path);
}

char	*find_command_path(char **paths, char *cmd)
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
			return (full_path); // Found executable path
		free(full_path);
		i++;
	}
	return (NULL); // Not found
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		error_and_exit("Expected 4 arguments");
	pipex.infile = av[1];
	pipex.infile_fd = open(av[1], O_RDONLY);
	if (pipex.infile_fd < 0)
		error_and_exit(NULL);
	pipex.outfile = av[4];
	pipex.outfile_fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex.outfile_fd < 0)
		error_and_exit(NULL);
	pipex.cmd_paths = get_path_var(envp);
	pipex.cmds1 = ft_split(av[2], ' ');
	if (!pipex.cmds1)
		error_and_exit(NULL);
	pipex.cmds2 = ft_split(av[3], ' ');
	if (!pipex.cmds2)
		error_and_exit(NULL);
	ft_printf("All is good so far: infile and fd, outfile and fd, cmds, cmdpath init\n");
	char* full_pathcmd1;
	char* full_pathcmd2;

	full_pathcmd1 = find_command_path(pipex.cmd_paths, pipex.cmds1[0]);
	if (!full_pathcmd1)
	{
		free_arr(pipex.cmd_paths);
		free_arr(pipex.cmds1);
		free_arr(pipex.cmds2);
		error_and_exit("Command not found");
	}
	full_pathcmd2 = find_command_path(pipex.cmd_paths, pipex.cmds2[0]);
	if (!full_pathcmd2)
	{
		free(full_pathcmd1);
		free_arr(pipex.cmd_paths);
		free_arr(pipex.cmds1);
		free_arr(pipex.cmds2);
		error_and_exit("Command not found");
	}
	ft_printf("Still good, commmands were found in their path\n");
	free_arr(pipex.cmd_paths);
	free_arr(pipex.cmds1);
	free_arr(pipex.cmds2);
	free(full_pathcmd1);
	free(full_pathcmd2);

	return (0);
}
