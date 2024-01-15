/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:14:10 by elchakir          #+#    #+#             */
/*   Updated: 2024/01/10 22:51:36 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*build_executable_path(char *cmd, char *path)
{
	char	*part_path;
	char	*exe;

	if (access(cmd, F_OK | X_OK) != -1)
		return (cmd);
	part_path = ft_strjoin(path, "/");
	exe = ft_strjoin(part_path, cmd);
	free(part_path);
	if (access(exe, F_OK | X_OK) == 0)
		return (exe);
	free(exe);
	return (NULL);
}

char	*find_path(char *cmd, char **ev)
{
	char	**allpaths;
	char	*exe;
	int		i;

	i = 0;
	while (ev[i])
	{
		if (ft_strnstr(ev[i], "PATH=", 5) != NULL)
			break ;
		i++;
	}
	allpaths = (char **)ft_split((ev[i] + 5), ':');
	i = 0;
	while (allpaths[i])
	{
		exe = build_executable_path(cmd, allpaths[i]);
		if (exe != NULL)
		{
			ft_clear_tab(allpaths);
			return (exe);
		}
		i++;
	}
	ft_clear_tab(allpaths);
	return (NULL);
}

void	exe(char **ev, char *av)
{
	char	**cmd;
	char	*cmd_exe;

	cmd = (char **)ft_split(av, ' ');
	cmd_exe = find_path(cmd[0], ev);
	if (cmd_exe == NULL)
	{
		perror("pipex: command not found");
		ft_putendl_fd(cmd[0], 2);
		ft_clear_tab(cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd_exe, cmd, ev) == -1)
	{
		perror("pipex: execution error");
		ft_putendl_fd(cmd[0], 2);
		ft_clear_tab(cmd);
		free(cmd_exe);
		exit(EXIT_FAILURE);
	}
}

void	do_pipe(char **av, char **ev, int is_last, int out_fd)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error_arg();
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (is_last)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		exe(ev, av[0]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}
