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

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		status;

	if (ac != 5)
		custom_exit("Expected 4 arguments", 1);
	init_struct(&pipex, av, envp);
	exec_processes(&pipex, envp);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, &status, 0);
	cleanup(&pipex);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
