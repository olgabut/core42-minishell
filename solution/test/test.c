/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:12:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/05 12:09:24 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "test.h"

// Run
// make re && make tests && ./tests

int main(void)
{
	//test_lexer();
	test_builtin();
	return (0);
}
