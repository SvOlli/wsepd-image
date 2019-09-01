
all:

%:
	make -C src $@

distclean: clean
	rm -rf extern

test:
	: no test

