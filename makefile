CC = gcc
CFLAGS = -ansi -Wall -pedantic -g
GLOBAL_DEPS = headers/util.h headers/table.h headers/pre_proc.h headers/first_pass.h headers/ins_parse.h headers/second_pass.h

# Object files (based on files in src/)
EXE_DEPS = assembler.o util.o table.o pre_proc.o first_pass.o ins_parse.o second_pass.o

# Executable
assembler: $(EXE_DEPS) $(GLOBAL_DEPS)
	$(CC) -g $(EXE_DEPS) $(CFLAGS) -o $@

assembler.o: src/assembler.c $(GLOBAL_DEPS)
	$(CC) -c src/assembler.c $(CFLAGS) -o $@

util.o: src/util.c $(GLOBAL_DEPS)
	$(CC) -c src/util.c $(CFLAGS) -o $@

table.o: src/table.c $(GLOBAL_DEPS)
	$(CC) -c src/table.c $(CFLAGS) -o $@

pre_proc.o: src/pre_proc.c $(GLOBAL_DEPS)
	$(CC) -c src/pre_proc.c $(CFLAGS) -o $@

first_pass.o: src/first_pass.c $(GLOBAL_DEPS)
	$(CC) -c src/first_pass.c $(CFLAGS) -o $@

ins_parse.o: src/ins_parse.c $(GLOBAL_DEPS)
	$(CC) -c src/ins_parse.c $(CFLAGS) -o $@

second_pass.o: src/second_pass.c $(GLOBAL_DEPS)
	$(CC) -c src/second_pass.c $(CFLAGS) -o $@

clean:
	rm -f *.o assembler tests/*.am tests/*.ob tests/*.ent tests/*.ext

