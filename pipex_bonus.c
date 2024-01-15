/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 23:23:53 by elchakir          #+#    #+#             */
/*   Updated: 2024/01/15 19:24:43 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_arg(void)
{
	char	*error1;
	char	*error2;
	char	*error3;

	error1 = "\033[1;31m!! Invalid arguments.!!\n\033[0m\n";
	error2 = "\033[1;31mUsage: ./pipex infile cmd1 cmd2 ... outfile\n\033[0m\n";
	error3 = "\033[1;31mOr:./pipex here_doc lim cmd1 cmd2...outfile\n\033[0m\n";
	write(2, error1, ft_strlen(error1));
	write(2, error2, ft_strlen(error2));
	write(2, error3, ft_strlen(error3));
	exit(EXIT_FAILURE);
}

void	ft_clear_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	gnl(char **line)
{
	char	buffer[BUFFER_SIZE];
	int		i;
	int		r;
	char	c;

	i = 0;
	r = read(0, &c, 1);
	while (r > 0 && c != '\n' && c != '\0')
	{
		buffer[i++] = c;
		r = read(0, &c, 1);
	}
	buffer[i] = '\0';
	*line = buffer;
	if (r > 0 || i > 0)
		return (1);
	else
		return (r);
}

int	open_file(char **av, int ac, int *flag, int *out)
{
	int	in;
	int	i;

	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		i = 3;
		*flag = 1;
		here_doc(av[2], ac);
	}
	*out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (*flag == 0)
	{
		i = 2;
		in = open(av[1], O_RDONLY, 0777);
		*flag = 2;
	}
	else
	{
		in = open(".in", O_RDONLY | O_CREAT, 0777);
		*flag = 2;
	}
	if (in == -1 || *out == -1)
		error_p("file descriptor error !", 1);
	dup2(in, 0);
	return (close(in), i);
}

int	main(int ac, char **av, char **ev)
{
	int	out;
	int	i;
	int	flag;
	int	status;

	i = 2;
	flag = 0;
	if (ac < 5)
		error_arg();
	i = open_file(av, ac, &flag, &out);
	while (i <= ac - flag)
	{
		do_pipe(&av[i], ev, (i == ac - flag), out);
		i++;
	}
	while (wait(&status) > 0)
		;
	return (close(out), unlink(".in"), exit(status), 0);
}
