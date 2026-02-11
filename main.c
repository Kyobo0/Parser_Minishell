/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:25:10 by hudescam          #+#    #+#             */
/*   Updated: 2026/02/11 17:50:29 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

// static void print_tokens(t_token *t)
// {
//     while (t)
//     {
//         if (t->type == TOKEN_WORD)
//             ft_printf("WORD(%s)\n", t->value);
//         else if (t->type == TOKEN_PIPE)
//             ft_printf("PIPE\n");
//         else if (t->type == TOKEN_REDIR_IN)
//             ft_printf("REDIR_IN\n");
//         else if (t->type == TOKEN_REDIR_OUT)
//             ft_printf("REDIR_OUT\n");
//         else if (t->type == TOKEN_REDIR_APPEND)
//             ft_printf("REDIR_APPEND\n");
//         else if (t->type == TOKEN_HEREDOC)
//             ft_printf("HEREDOC\n");
//         t = t->next;
//     }
// }

static void	print_cmds(t_cmd *cmd)
{
	t_redir	*tmp;
	int		i;

	while (cmd)
	{
		ft_printf("=== COMMAND ===\n");
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			ft_printf("ARG: %s\n", cmd->argv[i]);
			i++;
		}
		tmp = cmd->redirs;
		while (tmp)
		{
			ft_printf("REDIR type: %d target: %s\n",
				tmp->type, tmp->target);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
}

int	main(void)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;

	init_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		tokens = lexer(line);
		if (tokens && check_syntax(tokens))
		{
			cmds = parse_tokens(tokens);
			print_cmds(cmds);
			free_cmds(cmds);
		}
		free_tokens(tokens);
		free(line);
	}
	return (0);
}
// int	main (int argc, char** argv)
// {
// 	t_token	*tokens;
//     t_cmd	*cmds;

// 	if (argc != 2)
// 	{
// 		ft_printf("Usage: %s \"command\"\n", argv[0]);
// 		return (1);
// 	}
// 	init_signals();
// 	tokens = lexer(argv[1]);
//     if (!tokens)
// 		return (1);
// 	if (!check_syntax(tokens))
//     {
//         free_tokens(tokens);
// 	    return (1);
//     }
//     cmds = parse_tokens(tokens);
// 	print_cmds(cmds);
// 	while(1)
// 	{
// 		ft_printf("minishell$");
// 		getline(...)
// 	}
//     free_cmds(cmds);
//     free_tokens(tokens);
// 	return (0);
// }