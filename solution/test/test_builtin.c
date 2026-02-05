/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:18:54 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/05 12:39:31 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_builtin_test()
{
	char **argv;
	int fd[2];
	int saved_stdout;
	char buffer[1024];
	int bytes;

	printf("ECHO BUILTIN\n");
	argv = NULL;
	if (echo_builtin(argv) == 0)
		printf("1. OK\n");
	else printf("1. ERROR argv == NULL\n");

	// First argv isn't "echo" (NULL)
	argv = malloc(sizeof(char *) * 6);
	if (echo_builtin(argv) == 0)
		printf("2. OK\n");
	else printf("2. ERROR argv[0] == NULL\n");

	// First argv isn't "echo" ("bubu")
	argv[0] = malloc(sizeof(char) * 5);
	ft_strlcpy(argv[0], "bubu", 5);
	if (echo_builtin(argv) == 0)
		printf("3. OK\n");
	else printf("3. ERROR argv[0] != 'echo'\n");

	// First argv is "echo" OK
	ft_strlcpy(argv[0], "echo", 5);
	if (echo_builtin(argv) == 1)
		printf("4. OK\n");
	else printf("4. ERROR argv[0] == 'echo'\n");

	// First argv is echo. No options. No strings
	pipe(fd);
	saved_stdout = dup(STDOUT_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	echo_builtin(argv); // call echo_builtin
	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	bytes = read(fd[0], buffer, sizeof(buffer) - 1);
	buffer[bytes] = '\0';
	if (ft_strcmp(buffer, "\n") == 0)
		printf("5. OK\n");
	else printf("5. ERROR no options no strings\n");
	close(fd[0]);
}

void	test_builtin(void)
{
	printf("\n===BUILTIN===\n");
	echo_builtin_test();
}
