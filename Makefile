misha_compile:
	c++ misha.cc -g -o misha_valgrind
	c++ misha.cc -fsanitize=address -g -o misha_fsanitize
	c++ misha.cc -o misha

binaries_compile:
	c++ ./func/conv.cc -o ./bin/conv
	c++ ./func/direct.cc -o ./bin/direct
	c++ ./func/pattern.cc -o ./bin/pattern
	c++ ./func/time.cc -o ./bin/time
	gcc ./func/echo.c -o ./bin/echo
	gcc ./func/pwd.c -o ./bin/pwd
