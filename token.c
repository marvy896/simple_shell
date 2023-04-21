#include "shell.h"

/**
 * tokenize - tokenizes command string
 * @tokens: tokens_t struct containing initial string and array of strings
 * @string: command string
 */
void tokenize(tokens_t *tokens, const char *string)
{
    unsigned int l = _strlen(string);
    if (l == 0) l = 1; // If the length is zero, set it to 1 to avoid issues with malloc later
    init_tokens(tokens, l);

    char *data = safe_malloc((l * 2 + 1) * sizeof(char));
    unsigned int string_idx = 0;
    unsigned int data_idx = 0;
    unsigned int tokens_idx = 0;
    unsigned int skip_next = 0;
    unsigned int skip_quote = 0;
    unsigned int is_token = 0;

    char symbol;
    while ((symbol = string[string_idx++]) != '\0' && symbol != '#')
    {
        if (!is_token && _isspace(symbol))
            continue;

        if (!is_token && !_isspace(symbol) && (symbol != ';'))
        {
            tokens->tokens[tokens_idx++].str = data + data_idx;
            is_token = 1;
        }

        if (is_token && _isspace(symbol) && !skip_next && !skip_quote)
        {
            data[data_idx++] = '\0';
            is_token = 0;
            continue;
        }

        if ((symbol == ';') && !skip_next && !skip_quote)
        {
            if (is_token)
                data[data_idx++] = '\0';

            tokens->tokens[tokens_idx++].str = data + data_idx;
            data[data_idx++] = ';';
            data[data_idx++] = '\0';
            is_token = 0;
            continue;
        }

        if ((symbol == '\"' || symbol == '\'') && !skip_next)
        {
            skip_quote = !skip_quote;
            continue;
        }

        if ((symbol == '\\') && !skip_next)
        {
            skip_next = 1;
            continue;
        }

        skip_next = 0;
        data[data_idx++] = symbol;
    }

    cleanup_tokens(tokens, tokens_idx, data);
}

/**
 * cleanup_tokens - cleans up tokenized tokens variable
 * @tokens: the tokenized tokens variable
 * @tokens_idx: the index referring to the tokens
 * @data: pointer used to store the data in tokens, only used in this
 * function to free the memory there
 */
void cleanup_tokens(tokens_t *tokens, unsigned int tokens_idx, char *data)
{
    tokens->tokensN = tokens_idx;
    token_classify(tokens);
    delete_dups(tokens);

    if (tokens->tokensN)
    {
        if (tokens->tokens[tokens->tokensN - 1].id == TOKEN_SEMICOLON)
            tokens->tokensN--;

        for (unsigned int i = 0; i < tokens->tokensN; i++)
            tokens->tokens[i].str = _strdup((char *)tokens->tokens[i].str);
    }

    free(data);
}
