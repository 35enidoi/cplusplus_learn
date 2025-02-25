#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
#include <unistd.h>

class BracketNotMatch : public std::exception {
public:
    const char* what() const noexcept override {
        return "The number of matches brackets is incorrect.";
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
    const unsigned int memory_limit = 1 << 20;  // 1MBくらい
    const unsigned int memory_num_limit = 255;
    std::string program;
    std::string inputs;
    int program_pos = 0;
    int cursor_pos = 0;
    std::vector<unsigned char> memory{0, 0, 0};
    std::unordered_map<int, int> bracket_open_map{};
    std::unordered_map<int, int> bracket_close_map{};

    void cursor_pos_increment () {
        if (cursor_pos == memory_limit) {
            throw MemoryPosFlow();
        } else {
            cursor_pos += 1;
            if ((memory.size()-1) < cursor_pos) {
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
        if (memory[cursor_pos] == 0) {
            program_pos = bracket_open_map[program_pos];
        }
    }

    void bracket_close () {
        if (memory[cursor_pos] != 0) {
            program_pos = bracket_close_map[program_pos];
        }
    }

    void memory_out_char () {
        char a = static_cast<char>(memory[cursor_pos]);
        std::cout << a;
    }

    void memory_input_char () {
        // 入力文字がないとき
        if (inputs.empty()) {
            std::getline(std::cin, inputs);
            // 入力文字の中身がなく、EOFの時
            if (inputs.empty() && std::cin.eof()) {
                throw InputisNothing();
            }

        memory[cursor_pos] = static_cast<int>(inputs.front());
        inputs.erase(0);
        }
    }

public:
    explicit BrainFuck(const std::string& n) : program(n) {
        // [と]の数があっているか確認
        int bracket_match = 0;
        std::vector<int> bracket_stash{};

        for (int i=0; i < program.length(); i++) {
            switch (program[i]) {
            case '[':
                bracket_match += 1;
                bracket_stash.push_back(i);
                break;
            case ']':
                bracket_match -= 1;
                if (bracket_match < 0) {
                    throw BracketNotMatch();  // 例えば']['みたいな時
                }
                bracket_open_map.emplace(bracket_stash.back(), i);
                bracket_close_map.emplace(i, bracket_stash.back());
                bracket_stash.pop_back();
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
    }
};

int main() {
    std::string input;

    if (isatty(STDIN_FILENO)) {
        // 端末(キーボード)からの実行時
        std::cout << ">>> ";
    }
    std::getline(std::cin, input);

    BrainFuck brain = BrainFuck(input);
    brain.execute();
}
