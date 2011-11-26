target = doc 
src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))

#compile parameters
CC = gcc
CFLAGS = -Wall -g
CPPFLAGS = -I ../include
DFLAGS = 

#install enviroment
MPATH = /usr/bin/
TIP_PATH  = /usr/bin/

$(target):$(obj)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@ 

#install
install:
	mv $(target) $(MPATH) 
	mv ./tip $(TIP_PATH) 

#clear
clean:
	-rm -rf $(obj)
distclean:
	-rm -rf $(obj) $(target)

.PHONY:clean distclean install
