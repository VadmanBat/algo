#include <iostream>
#include <windows.h>

#include "algo/kahn.hpp"

int main() {
    using size = std::size_t;
    using std::cout;

    SetConsoleOutputCP(CP_UTF8);

    // Вспомогательная функция для красивого вывода вектора
    auto print_vector = [](const std::vector<size>& vec, const std::string& title) {
        std::cout << title << ": ";
        if (vec.empty())
            std::cout << "(пусто)";
        else {
            for (size_t i = 0; i < vec.size(); ++i) {
                std::cout << vec[i];
                if (i + 1 < vec.size())
                    std::cout << " -> ";
            }
        }
        std::cout << "\n";
    };

    std::cout << "=== Тест 1: Ациклический граф ===\n";
    std::unordered_map<size, std::vector<size>> acyclic_graph = {
        {0, {1, 2}},
        {1, {3}},
        {2, {3}},
        {4, {}} // изолированная вершина
    };

    const algo::KahnTopologicalSort sorter1(acyclic_graph); // без loop_breakers

    print_vector(sorter1.result(), "Порядок выполнения");
    print_vector(sorter1.brokenLoopBreakers(), "Разорванные вершины");
    std::cout << "Всего вершин: " << sorter1.nodeCount() << "\n";
    std::cout << "Обработано вершин: " << sorter1.result().size() << "\n";
    std::cout << "Есть неразорванный цикл? " << (sorter1.hasUnbrokenCycle() ? "Да" : "Нет") << "\n\n";

    std::cout << "=== Тест 2: Циклический граф с разрываемыми петлями ===\n";
    // Граф содержит цикл 1 → 3 → 4 → 1 и ациклическую часть
    std::unordered_map<size, std::vector<size>> cyclic_graph = {
        {0, {1, 2}},
        {1, {3}},
        {2, {3}},
        {3, {4}},
        {4, {1}}, // замыкает цикл
        {5, {}}   // изолированная
    };

    // Вершины, которые можно использовать для разрыва (достаточно одной из цикла)
    const std::vector<size> loop_breakers = {1, 4}; // порядок важен: сначала попробует 1
    const algo::KahnTopologicalSort sorter2(cyclic_graph, loop_breakers);

    print_vector(sorter2.result(), "Порядок выполнения");
    print_vector(sorter2.brokenLoopBreakers(), "Разорванные вершины");
    std::cout << "Всего вершин: " << sorter2.nodeCount() << "\n";
    std::cout << "Обработано вершин: " << sorter2.result().size() << "\n";
    std::cout << "Есть неразорванный цикл? " << (sorter2.hasUnbrokenCycle() ? "Да" : "Нет") << "\n";

    return 0;
}