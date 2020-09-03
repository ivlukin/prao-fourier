#include <iostream>
#include <vector>

int main(int argc, char **argv) {
    std::vector<std::string> args;
    if (argc != 3) {
        std::cout << "provide correct number of args!" << std::endl;
        exit(-1);
    }
    for (int i = 0; i < argc; ++i) {
        std::string arg(argv[i]);
        args.push_back(arg);
    }
    if (args[1] != "-config") {
        std::cout << "provide --c or -config argument" << std::endl;
        std::cout << args[1] << std::endl;
        exit(-1);
    }

    // TODO 1. Сделать класс конфиг с парсингом джсона
    // TODO 2. Сканировать файлы в папке в TimeCoordinateHandler
    // TODO 3. Брать первый файл в качестве опорного
    // TODO 4. Сгенерить тайм-координаты согласно опорному файлу
    // TODO 5. Написать метод, вытаскивающий из файла нужный отрезок по звездному времени
}
