/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:18:54 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/23 11:35:55 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *run_cmd_and_capture(char **argv, int (*func)(char **))
{
	int     fd[2];
	int     saved_stdout;
	char    buffer[1024];
	int     bytes;

	pipe(fd);
	saved_stdout = dup(STDOUT_FILENO);

	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);

	func(argv);

	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	bytes = read(fd[0], buffer, sizeof(buffer) - 1);
	buffer[bytes] = '\0';
	close(fd[0]);

	return (strdup(buffer));
}

char *run_env_cmd_and_capture(t_memory_info **memory, char **argv, t_env **env,
		int (*func)(t_memory_info **memory_long, char **argv, t_env **env))
{
	int     fd[2];
	int     saved_stdout;
	char    buffer[1024];
	int     bytes;

	pipe(fd);
	saved_stdout = dup(STDOUT_FILENO);

	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	func(memory, argv, env);

	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	bytes = read(fd[0], buffer, sizeof(buffer) - 1);
	buffer[bytes] = '\0';
	close(fd[0]);

	return (strdup(buffer));
}


void	built_in_echo_test()
{
	char **argv;

	printf("\nECHO BUILTIN\n");
	// argv == NULL.  Return -1;
	argv = NULL;
	if (built_in_echo(argv) == -1)
		printf("1. OK\n");
	else
		printf("1. ERROR argv == NULL\n");

	// First argv[0] = NULL.  Return -1;
	argv = calloc(7, sizeof(char *));
	if (built_in_echo(argv) == -1)
		printf("2. OK\n");
	else
		printf("2. ERROR argv[0] == NULL\n");

	// First argv[0] != "echo". Command "bubu". Return -1;
	argv[0] = calloc(5, sizeof(char));
	ft_strlcpy(argv[0], "bubu", 5);
	if (built_in_echo(argv) == -1)
		printf("3. OK\n");
	else
		printf("3. ERROR argv[0] != 'echo'\n");

	// First argv is "echo". Command "echo". Return 0;
	ft_strlcpy(argv[0], "echo", 5);
	if (built_in_echo(argv) == 0)
		printf("4. OK\n");
	else
		printf("4. ERROR argv[0] == 'echo'\n");

	// First argv is echo. Command "echo". Print "\n"
	if (ft_strcmp(run_cmd_and_capture(argv, built_in_echo), "\n") == 0)
		printf("5. OK\n");
	else
		printf("5. ERROR command 'echo'\n");

	// Command "echo -n". Print ""
	argv[1] = calloc(3, sizeof(char));
	ft_strlcpy(argv[1], "-n", 3);
	if (strlen(run_cmd_and_capture(argv, built_in_echo)) == 0)
		printf("6. OK\n");
	else
		printf("6. ERROR command 'echo -n'\n");

	// Command "echo ok". Print "ok\n"
	ft_strlcpy(argv[1], "ok", 3);
	if (ft_strcmp(run_cmd_and_capture(argv, built_in_echo), "ok\n") == 0)
		printf("7. OK\n");
	else
		printf("7. ERROR command 'echo ok'\n");

	// Command "echo -e". Print "\n"
	ft_strlcpy(argv[1], "-e", 3);
	if (ft_strcmp(run_cmd_and_capture(argv, built_in_echo), "\n") == 0)
		printf("8. OK\n");
	else
		printf("8. ERROR command 'echo -e'\n");

	// Command "echo -e hi". Print "hi\n"
	argv[2] = calloc(3, sizeof(char));
	ft_strlcpy(argv[2], "hi", 3);
	if (ft_strcmp(run_cmd_and_capture(argv, built_in_echo), "hi\n") == 0)
		printf("9. OK\n");
	else
		printf("9. ERROR command 'echo -e hi'\n");

	// Command "echo -e -n". Print ""
	ft_strlcpy(argv[2], "-n", 3);
	if (strlen(run_cmd_and_capture(argv, built_in_echo)) == 0)
		printf("10. OK\n");
	else
		printf("10. ERROR command 'echo -e -n'\n");

	// Command "echo -e -n to". Print "to"
	argv[3] = calloc(3, sizeof(char));
	ft_strlcpy(argv[3], "to", 3);
	if (ft_strcmp(run_cmd_and_capture(argv, built_in_echo), "to") == 0)
		printf("11. OK\n");
	else
		printf("11. ERROR command 'echo -e -n to'\n");

	// Command "echo -e -n -E". Print ""
	argv[3] = calloc(3, sizeof(char));
	ft_strlcpy(argv[3], "-E", 3);
	if (strlen(run_cmd_and_capture(argv, built_in_echo)) == 0)
		printf("12. OK\n");
	else
		printf("12. ERROR command 'echo -e -n -E'\n");

	// Command "echo -e -n -n word". Print "word"
	argv[4] = calloc(5, sizeof(char));
	ft_strlcpy(argv[3], "-n", 3);
	ft_strlcpy(argv[4], "word", 5);
	if (ft_strcmp(run_cmd_and_capture(argv, built_in_echo), "word") == 0)
		printf("13. OK\n");
	else
		printf("13. ERROR command 'echo -e -n -n word'\n");

	// Command "echo -e -n -n -nnn". Print ""
	ft_strlcpy(argv[4], "-nnn", 5);
	if (ft_strcmp(run_cmd_and_capture(argv, built_in_echo), "") == 0)
		printf("14. OK\n");
	else
		printf("14. ERROR command 'echo -e -n -n -nnn'\n");

	// Command "echo -e -n hi good". Print "hi good"
	ft_strlcpy(argv[4], "good", 5);
	ft_strlcpy(argv[3], "hi", 3);
	if (ft_strcmp(run_cmd_and_capture(argv, built_in_echo), "hi good") == 0)
		printf("15. OK\n");
	else
		printf("15. ERROR command 'echo -e -n hi good'\n");

	// Command "echo -e ow hi word". Print "ow hi word\n"
	ft_strlcpy(argv[4], "word", 5);
	ft_strlcpy(argv[2], "ow", 3);
	if (ft_strcmp(run_cmd_and_capture(argv, built_in_echo),
			"ow hi word\n") == 0)
		printf("16. OK\n");
	else
		printf("16. ERROR command 'echo -e ow hi word'\n");

	// Command "echo wo ow hi word". Print "wo ow hi word\n"
	ft_strlcpy(argv[1], "wo", 3);
	ft_strlcpy(argv[4], "w\nrd", 5);
	if (ft_strcmp(run_cmd_and_capture(argv, built_in_echo),
			"wo ow hi w\nrd\n") == 0)
		printf("17. OK\n");
	else
		printf("17. ERROR command 'echo wo ow hi w\nrd'\n");

	// Command "echo -e -E -e -nnn 1234". Print "1234"
	argv[5] = calloc(5, sizeof(char));
	ft_strlcpy(argv[1], "-e", 3);
	ft_strlcpy(argv[2], "-E", 3);
	ft_strlcpy(argv[3], "-e", 3);
	ft_strlcpy(argv[4], "-nnn", 5);
	ft_strlcpy(argv[5], "1234", 5);
	if (ft_strcmp(run_cmd_and_capture(argv, built_in_echo), "1234") == 0)
		printf("18. OK\n");
	else
		printf("18. ERROR command 'echo -e -E -e -nnn 1234");

	// Command "echo -e -E -e -nnf 1234". Print "-nnf 1234\n"
	ft_strlcpy(argv[4], "-nnf", 5);
	if (ft_strcmp(run_cmd_and_capture(argv, built_in_echo), "-nnf 1234\n") == 0)
		printf("19. OK\n");
	else
		printf("19. ERROR command 'echo -e -E -e -nnf 1234");

	// Command "echo -e -E -e -n-E 1234". Print "-n-E 1234\n"
	ft_strlcpy(argv[4], "-n-E", 5);
	if (ft_strcmp(run_cmd_and_capture(argv, built_in_echo), "-n-E 1234\n") == 0)
		printf("20. OK\n");
	else
		printf("20. ERROR command 'echo -e -E -e -n-E 1234");
}

