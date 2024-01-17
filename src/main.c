/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:48:21 by vacsargs          #+#    #+#             */
/*   Updated: 2023/12/25 16:30:19 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			lex(&parser, &str, my_env);
			if (parser.pars)
			{
				parser.exit_status = check_ast(&parser, parser.pars, my_env);
				parser.hd->i = 0;
			}
			destroy_init(&parser);
			add_history(str);
			free(str);
		}
	}
	return (0);
}
