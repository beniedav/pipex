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

	char *argv[] = {pipex.cmds1[0], pipex.cmds1[1], NULL};

	execve(pipex.cmds1[0], argv, envp);

	free_arr(pipex.cmd_paths);
	free_arr(pipex.cmds1);
	free_arr(pipex.cmds2);
	close(pipex.outfile_fd);
	close(pipex.infile_fd);
	return (0);
}
