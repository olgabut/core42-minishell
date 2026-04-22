/*
 * readline_mock.c
 * Mock library for readline() using LD_PRELOAD
 * Usage: LD_PRELOAD=./libreadline_mock.so MOCK_LINES="line1\nline2\nEOF\n" ./tests
 * Note: Mock only activates when prompt is ">" (heredoc) or MOCK_HEREDOC=1 is set
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

static char **g_lines = NULL;
static size_t g_line_count = 0;
static size_t g_current_line = 0;
static int g_initialized = 0;
static int g_mock_active = 0;
static char *(*real_readline)(const char *) = NULL;

/*
 * Get real readline function from libc
 */
static void init_mock(void)
{
    if (g_initialized)
        return;
    
    /* Get real readline from next library in load chain */
    real_readline = dlsym(RTLD_NEXT, "readline");
    
    /* Check if mock should be active */
    char *heredoc_only = getenv("MOCK_HEREDOC_ONLY");
    if (heredoc_only && strcmp(heredoc_only, "1") == 0)
        g_mock_active = 1;
    
    /* Parse MOCK_LINES environment variable */
    char *env_lines = getenv("MOCK_LINES");
    if (env_lines)
    {
        /* Split by \n and store in array */
        char *copy = strdup(env_lines);
        char *token = strtok(copy, "\\n");
        
        while (token != NULL)
        {
            g_lines = realloc(g_lines, sizeof(char *) * (g_line_count + 1));
            g_lines[g_line_count++] = strdup(token);
            token = strtok(NULL, "\\n");
        }
        free(copy);
        
        /* Only activate if MOCK_HEREDOC_ONLY is not set, or if prompt is ">" */
        if (!heredoc_only)
            g_mock_active = 1;
    }
    
    g_initialized = 1;
}

/*
 * Mocked readline function
 * Returns predefined lines sequentially, then NULL on EOF
 * Only mocks when prompt is ">" (heredoc) or g_mock_active is set
 */
char *readline(const char *prompt)
{
    init_mock();
    
    /* If mock not active or no lines configured, use real readline */
    if (!g_mock_active || !g_lines || g_line_count == 0)
    {
        if (real_readline)
            return real_readline(prompt);
        return NULL;
    }
    
    /* Only mock for heredoc prompt ">" unless MOCK_HEREDOC_ONLY=0 */
    char *heredoc_only = getenv("MOCK_HEREDOC_ONLY");
    if (heredoc_only && strcmp(heredoc_only, "0") == 0)
    {
        /* Mock all readline calls */
    }
    else if (prompt && strcmp(prompt, ">") != 0)
    {
        /* Only mock heredoc prompts, fall back for others */
        if (real_readline)
            return real_readline(prompt);
        return NULL;
    }
    
    /* Return next line or NULL if exhausted */
    if (g_current_line < g_line_count)
    {
        char *line = strdup(g_lines[g_current_line++]);
        
        /* Clear lines after use to prevent infinite loop on re-run */
        if (g_current_line >= g_line_count)
        {
            for (size_t i = 0; i < g_line_count; i++)
                free(g_lines[i]);
            free(g_lines);
            g_lines = NULL;
            g_line_count = 0;
            g_current_line = 0;
        }
        
        return line;
    }
    
    return NULL;
}
