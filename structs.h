#ifndef STRUCT
#define STRUCT

typedef struct token
{
    int id;
    char *str;
    int prec;
} token_t;

typedef struct tokens
{
    token_t *tokens;
    unsigned int tokensN;
} tokens_t;

typedef struct token_id
{
    int token_id;
    const char *token_str;
    const char *token_descr;
    int precedence;
} token_types;

typedef struct ptree
{
    struct ptree *left;
    struct ptree *right;
    struct ptree *parent;

    int token_id;
    char **strings;
    unsigned int stringsN;
} ptree_t;

typedef struct parser
{
    ptree_t *tree;
} parser_t;

typedef struct process
{
    ptree_t *ptree;
    pid_t pid;
    int io_redir;
    char *filename;
} process_t;

typedef struct pipeline
{
    process_t *processes;
    unsigned int processesN;
    unsigned int background;
    pid_t background_pid;
} pipeline_t;

typedef struct env
{
    char *var;
    char *val;
    struct env *next;
} env_t;

typedef struct history
{
    unsigned int number;
    char *command;
    struct history *next;
} history_t;

typedef struct alias
{
    char *alias;
    char *command;
    struct alias *next;
} alias_t;

typedef struct arg_inventory
{
    char *input_commands;
    env_t *envlist;
    char **commands;
    size_t buflimit;
    int st_mode;
    history_t *history;
    char *history_file;
    alias_t *alias;
    char *alias_file;
    tokens_t tokens;
    parser_t parser;
    pipeline_t pipeline;
    int n_bg_jobs;
    int pipein;
    int pipeout;
    int io_redir;
    char *filename;
    pid_t last_bg_pid;
    int exit;
    int exit_status;
} arg_inventory_t;

typedef struct _builtins
{
    char *command;
    int (*builtin_func)(arg_inventory_t *arginv);
} builtins_t;

#endif
