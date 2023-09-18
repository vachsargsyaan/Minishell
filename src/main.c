/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:48:21 by vacsargs          #+#    #+#             */
/*   Updated: 2023/09/18 16:18:06 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_init	parser;
	char	*str;

	if (argc == 1 && argv)
	{
		printf_minishell();
		while (1)
		{
			parser = init(argc, argv, env);
			str = readline("minishell$ ");
			if (!str)
				break ;
			lex(&parser, str,env);
			destroy_init(&parser);
			add_history(str);
			free(str);
		}
	}
	return (0);
}
