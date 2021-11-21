# Microsha

## Описание

Реализация командной оболочки Unix (Unix shell) с использованием большинства команд папки /usr/bin.

### Папки:

1. ./ :
    * `misha.cc` реализация функции main() --- основа работы оболочки;
    * `misha` бинарный файл, полученный компиляцией, описанной ниже;
    * `misha_valgrind` бинарный файл, предназначенный для отладки c программой valgrind;
    * `misha_fsanitize` бинарный файл, предназначенный для отладки;
    * `Makefile` предназначен для команды make;
    * `./func` папка, содержащая реализацию функций проекта;
    * `./bin` папка, содержащая бинарные файлы.

2. ./func:
    * `config.cc` "библиотека" проекта;
    * `conv.cc`  реализация конвейера;
    * `direct.cc` реализация перенаправления потока ввода-вывода;   
    * `echo.c` реализация команды echo;
    * `pattern.cc` реализация обработки шаблонов "*" и "?";
    * `pwd.c` реализация команды pwd;
    * `time.cc` реализация команды time.

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