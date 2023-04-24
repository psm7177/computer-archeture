#include <stdio.h>
#include <argparser.h>
#include <mips-memory.h>
#include <loader.h>
#include <ifetch.h>
#include <dec.h>
#include <control-unit.h>
#include <alu.h>
#include <execute.h>
#include <mem.h>
#include <write-back.h>
#include <debug.h>

void test_arg(argparser_t arg)
{
    dbprintf("m: %d\n", arg.option_m);
    dbprintf("addr1: %x\n", arg.addr1);
    dbprintf("addr2: %x\n", arg.addr2);

    dbprintf("d: %d\n", arg.option_d);
    dbprintf("n: %d\n", arg.option_n);
    dbprintf("num_instruction: %d\n", arg.num_instruction);

    dbprintf("filename: %s\n", arg.filename);
}

void test_memory(memory_t mem)
{
    dbprintf("text section size: %ld\n", mem.size_text);
    for (int i = 0; i < mem.size_text; i += WORD_SIZE)
    {
        unsigned int *p_text = mem.text + i;
        dbprintf("%x\n", *p_text);
    }

    dbprintf("data section size: %ld\n", mem.size_data);
    for (int i = 0; i < mem.size_data; i += WORD_SIZE)
    {
        unsigned int *p_data = mem.data + i;
        dbprintf("%x\n", *p_data);
    }
}

void test_ifetch(ifetch_t ifetch)
{
    dbprintf("pc: %x\n", ifetch.pc);
    dbprintf("num_instr: %d\n", ifetch.count_exe_instr);
    dbprintf("Instr: %x\n", ifetch.Instr);
}

void test_dec(dec_t dec)
{
    dbprintf("==dec==\n");
    dbprintf("read_data_1: %d\n", dec.read_data_1);
    dbprintf("read_data_2: %d\n", dec.read_data_2);
}

void test_ex(execute_t ex)
{
    // dbprintf("result: %d\n", ex.result);
}

void display(ifetch_t ifetch, reg_file_t reg, memory_t mem, argparser_t arg)
{
    printf("Current register values:\n");
    printf("------------------------------------\n");
    printf("pc: %x\n", ifetch.pc);
    printf("Registers:\n");
    for (int i = 0; i < NUM_REG; i++)
    {
        printf("R%d: 0x%x\n", i, read_register(&reg, i));
    }
    printf("\n");
    if (arg.option_m)
    {
        printf("Memory content [0x%x..0x%x]:\n", arg.addr1, arg.addr2);
        printf("------------------------------------\n");

        for (int i = arg.addr1; i <= arg.addr2; i += WORD_SIZE)
        {
            printf("0x%x: 0x%x\n", i, read_word(&mem, i));
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{

    argparser_t arg = parse_argument(argc, argv);
    test_arg(arg);

    memory_t memory;
    load_memory(&memory, arg.filename);
    test_memory(memory);

    reg_file_t reg_file;
    control_unit_t ctrl_unit;
    alu_t alu;

    ifetch_t ifetch;
    dec_t dec;
    execute_t ex;
    mem_t mem;
    write_back_t wb;

    mux2_t mux2_RegDst;
    mux2_t mux2_ALUSrc;
    mux4_t mux4_PCSrc;
    mux3_t mux3_MemtoReg;

    init_iftech(&ifetch, &memory, arg.num_instruction);
    init_dec(&dec, &ifetch, &ctrl_unit, &reg_file, &mux2_RegDst, &mux4_PCSrc);
    init_execute(&ex, &dec, &alu, &mux2_ALUSrc);
    init_mem(&mem, &ex, &memory);
    init_write_back(&wb, &mem, &reg_file, &mux3_MemtoReg);

    init_reg_file(&reg_file);
    init_control_unit(&ctrl_unit, &reg_file, &dec);

    test_ifetch(ifetch);
    while (iftech_clock(&ifetch))
    {
        test_ifetch(ifetch);
        dec_clock(&dec);
        execute_clock(&ex);
        mem_clock(&mem);
        write_back_clock(&wb);
        test_ex(ex);
        dbprintf("\n");
        if (arg.option_d)
        {
            display(ifetch, reg_file, memory, arg);
        }
    }
    display(ifetch, reg_file, memory, arg);

    return 0;
}
