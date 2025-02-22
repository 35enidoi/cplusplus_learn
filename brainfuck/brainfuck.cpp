#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

class BracketNotMatch : public std::exception {
public:
    const char* what() const noexcept override {
        return "The number of brackets is incorrect.";
    }
};

class MemoryPosFlow : public std::exception {
public:
    const char* what() const noexcept override {
        return "Memory space has increased too much.";
    }
};

class MemoryPosUnderFlow : public std::exception {
public:
    const char* what() const noexcept override {
        return "Memory location cannot be backward.";
    }
};

class InputisNothing : public std::exception {
public:
    const char* what() const noexcept override {
        return "No inputs.";
    }
};

class BrainFuck
{
private:
    const unsigned int memory_limit = 2147483647;
    const unsigned int memory_num_limit = 255;
    std::string program;
    std::string inputs;
    int program_pos = 0;
    unsigned int cursor_pos = 0;
    std::vector<int> memory{0, 0, 0};
    std::vector<int> bracket_stashs{};

    void cursor_pos_increment () {
        if (cursor_pos == memory_limit) {
            throw MemoryPosFlow();
        } else {
            cursor_pos += 1;
            if (memory.size() < cursor_pos-1) {
                memory.push_back(0);
            }
        }
    }

    void cursor_pos_decrement () {
        if (cursor_pos == 0) {
            throw MemoryPosUnderFlow();
        } else {
            cursor_pos -= 1;
        }
    }
 
    void memory_increment () {
        if (memory[cursor_pos] == memory_num_limit) {
            memory[cursor_pos] = 0;
        } else {
            memory[cursor_pos] += 1;
        }
    }

    void memory_decrement () {
        if (memory[cursor_pos] == 0) {
            memory[cursor_pos] = memory_num_limit;
        } else {
            memory[cursor_pos] -= 1;
        }
    }

    void bracket_open () {
        bracket_stashs.push_back(program_pos);
    }

    void bracket_close () {
        if (memory[cursor_pos] == 0) {
            bracket_stashs.pop_back();
        } else {
            program_pos = bracket_stashs.back();  // jump
        }
    }

    void memory_out_char () {
        char a = static_cast<char>(memory[cursor_pos]);
        std::cout << a;
    }

    void memory_input_char () {
        if (inputs.empty()) {
            if (!(std::cin >> inputs)) {
                if (inputs.empty() && std::cin.eof()) {
                    throw InputisNothing();
                }
            }
        memory[cursor_pos] = static_cast<int>(inputs.back());
        inputs.pop_back();
        }
    }

public:
    BrainFuck(std::string n) : program(n) {
        // [と]の数があっているか確認
        int bracket_match = 0;

        for (int i=0; i == program.length(); i++) {
            switch (program[i])
            {
            case '[':
                bracket_match += 1;
                break;
            case ']':
                bracket_match -= 1;
                if (bracket_match < 0) {
                    throw BracketNotMatch();  // 例えば']['みたいな時
                }
                break;
            default:
                break;
            }
        }

        if (bracket_match != 0) {
            throw BracketNotMatch();  // 例えば[][みたいな時
        }
    }

    void execute() {
        while (program_pos < program.length()) {
            switch (program[program_pos]) {
                case '>':
                    cursor_pos_increment();
                    break;
                case '<':
                    cursor_pos_decrement();
                    break;
                case '+':
                    memory_increment();
                    break;
                case '-':
                    memory_decrement();
                    break;
                case '[':
                    bracket_open();
                    break;
                case ']':
                    bracket_close();
                    break;
                case ',':
                    memory_input_char();
                    break;
                case '.':
                    memory_out_char();
                    break;
                default:
                    break;
            }
            program_pos++;
        }
        std::cout << std::endl;
        for (int i; i < memory.size(); i++) {
            std::cout << memory[i] << ' ';
        }
    }
};

int main() {
    BrainFuck brain = BrainFuck("++++++++[>++++++++<-]>+.");
    brain.execute();
}
