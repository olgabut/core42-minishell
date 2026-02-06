/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:18:54 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/06 10:10:05 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *run_echo_and_capture(char **argv)
{
	int     fd[2];
	int     saved_stdout;
	char    buffer[1024];
	int     bytes;

	pipe(fd);
	saved_stdout = dup(STDOUT_FILENO);

	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);

	echo_builtin(argv);

	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	bytes = read(fd[0], buffer, sizeof(buffer) - 1);
	buffer[bytes] = '\0';
	close(fd[0]);

	return (strdup(buffer));
}

void	echo_builtin_test()
{
	char **argv;

	printf("ECHO BUILTIN\n");
	// argv == NULL.  Return 0;
	argv = NULL;
	if (echo_builtin(argv) == 0)
		printf("1. OK\n");
	else printf("1. ERROR argv == NULL\n");

	// First argv[0] = NULL.  Return 0;
	argv = malloc(sizeof(char *) * 6);
	if (echo_builtin(argv) == 0)
		printf("2. OK\n");
	else printf("2. ERROR argv[0] == NULL\n");

	// First argv[0] != "echo". Command "bubu". Return 0;
	argv[0] = malloc(sizeof(char) * 5);
	ft_strlcpy(argv[0], "bubu", 5);
	if (echo_builtin(argv) == 0)
		printf("3. OK\n");
	else printf("3. ERROR argv[0] != 'echo'\n");

	// First argv is "echo". Command "echo". Return 1;
	ft_strlcpy(argv[0], "echo", 5);
	if (echo_builtin(argv) == 1)
		printf("4. OK\n");
	else printf("4. ERROR argv[0] == 'echo'\n");

	// First argv is echo. Command "echo". Print "\n"
	if (ft_strcmp(run_echo_and_capture(argv), "\n") == 0)
		printf("5. OK\n");
	else printf("5. ERROR command 'echo'\n");

	// Command "echo -n". Print ""
	argv[1] = malloc(sizeof(char) * 3);
	ft_strlcpy(argv[1], "-n", 3);
	if (strlen(run_echo_and_capture(argv)) == 0)
		printf("6. OK\n");
	else printf("6. ERROR command 'echo -n'\n");

	// Command "echo ok". Print "ok\n"
	ft_strlcpy(argv[1], "ok", 3);
	if (ft_strcmp(run_echo_and_capture(argv), "ok\n") == 0)
		printf("7. OK\n");
	else printf("7. ERROR command 'echo ok'\n");

	// Command "echo -e". Print "\n"
	ft_strlcpy(argv[1], "-e", 3);
	if (ft_strcmp(run_echo_and_capture(argv), "\n") == 0)
		printf("8. OK\n");
	else printf("8. ERROR command 'echo -e'\n");

	// Command "echo -e hi". Print "hi\n"
	argv[2] = malloc(sizeof(char) * 3);
	ft_strlcpy(argv[2], "hi", 3);
	if (ft_strcmp(run_echo_and_capture(argv), "hi\n") == 0)
		printf("9. OK\n");
	else printf("9. ERROR command 'echo -e hi'\n");

	// Command "echo -e -n". Print ""
	ft_strlcpy(argv[2], "-n", 3);
	if (strlen(run_echo_and_capture(argv)) == 0)
		printf("10. OK\n");
	else printf("10. ERROR command 'echo -e -n'\n");

	// Command "echo -e -n to". Print "to"
	argv[3] = malloc(sizeof(char) * 3);
	ft_strlcpy(argv[3], "to", 3);
	if (ft_strcmp(run_echo_and_capture(argv), "to") == 0)
		printf("11. OK\n");
	else printf("11. ERROR command 'echo -e -n to'\n");

	// Command "echo -e -n -E". Print ""
	argv[3] = malloc(sizeof(char) * 3);
	ft_strlcpy(argv[3], "-E", 3);
	if (strlen(run_echo_and_capture(argv)) == 0)
		printf("12. OK\n");
	else printf("12. ERROR command 'echo -e -n -E'\n");

	// Command "echo -e -n -n word". Print "word"
	argv[4] = malloc(sizeof(char) * 5);
	ft_strlcpy(argv[3], "-n", 3);
	ft_strlcpy(argv[4], "word", 5);
	if (ft_strcmp(run_echo_and_capture(argv), "word") == 0)
		printf("13. OK\n");
	else printf("13. ERROR command 'echo -e -n -n word'\n");

	// Command "echo -e -n hi word". Print "hi word"
	ft_strlcpy(argv[3], "hi", 3);
	if (ft_strcmp(run_echo_and_capture(argv), "hi word") == 0)
		printf("14. OK\n");
	else printf("14. ERROR command 'echo -e -n hi word'\n");

	// Command "echo -e ow hi word". Print "ow hi word\n"
	ft_strlcpy(argv[2], "ow", 3);
	if (ft_strcmp(run_echo_and_capture(argv), "ow hi word\n") == 0)
		printf("15. OK\n");
	else printf("15. ERROR command 'echo -e ow hi word'\n");

	// Command "echo wo ow hi word". Print "wo ow hi word\n"
	ft_strlcpy(argv[1], "wo", 3);
	ft_strlcpy(argv[4], "w\nrd", 5);
	if (ft_strcmp(run_echo_and_capture(argv), "wo ow hi w\nrd\n") == 0)
		printf("16. OK\n");
	else printf("16. ERROR command 'echo wo ow hi w\nrd'\n");
}

void	test_builtin(void)
{
	printf("\n===BUILTIN===\n");
	echo_builtin_test();
}
