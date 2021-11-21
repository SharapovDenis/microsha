# Microsha

## Описание

Реализация командной оболочки Unix (Unix shell) с использованием большинства команд папки /usr/bin.

### Папки:

1. ./ :
    * `misha.cc` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; реализация функции main() --- основа работы оболочки;
    * `misha` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; бинарный файл, полученный компиляцией, описанной ниже;
    * `misha_valgrind` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; бинарный файл, предназначенный для отладки c программой valgrind;
    * `misha_fsanitize` &nbsp;&nbsp;&nbsp; бинарный файл, предназначенный для отладки;
    * `Makefile` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; предназначен для команды make;
    * `./func` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; папка, содержащая реализацию функций проекта;
    * `./bin` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; папка, содержащая бинарные файлы.

2. ./func:
    * `config.cc` &nbsp;&nbsp;&nbsp;&nbsp; "библиотека" проекта;
    * `conv.cc` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; реализация конвейера;
    * `direct.cc` &nbsp;&nbsp;&nbsp;&nbsp; реализация перенаправления потока ввода-вывода;   
    * `echo.c` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;реализация команды echo;
    * `pattern.cc` &nbsp;&nbsp; реализация обработки шаблонов "*" и "?";
    * `pwd.c` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; реализация команды pwd;
    * `time.cc` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; реализация команды time.

3. ./bin:
    * Бинарные файлы, полученные компиляцией файлов из папки func.

Бинарные файлы из папки ./bin запускаются с помощью функций семейства exec. Описания этого семества доступно в терминале при использовании команды

    man 3 exec

## Компиляция:

С использованием команды make:

    make misha_compile

    make binaries_compile

или вручную:

    c++ misha.cc -g -o misha_valgrind

    c++ misha.cc -g -fsanitize=address -o misha_fsanitize

    c++ misha.cc -o misha

    c++ [-Wall -Wextra] <file_name.cc> -o <file_name> 

    gcc [-Wall -Wextra] <file_name.c>  -o <file_name> 

## Предупреждение:

Пожалуйста, запускайте исполняемые файлы misha_valgrind, misha_fsanitize, misha в папке ./ (в той, где находится ./bin).
Иначе misha не сможет правильно прочитать путь до папки и, как следствие, правильно выполниться.

## Версии:

1.0.0 --- реализация time.c + исправлены ошибки чтения пути до ./bin в программе conv.

1.0.1 --- исправлены ошибки в time.c -> time.cc. Теперь программа выполняется с функцией _execute().