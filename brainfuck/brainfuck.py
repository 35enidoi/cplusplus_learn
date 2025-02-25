from sys import stdin
from typing import Final


class BracketNotMatch(Exception):
    def __str__(self):
        return "The number of matches brackets is incorrect."


class MemoryPosFlow(Exception):
    def __str__(self):
        return "Memory space has increased too much."


class MemoryPosUnderFlow(Exception):
    def __str__(self):
        return "Memory location cannot be backward."


class InputisNothing(Exception):
    def __str__(self):
        return "No inputs."


class BrainFuck:
    def __init__(self, program: str):
        # 内部で使う変数の初期化
        self.__MEMORY_LIMIT: Final[int] = (1 << 20)
        self.__MEMORY_NUM_LIMIT: Final[int] = 255
        self.__program: str = program
        self.__inputs: str = ""
        self.__program_pos: int = 0
        self.__cursor_pos: int = 0
        self.__memory: list[int] = [0, 0, 0]
        self.__bracket_open_map = dict()
        self.__bracket_close_map = dict()

        # 一々len関数実行してると実行時間とんでもないことになるので変数で管理する
        self.__memory_length: int = len(self.__memory)

        # ブラケットの確認
        bracket_match: int = 0
        bracket_stash: list[int] = []
        for i in range(len(program)):
            match program[i]:
                case "[":
                    bracket_match += 1
                    bracket_stash.append(i)
                case "]":
                    bracket_match -= 1
                    if bracket_match < 0:
                        raise BracketNotMatch()
                    self.__bracket_open_map[bracket_stash[-1]] = i
                    self.__bracket_close_map[i] = bracket_stash[-1]
                    bracket_stash.pop()

        if bracket_match != 0:
            raise BracketNotMatch()

    def __cursor_pos_increment(self):
        if self.__cursor_pos == self.__MEMORY_LIMIT:
            raise MemoryPosFlow()
        else:
            self.__cursor_pos += 1
            if self.__memory_length-1 < self.__cursor_pos:
                self.__memory.append(0)
                self.__memory_length += 1

    def __cursor_pos_decrement(self):
        if self.__cursor_pos == 0:
            raise MemoryPosUnderFlow()
        else:
            self.__cursor_pos -= 1

    def __memory_increment(self):
        if self.__memory[self.__cursor_pos] == self.__MEMORY_NUM_LIMIT:
            self.__memory[self.__cursor_pos] = 0
        else:
            self.__memory[self.__cursor_pos] += 1

    def __memory_decrement(self):
        if self.__memory[self.__cursor_pos] == 0:
            self.__memory[self.__cursor_pos] = self.__MEMORY_NUM_LIMIT
        else:
            self.__memory[self.__cursor_pos] -= 1

    def __bracket_open(self):
        if self.__memory[self.__cursor_pos] == 0:
            self.__program_pos = self.__bracket_open_map[self.__program_pos]

    def __bracket_close(self):
        if self.__memory[self.__cursor_pos] != 0:
            self.__program_pos = self.__bracket_close_map[self.__program_pos]

    def __memory_out_char(self):
        print(chr(self.__memory[self.__cursor_pos]), end="")

    def __memory_input_char(self):
        if self.__inputs == []:
            try:
                self.__inputs = input()
            except EOFError:
                raise InputisNothing()

        self.__memory[self.__cursor_pos] = ord(self.__inputs[-1])
        self.__inputs[:-1]

    def execute(self):
        program_length = len(self.__program)  # そのままwhile文に入れると毎回len関数呼んで遅くなる
        while self.__program_pos < program_length:
            match self.__program[self.__program_pos]:
                case ">":
                    self.__cursor_pos_increment()
                case "<":
                    self.__cursor_pos_decrement()
                case "+":
                    self.__memory_increment()
                case "-":
                    self.__memory_decrement()
                case "[":
                    self.__bracket_open()
                case "]":
                    self.__bracket_close()
                case ",":
                    self.__memory_input_char()
                case ".":
                    self.__memory_out_char()

            self.__program_pos += 1


if __name__ == "__main__":
    if stdin.isatty():
        print(">>> ", end="")
    inputs = input()
    brainfuck = BrainFuck(inputs)
    brainfuck.execute()
