#include <stdio.h>
#include <string.h>
#include <argparser.h>
#include <regex.h>
#include <stdlib.h>
#include <parser.h>
#include <debug.h>

argparser_t parse_argument(int argc, char *argv[])
{
    argparser_t arg;
    regex_t option_reg;
    regex_t filename_reg;

    arg.option_m = false;
    arg.option_d = false;
    arg.option_n = false;
    arg.addr1 = 0;
    arg.addr2 = 0;
    arg.num_instruction = -1;

    if (regcomp(&option_reg, "-[a-z]", REG_EXTENDED) != 0)
    {
        dbprintf("option_reg is not compliled successfully.");
        exit(1);
    }

    if (regcomp(&filename_reg, "[^.]+\\.o", REG_EXTENDED) != 0)
    {
        dbprintf("filename_reg is not compliled successfully.");
        exit(1);
    }

    for (int i = 1; i < argc; i++)
    {
        if (regexec(&option_reg, argv[i], 0, 0, 0) == 0)
        {
            switch (argv[i][1])
            {
            case 'm':
                arg.option_m = true;
                i += parse_option_m(&arg, argv[i + 1]);
                break;
            case 'd':
                arg.option_d = true;
                break;
            case 'n':
                arg.option_n = true;
                i += parse_option_n(&arg, argv[i + 1]);
                break;
            }
        }
        else if (regexec(&filename_reg, argv[i], 0, 0, 0) == 0)
        {
            parse_filename(&arg, argv[i]);
        }
    }

    return arg;
}

int parse_option_m(argparser_t *arg, char *str)
{
    regmatch_t matches[3];

    regex_t mem_range_reg;
    if (regcomp(&mem_range_reg, "(0x[0-9a-fA-F]+):(0x[0-9a-fA-F]+)", REG_EXTENDED) != 0)
    {
        dbprintf("mem_range_reg is not compliled successfully.");
        return 0;
    }

    if (regexec(&mem_range_reg, str, 3, matches, 0) == 0)
    {
        dbprintf("matched");

        char addr1[32];
        char addr2[32];

        slice_str(addr1, str, matches[1].rm_so, matches[1].rm_eo);
        slice_str(addr2, str, matches[2].rm_so, matches[2].rm_eo);

        // dbprintf("%d %d\n",matches[1].rm_so,matches[1].rm_eo);
        // dbprintf("%d %d\n",matches[2].rm_so,matches[2].rm_eo);
        // dbprintf("%s \n%s \n%s\n", str,addr1, addr2);

        arg->addr1 = str_hex2int(addr1);
        arg->addr2 = str_hex2int(addr2);
        return 1;
    }
    arg->option_m = false;

    return 0;
}

int parse_option_n(argparser_t *arg, char *str)
{
    regex_t num_instruction_reg;
    if (regcomp(&num_instruction_reg, "[0-9]+", REG_EXTENDED) != 0)
    {
        dbprintf("mem_range_reg is not compliled successfully.");
        return 0;
    }

    if (regexec(&num_instruction_reg, str, 0, 0, 0) == 0)
    {
        arg->num_instruction = atoi(str);
        return 1;
    }
    arg->option_n = false;

    return 0;
}

int parse_filename(argparser_t *arg, char *str)
{
    int len_filename = strlen(str);
    arg->filename = malloc(sizeof(char) * (len_filename + 1));
    memcpy(arg->filename, str, len_filename + 1);
}