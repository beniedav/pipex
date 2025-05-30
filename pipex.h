/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:11:50 by badou             #+#    #+#             */
/*   Updated: 2025/05/27 18:24:04 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "Libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	int		infile_fd;
	int		outfile_fd;
	char	**cmd_paths;
	char	**cmds1;
	char	**cmds2;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int	permission_denied;
}			t_pipex;

// init	struct helper
void		init_input_fds(t_pipex *pipex, char **av);
void		init_input_cmds(t_pipex *pipex, char **av, char **envp);
void		init_cmds(t_pipex *pipex);

// init struct
void		init_struct(t_pipex *pipex, char **av, char **envp);

// processes
void		exec_processes(t_pipex *pipex, char **envp);

// error and free
void		error_and_exit(char *string, int exit);
void		custom_exit(char *string, int exit_code);
void		free_arr(char **arr);
void		close_fds(t_pipex *pipex);
void		cleanup(t_pipex *pipex);
void		safe_close(int fd);

#endif
