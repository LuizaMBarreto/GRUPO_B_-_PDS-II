#include "interface/JogoGUI.hpp"
#include <iostream>
#include <exception>

int main() {
    try {
        JogoGUI jogo(1000, 700);
        jogo.executar();
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    } catch(...) {
        std::cerr << "Erro desconhecido ocorreu." << std::endl;
        return 1;
    }
    return 0;
}