void	built_in_pwd_test()
{
	char	**argv;
	char	*cwd;

	printf("\nPWD BUILTIN\n");
	// argv == NULL.  Return -1;
	argv = NULL;
	if (built_in_pwd(argv) == -1)
		printf("1. OK\n");
	else printf("1. ERROR argv == NULL\n");

	// First argv[0] = NULL.  Return -1;
	argv = calloc(3, sizeof(char *));
	if (built_in_pwd(argv) == -1)
		printf("2. OK\n");
	else printf("2. ERROR argv[0] == NULL\n");

	// First argv[0] != "pwd". Command "mmm". Return -1;
	argv[0] = calloc(4, sizeof(char));
	ft_strlcpy(argv[0], "mmm", 4);
	if (built_in_pwd(argv) == -1)
		printf("3. OK\n");
	else printf("3. ERROR argv[0] != 'pwd'\n");

	// First argv is "pwd". Command "pwd". Return 0;
	ft_strlcpy(argv[0], "pwd", 4);
	if (built_in_pwd(argv) == 0)
		printf("4. OK\n");
	else printf("4. ERROR argv[0] == 'pwd'\n");

	// Command "pwd"
	cwd = getcwd(NULL, 0);
	if (ft_strcmp(run_cmd_and_capture(argv, built_in_pwd), ft_straddchar(cwd, '\n')) == 0)
		printf("5. OK\n");
	else printf("5. ERROR command 'pwd'\n");

	free(cwd);
}

