#include <iostream>
#include <string>

class HQ9Plus {
private:
    std::string args;
    int accumulator = 0;

    void hello() {
        std::cout << "Hello, world! ";
    }

    void quine() {
        std::cout << args << ' ';
    }

    void nine() {
        int i = 99;
        std::string bottle_num;
        while (i >= 0)
        {
            bottle_num = _bottle_num(i);
            
            std::cout << bottle_num << " bottles of beer on the wall." << std::endl;
            std::cout << bottle_num << " bottles of beer." << std::endl;
            std::cout << "If one of the bottles just happen to fall," << std::endl;

            if (i == 1) { // 1-1 = 0
                std::cout << "No more bottles of beer on the wall." << std::endl;
            } else if (i == 0) {
                std::cout << "We've taken them down" << std::endl;
                std::cout << "and passed them around;" << std::endl;
                std::cout << "now we're drunk and passed out!" << std::endl;
            } else {
                std::cout << i-1 << " bottles of beer on the wall." << std::endl;
            }
            
            i--;
        }
        
    }

    void incriment() {
        accumulator += 1;
    }

    std::string _bottle_num(int a) {
        if (a == 0) {
            return std::string("No more");
        } else {
            return std::to_string(a);
        }
    }

public:
    HQ9Plus(std::string n) : args(n) {}

    void execute() {
        for (int i = 0; i <= args.length(); i++) {
            switch (args[i])
            {
            case 'H':
                hello();
                break;
            case 'Q':
                quine();
                break;
            case '9':
                nine();
                break;
            case '+':
                incriment();
                break;
            default:
                break;
            }
        }
    }

};

int main() {
    std::string program;
    std::cin >> program;

    HQ9Plus executer(program);

    executer.execute();
}
