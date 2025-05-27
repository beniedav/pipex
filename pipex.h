/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:11:50 by badou             #+#    #+#             */
/*   Updated: 2025/05/26 16:49:23 by badou            ###   ########.fr       */
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
	char *infile;     // argv[1] - input file
	char *outfile;    // argv[4] - output file
	int infile_fd;    // file descriptor for infile
	int outfile_fd;   // file descriptor for outfile
	char **cmd_paths; // split PATH (used to resolve commands)
	char **cmds1;     // split argv[2] (first command and args)
	char **cmds2;     // split argv[3] (second command and args)
	int pipefd[2];    // pipe file descriptors: [0] = read, [1] = write
	pid_t pid1;       // PID of first child
	pid_t pid2;       // PID of second child
}		t_pipex;

// init struct
void	init_struct(t_pipex *pipex, char **av, char **envp);

//processes
void	exec_processes(t_pipex *pipex, char** envp);


//error and free
void	error_and_exit(char *string, int exit);
void	custom_exit(char* string, int exit_code);
void	free_arr(char **arr);
void	close_fds(t_pipex* pipex);
void	cleanup(t_pipex* pipex);


#endif
