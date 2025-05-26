/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:14:51 by badou             #+#    #+#             */
/*   Updated: 2025/05/26 16:54:27 by badou            ###   ########.fr       */
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
	exec_processes(&pipex, envp);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	cleanup(&pipex);
	return (0);
}
