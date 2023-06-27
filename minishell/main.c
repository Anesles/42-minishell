/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:36:04 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 17:58:31 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_exit_status = 0;

void	sig_continue(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

char	**arraydup(char **old)
{
	char	**new;
	int		i;

	i = 0;
	while (old[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (old[i])
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	main(int argc, char *argv[], char **envp)
{
	t_mshell	mshell;

	if (argc != 1 || argv[1])
		perror("minishell: too many arguments");
	signal(SIGINT, &sig_continue);
	mshell.envior = arraydup(envp);
	mshell.path = get_path(mshell.envior);
	mshell.save_fd[0] = dup(0);
	mshell.save_fd[1] = dup(1);
	b_export("?=0", &mshell);
	minishell_loop(&mshell);

	return (EXIT_FAILURE);
}
