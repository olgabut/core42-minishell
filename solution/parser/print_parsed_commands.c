/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsed_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:50:30 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/22 17:05:50 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static char	*redir_type_to_str(enum e_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return ("REDIR_IN (<)");
	if (type == TOKEN_REDIR_OUT)
		return ("REDIR_OUT (>)");
	if (type == TOKEN_APPEND)
		return ("APPEND (>>)");
	if (type == TOKEN_HEREDOC)
		return ("HEREDOC (<<)");
	return ("UNKNOWN");
}

static void	print_string_array(char **arr, const char *label)
{
	int	i;

	printf("  %s: [", label);
	if (!arr)
	{
		printf("NULL]\n");
		return ;
	}
	i = 0;
	while (arr[i])
	{
		printf("\"%s\"", arr[i]);
		if (arr[i + 1])
			printf(", ");
		i++;
	}
	printf("]\n");
}

static void	print_one_io(t_io *io)
{
	printf("    Type: %s\n", redir_type_to_str(io->type));
	printf("    Path: %s\n", io->path ? io->path : "(null)");
	print_string_array(io->exp_args, "    exp_args");
}

static void	print_io_list(t_io *io_list)
{
	t_io	*io;
	int		idx;

	idx = 0;
	io = io_list;
	while (io)
	{
		printf("  IO #%d:\n", idx++);
		print_one_io(io);
		io = io->next;
	}
}

void	print_parsed_commands(t_cmd *cmds)
{
	t_cmd	*cmd;
	int		cmd_idx;

	cmd_idx = 0;
	cmd = cmds;
	while (cmd)
	{
		printf("=== COMMAND %d ===\n", cmd_idx++);
		printf("  Path: %s\n", cmd->path ? cmd->path : "(null)");
		print_string_array(cmd->args, "  Args");
		if (cmd->io_list)
			print_io_list(cmd->io_list);
		else
			printf("  IO list: (empty)\n");
		printf("\n");
		cmd = cmd->next;
	}
	if (cmd_idx == 0)
		printf("(empty pipeline)\n");
}
