misha_compile:
	c++ misha.cc -g -o misha_valgrind
	c++ misha.cc -fsanitize=address -g -o misha_fsanitize
	c++ misha.cc -o misha

binaries_compile:
	c++ ./func/conv.cc -o conv
	c++ ./func/direct.cc -o direct
	c++ ./func/pattern.cc -o pattern
	c++ ./func/time.cc -o time
	gcc ./func/echo.c -o echo
	gcc ./func/pwd.c -o pwd
	mv conv ./bin
	mv direct ./bin
	mv pattern ./bin
	mv time ./bin
	mv echo ./bin
	mv pwd ./bin