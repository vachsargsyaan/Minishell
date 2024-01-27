/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:48:21 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/27 15:52:44 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_backup(t_init *init)
{
	init->stdin_backup = dup(STDIN_FILENO);
	if (init->stdin_backup == -1)
		perror("minishell");
	init->stdout_backup = dup(STDOUT_FILENO);
	if (init->stdout_backup == -1)
		perror("minishell");
}

void	handle_dollar(int exit_status, t_env *env)
{
	t_env	*tmp;
	char	*status;

	tmp = env;
	if (g_exit_status_ == -111)
		status = ft_strdup("1");
	else
		status = ft_itoa(exit_status);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "$?"))
		{
			free(tmp->data);
			tmp->data = ft_strdup(status);
			break ;
		}
		tmp = tmp->next;
	}
	if (g_exit_status_ != -111)
		g_exit_status_ = 0;
	free(status);
}

int	ft_onlyspaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
	}
	return (0);
}

void static	while_loop(t_init *init, t_env *env, char *str)
{
	save_backup(init);
	call_signals(1);
	str = readline("minishell$ ");
	if (!str)
	{
		ft_dprintf(2, "exit\n");
		if (g_exit_status_ == 130)
			exit (1);
		exit (init->exit_status);
	}
	if (ft_onlyspaces(str))
	{
		lex(init, &str, env);
		if (init->pars)
		{
			init->exit_status = check_ast(init, init->pars, env);
			init->hd->i = 0;
			destroy_init(init);
		}
		handle_dollar(init->exit_status, env);
		init->exit_status = 0;
		add_history(str);
	}
	free(str);
}

int	main(int argc, char **argv, char **env)
{
	t_init	parser;
	char	*str;
	t_env	*my_env;

	my_env = NULL;
	str = NULL;
	parser.flag = 1;
	parser = init(argc, argv, env);
	my_env = env_init(env, my_env);
	rl_catch_signals = 0;
	if (argc == 1 && argv)
	{
		init_hd(&parser.hd);
		printf_minishell();
		while (1)
			while_loop(&parser, my_env, str);
	}
	return (0);
}
