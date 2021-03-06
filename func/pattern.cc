#include "config.cc"
#define EXEC_EXIT 2

void walk_recursive(string const &dirname, vector<string> &ret) {

    /*

        Рекурсивный поиск файлов в директории.

    */
   
    DIR *dir = opendir(dirname.c_str());
    if (dir == nullptr) {
        return;
    }
    for (dirent *de = readdir(dir); de != nullptr; de = readdir(dir)) {
        if (strcmp(".", de->d_name) == 0 || strcmp("..", de->d_name) == 0) continue; // не берём . и ..
        ret.push_back(dirname + "/" + de->d_name); // добавление в вектор
        if (de->d_type == DT_DIR) {
            walk_recursive(dirname + "/" + de->d_name, ret);
        }
    }
    closedir(dir);
}

vector<string> walk(string const &dirname) {

    /*

        Вывод в вектор файлов директории.

    */
    vector<string> ret;
    walk_recursive(dirname, ret);
    return ret;
}

int pattern_cmp_str(string file, string pattern) {
    
    /*

        Функция сравнения имен файлов при наличии шаблонов * и ? .

    */

    long unsigned int i;

    if(file == "" && pattern == "") {
        return 1;
    }
    
    if(file != "" && pattern == "") {
        return 0;
    }

    if(pattern[0] == '?') {
        if(file.size() == 0) {
            return 0;
        }
        else { 
            return (pattern_cmp_str(file.substr(1), pattern.substr(1))); 
        }
    }
    
    if (pattern[0] == '*') {
        for (i = 0; i <= file.size(); i++) {
            if (pattern_cmp_str(file.substr(i), pattern.substr(1))) {
                return 1;
            }
        }
        return 0;
    }

    if (pattern[0] == file[0]) {
        return (pattern_cmp_str(file.substr(1), pattern.substr(1)));
    } 
    else {
        return 0;
    }
}

int pattern_cmp_vec(vector<string> args, vector<string> pattern) {

    /*

        Сравнение имён файлов для веторов.

    */

    long unsigned int i;

	if (args.size() != pattern.size()) { 
        return 0; 
    }
	for (i = 0; i < args.size(); i++) {
		if (pattern_cmp_str(args[i], pattern[i]) == 0) {
			return 0;
		}
	}
	return 1;
}

string sub_direction(string line) {

    /*

        Выводит подслово директории до первого вхождения
        шаблона * или ? .

    */

    long unsigned int i;
    string s = "";

    for(i = 0; i < line.size(); ++i) {
        if(line[i] == '*'){
            return s;
        }
        s = s + line[i];
    }
    return s;
}

int main(int argc, char **argv) {
    
    if(argc < 2) {
        fprintf(stderr, "Too few arguments\n");
        return 1;
    }

    size_t pos;
    string location = string(argv[0]);
    
    pos = location.find("/bin/pattern");
    location.erase(pos);

    int j, flag = 0, point_flag = 0;
    long unsigned int i;
    vector<string> args;

    for(j = 1; j < argc; ++j) {
        args.push_back(string(argv[j]));
    }

    int position = pattern_find(args);

    if(position < 0) {
        fprintf(stderr, "pattern_process: exit(position not found)\n");
        exit(EXIT_FAILURE);
    }
	
    vector<string> dirs, file, pattern, cmd = args;
    string joined;
    string to_walk = sub_direction(args[position]);

	if (args[position][0] == '/') {
        dirs = walk(to_walk);
        flag = 1;
    } 
    else {
        dirs = walk(".");
        flag = 0;
	}
    
    sort(dirs.begin(), dirs.end());

    vector<string> to_execute;

    for(i = 0; i < position; ++i) {
        to_execute.push_back(args[i]);
    }

    // сравниваем для каждого dirent->name
	for (i = 0; i < dirs.size(); ++i) {

        // убираем слеши
        pattern = split(args[position], '/');
        file = split(dirs[i], '/');
        
        // убираем точки из начала
        if(file[0] == ".") {
            file.erase(file.begin(), file.begin() + 1);
        }
        if(pattern[0] == ".") {
            pattern.erase(pattern.begin(), pattern.begin() + 1);
            point_flag = 1;
        }

        if (pattern_cmp_vec(file, pattern)) {

            // прицепили слеши
            joined = join(file, "/", flag, point_flag);
            to_execute.push_back(joined);

		}
	}

    for(i = position + 1; i < args.size(); ++i) {
        to_execute.push_back(args[i]);
    }

    if(to_execute.size() == position) {
        fprintf(stderr, "'%s': no such file or directory!\n", args[position].c_str());
        return 1;
    }

    return _execute(to_execute, location);
}
