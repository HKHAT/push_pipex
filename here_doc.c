/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:37:36 by elchakir          #+#    #+#             */
/*   Updated: 2024/01/13 04:19:17 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	herdoc(char *limiter, int *fd)
{
	char	*line;

	close(fd[0]);
	write(1, "heredoc> ", 9);
	while (gnl(&line) > 0)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			|| line[0] == '\0')
			exit(EXIT_SUCCESS);
		write(fd[1], line, ft_strlen(line));
		write(1, "heredoc> ", 9);
	}
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

void	here_doc(char *limiter, int ac)
{
	int		fd[2];
	pid_t	pid;

	if (ac < 6)
		error_arg();
	if (pipe(fd) == -1)
		error_p("here_doc Pipe", 1);
	pid = fork();
	if (pid == -1)
		error_p("here_doc fork", 1);
	if (pid == 0)
	{
		herdoc(limiter, fd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
	}
}
