/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:48:21 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/23 18:52:19 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int argc, char **argv, char **env)
{
	t_init	parser;
	char	*str;
	t_env	*my_env;

	my_env = NULL;
	if (argc == 1 && argv)
	{
		printf_minishell();
		while (1)
		{
			rl_catch_signals = 0;
			call_signals(1);
			parser = init(argc, argv, env);
			my_env = env_init(env, my_env);
			init_hd(&parser.hd);
			str = readline("minishell$ ");
			if (!str)
				break ;
			if (ft_onlyspaces(str))
			{
				lex(&parser, &str, my_env);
				if (parser.pars)
				{
					parser.exit_status = check_ast(&parser, parser.pars, my_env);
					parser.hd->i = 0;
				}
				destroy_init(&parser);
				handle_dollar(parser.exit_status, my_env);
				add_history(str);
			}
			free(str);
		}
	}
	return (0);
}