void	built_in_exit_test(void)
{
	char	**argv;

	printf("\nEXIT BUILTIN\n");
	argv = NULL;
	if (built_in_exit(argv) == -1)
		printf("1. OK\n");
	else printf("1. ERROR argv == NULL\n");
}

void	built_in_export_test(void)
{
	char			**argv;
	char			**argv_only_export;
	t_memory_info	*memory_list;
	t_env			*env;
	

	printf("\nEXPORT BUILTIN\n");
	argv = NULL;
	argv_only_export = NULL;
	memory_list = NULL;
	env = NULL;
	if (built_in_export(&memory_list, argv, &env) == -1)
		printf("1. OK\n");
	else printf("1. ERROR argv == NULL\n");

	// First argv[0] = NULL.  Return -1;
	argv = calloc(4, sizeof(char *));
	if (built_in_export(&memory_list, argv, &env) == -1)
		printf("2. OK\n");
	else
		printf("2. ERROR argv[0] == NULL\n");

	// First argv[0] != "export". Command "bububub". Return -1;
	argv[0] = calloc(7, sizeof(char));
	ft_strlcpy(argv[0], "bububub", 7);
	if (built_in_export(&memory_list, argv, &env) == -1)
		printf("3. OK\n");
	else
		printf("3. ERROR argv[0] != 'echo'\n");

	// First argv[0] != "export". Command "export". env = NULL Return 0;
	ft_strlcpy(argv[0], "export", 7);
	if (built_in_export(&memory_list, argv, &env) == 0)
		printf("4. OK\n");
	else
		printf("4. ERROR command 'export', env=NULL\n");

	// Command "export USER"
	argv[1] = calloc(50, sizeof(char));
	ft_strlcpy(argv[1], "USER", 5);
	if (ft_strlen(run_env_cmd_and_capture(
				&memory_list, argv, &env, built_in_export)) == 0
			&& count_env(env) == 1)
		printf("5. OK\n");
	else
		printf("5. ERROR command 'export USER'\n");


	// Command "export" (env has "USER=null")
	argv_only_export = calloc(3, sizeof(char *));
	argv_only_export[0] = calloc(7, sizeof(char));
	ft_strlcpy(argv_only_export[0], "export", 7);
	if (ft_strcmp(run_env_cmd_and_capture(
				&memory_list, argv_only_export, &env, built_in_export),
				"declare -x USER\n") == 0)
		printf("6. OK\n");
	else
		printf("6. ERROR command 'export' with env USER=null\n");

	// Command "export WMVAR=MyVal"
	ft_strlcpy(argv[1], "WMVAR=MyVal", 12);
	if (ft_strlen(run_env_cmd_and_capture(
				&memory_list, argv, &env, built_in_export)) == 0
			&& count_env(env) == 2)
		printf("7. OK\n");
	else
		printf("7. ERROR command 'export WMVAR=MyVal'\n");

	// Command "export" (env has "USER=null and WMVAR=MyVal ")
	if (ft_strcmp(run_env_cmd_and_capture(
				&memory_list, argv_only_export, &env, built_in_export),
				"declare -x USER\ndeclare -x WMVAR=\"MyVal\"\n") == 0)
		printf("8. OK\n");
	else
		printf("8. ERROR command 'export' with env USER and WMVAR\n");

	// Command "export MyVAR=999"
	ft_strlcpy(argv[1], "MyVAR=999", 10);
	if (ft_strlen(run_env_cmd_and_capture(
				&memory_list, argv, &env, built_in_export)) == 0
			&& count_env(env) == 3)
		printf("9. OK\n");
	else
		printf("9. ERROR command 'export MyVAR=999'\n");

	// Command "export" (env has "USER=null, WMVAR=MyVal, MyVAR=999 ")
	if (ft_strcmp(run_env_cmd_and_capture(
				&memory_list, argv_only_export, &env, built_in_export),
				"declare -x MyVAR=\"999\"\ndeclare -x USER\ndeclare -x WMVAR=\"MyVal\"\n") == 0)
		printf("10. OK\n");
	else
		printf("10. ERROR command 'export' with env USER, WMVAR, MyVAR\n");

	// Command "export MyVAR=new"  Change the value to new value
	ft_strlcpy(argv[1], "MyVAR=new", 10);
	if (ft_strlen(run_env_cmd_and_capture(
				&memory_list, argv, &env, built_in_export)) == 0
			&& count_env(env) == 3)
		printf("11. OK\n");
	else
		printf("11. ERROR command 'export MyVAR=new'\n");

	// Command "export" (env has "USER=null, WMVAR=MyVal, MyVAR=new ")
	if (ft_strcmp(run_env_cmd_and_capture(
				&memory_list, argv_only_export, &env, built_in_export),
				"declare -x MyVAR=\"new\"\ndeclare -x USER\ndeclare -x WMVAR=\"MyVal\"\n") == 0)
		printf("12. OK\n");
	else
		printf("12. ERROR command 'export' with env USER, WMVAR, MyVAR\n");
	
	// Command "export MyVAR"  No changes
	free(argv[2]);
	argv[2] = NULL;
	if (ft_strlen(run_env_cmd_and_capture(
				&memory_list, argv, &env, built_in_export)) == 0
			&& count_env(env) == 3)
		printf("13. OK\n");
	else
		printf("13. ERROR command 'export MyVAR'\n");

	// Command "export" (env has "USER=null, WMVAR=MyVal, MyVAR=new ")
	if (ft_strcmp(run_env_cmd_and_capture(
				&memory_list, argv_only_export, &env, built_in_export),
				"declare -x MyVAR=\"new\"\ndeclare -x USER\ndeclare -x WMVAR=\"MyVal\"\n") == 0)
		printf("14. OK\n");
	else
		printf("14. ERROR command 'export' with env USER, WMVAR, MyVAR\n");
	
	// Command "export USER=Bob"
	ft_strlcpy(argv[1], "USER=Bob", 9);
	if (ft_strlen(run_env_cmd_and_capture(
				&memory_list, argv, &env, built_in_export)) == 0
			&& count_env(env) == 3)
		printf("15. OK\n");
	else
		printf("15. ERROR command 'export USER=Bob'\n");

	// Command "export" (env has "USER=null, WMVAR=MyVal, MyVAR=new ")
	if (ft_strcmp(run_env_cmd_and_capture(
				&memory_list, argv_only_export, &env, built_in_export),
				"declare -x MyVAR=\"new\"\ndeclare -x USER=\"Bob\"\ndeclare -x WMVAR=\"MyVal\"\n") == 0)
		printf("16. OK\n");
	else
		printf("16. ERROR command 'export' with env USER, WMVAR, MyVAR\n");

	// Command "export _Var"
	ft_strlcpy(argv[1], "_Var", 5);
	if (ft_strlen(run_env_cmd_and_capture(
				&memory_list, argv, &env, built_in_export)) == 0
			&& count_env(env) == 4)
		printf("17. OK\n");
	else
		printf("17. ERROR command 'export _Var=Bob'\n");

	// Command "export" (env has "_Var, USER=Bob, WMVAR=MyVal, MyVAR=new ")
	if (ft_strcmp(run_env_cmd_and_capture(
				&memory_list, argv_only_export, &env, built_in_export),
				"declare -x MyVAR=\"new\"\ndeclare -x USER=\"Bob\"\ndeclare -x WMVAR=\"MyVal\"\ndeclare -x _Var\n") == 0)
		printf("18. OK\n");
	else
		printf("18. ERROR command 'export' with env USER, WMVAR, MyVAR, _Var\n");

	// Command "export 1var" wrang key
	ft_strlcpy(argv[1], "1var", 5);
	if (ft_strcmp(run_env_cmd_and_capture(
				&memory_list, argv, &env, built_in_export),
				"minishell: export: `1var`: not a valid identifier\n") == 0
			&& count_env(env) == 4)
		printf("19. OK\n");
	else
		printf("19. ERROR command 'export 1Var=Bob'\n");

	// Command "export _Var=TED AVar2=Meg" wrang key
	ft_strlcpy(argv[1], "_Var=TED", 9);
	argv[2] = calloc(50, sizeof(char));
	ft_strlcpy(argv[2], "AVar2=Meg", 10);
	if (ft_strlen(run_env_cmd_and_capture(
				&memory_list, argv, &env, built_in_export)) == 0
			&& count_env(env) == 5)
		printf("20. OK\n");
	else
		printf("20. ERROR command 'export _Var=TED AVar2=Meg'\n");
	
	// command "export"
	if (ft_strcmp(run_env_cmd_and_capture(
				&memory_list, argv_only_export, &env, built_in_export),
				"declare -x AVar2=\"Meg\"\ndeclare -x MyVAR=\"new\"\ndeclare -x USER=\"Bob\"\ndeclare -x WMVAR=\"MyVal\"\ndeclare -x _Var=\"TED\"\n") == 0)
		printf("21. OK\n");
	else
		printf("21. ERROR command 'export' with env USER, WMVAR, MyVAR, _Var\n");

	
	free_memory_links(&memory_list);
}

void	test_built_in(void)
{
	printf("\n===BUILTIN===\n");
	built_in_echo_test();
	built_in_pwd_test();
	built_in_exit_test();
	built_in_export_test();
}
