
#include "minishell.h"
#include "test.h"

// Run
// make re && make tests && ./tests

int	main(void)
{
	test_lexer();
	test_built_in();
	return (0);
}
