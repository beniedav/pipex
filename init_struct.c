/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:18:47 by badou             #+#    #+#             */
/*   Updated: 2025/05/27 18:23:01 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_pipex *pipex, char **av, char **envp)
{
	init_input_fds(pipex, av);
	init_input_cmds(pipex, av, envp);
	init_cmds(pipex);
	return ;
}
