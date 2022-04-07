#include <Windows.h>

#include <chrono>
#include <iostream>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>

constexpr std::chrono::milliseconds looong{500};
constexpr std::chrono::milliseconds shrt{100};

class Char {
public:
    Char(std::vector<std::chrono::milliseconds> beeps) : m_beeps(std::move(beeps)) {}

    void operator()() const {
        for (auto& pause : m_beeps) {
            PlaySound(TEXT("sine.wav"), nullptr, SND_FILENAME | SND_ASYNC);
            std::this_thread::sleep_for(pause);
            PlaySound(nullptr, nullptr, 0);
            std::this_thread::sleep_for(shrt);
        }
    }
public:
    std::vector<std::chrono::milliseconds> m_beeps;
};

int cppmain(std::string_view program, std::vector<std::string_view> words) {
    if(words.empty())
    {
        std::cerr << "USAGE: " << program.data() << " words to play\n";
        return 1;
    }
    for (auto& word : words) {
        for (auto letter : word) {
            std::cout << letter;
        }
        std::cout << '\n';
        std::this_thread::sleep_for(shrt);
    }
    return 0;
}

int main(int argc, char* argv[]) {
    return cppmain(argv[0], {argv + 1, argv + argc});
}
