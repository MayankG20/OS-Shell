CC=gcc
CFLAGS=-I ./
DEPS=functions.h
OBJ= run.o functions.o cd.o pwd.o fgbg.o ls.o info.o chkbg.o piping.o cmd.o redir.o jobs.o findpid.o kill.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -g
# 	here -o $@ denotes left side of (:) and $< is the first item on the right side of (:)

shell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
# 	here $^ denotes all the items which are on the right side of (:)

.PHONY: clean

clean:
	rm -rf *.o

