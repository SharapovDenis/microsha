MIcrosHA

Компиляция:

c++ misha.cc -g -o misha_valgrind (для запуска  valgrind ./misha_valgrind)

c++ misha.cc -fsanitize=address -o misha_fsanitize (для запуска ./a.out)

c++ -Wall -Wextra misha.cc -o misha (запуск без дополнительных программ ./a.out)

Предупреждение:

Пожалуйста, запускайте исполняемые файлы misha_valgrind, misha_fsanitize, misha в папке ./ (в той, где находится ./bin).
Иначе misha не сможет правильно прочитать путь до папки и, как следствие, выполниться.

Все исполняемые файлы получены с помощью компиляции:

c++ -Wall -Wextra <file_name.cc> -o <file_name> 

gcc -Wall -Wextra <file_name.c>  -o <file_name> 