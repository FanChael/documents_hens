all:
	make -C src

clean:
	-rm -rf src/*.o
distclean:
	-rm -rf src/*.o
	-rm -rf src/doc

.PHONY:clean distclean
