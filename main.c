/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:25:10 by hudescam          #+#    #+#             */
/*   Updated: 2026/02/11 12:41:30 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static void print_tokens(t_token *t)
{
    while (t)
    {
        if (t->type == TOKEN_WORD)
            ft_printf("WORD(%s)\n", t->value);
        else if (t->type == TOKEN_PIPE)
            ft_printf("PIPE\n");
        else if (t->type == TOKEN_REDIR_IN)
            ft_printf("REDIR_IN\n");
        else if (t->type == TOKEN_REDIR_OUT)
            ft_printf("REDIR_OUT\n");
        else if (t->type == TOKEN_REDIR_APPEND)
            ft_printf("REDIR_APPEND\n");
        else if (t->type == TOKEN_HEREDOC)
            ft_printf("HEREDOC\n");
        t = t->next;
    }
}

static void	print_cmds(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		ft_printf("=== COMMAND ===\n");
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			ft_printf("ARG: %s\n", cmd->argv[i]);
			i++;
		}
		while (cmd->redirs)
		{
			ft_printf("REDIR type: %d target: %s\n",
				cmd->redirs->type,
				cmd->redirs->target);
			cmd->redirs = cmd->redirs->next;
		}
		cmd = cmd->next;
	}
}

int	main (int argc, char** argv)
{
	t_token	*tokens;
    t_cmd	*cmds;

	if (argc != 2)
	{
		ft_printf("Usage: %s \"command\"\n", argv[0]);
		return (1);
	}
	tokens = lexer(argv[1]);
	print_tokens(tokens);
    if (!tokens)
		return (1);
	if (!check_syntax(tokens))
	    return (1);
    cmds = parse_tokens(tokens);
	print_cmds(cmds);
	return (0);
}