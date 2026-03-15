#include "minishell.h"

t_token *add_token(t_token *head, enum e_token_type type, char *value)
{
    t_token *new_node = malloc(sizeof(t_token));
    new_node->type = type;
    new_node->value = value ? strdup(value) : NULL;
    new_node->next = NULL;

    if (!head) return new_node;

    t_token *current = head;
    while (current->next)
        current = current->next;
    current->next = new_node;
    return head;
}

void free_test_tokens(t_token *head)
{
    t_token *tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        if (tmp->value)
            free(tmp->value);
        free(tmp);
    }
}
