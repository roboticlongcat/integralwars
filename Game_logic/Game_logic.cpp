#include "Game_logic.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

void playGame() {
    // включаем рандом
    std::srand(std::time(0));

    // заполняем бд, скорее всего эта функция уйдет, как только напишем MAIN
    //!!!!
    db::fill(db::base1);

    // пока есть непройденные карточки
    for (int i = 0; i < db::size_table; ++i) {
        if (!db::is_learned[i]) {
            // выбираемм случайный интеграл из ббд
            int randomIndex = std::rand() % db::size_table;
            std::string integral = std::to_string(randomIndex) + ".png";

            // генирируем правильный ответ
            std::vector<std::string> options;
            options.push_back(db::base1[integral]); // правильный ответ

            // генерируем еще 3 неправильных ответа (просто случайные)
            for (int j = 0; j < 3; ++j) {
                int randomWrongIndex = std::rand() % db::size_table;
                std::string wrongIntegral = std::to_string(randomWrongIndex) + ".png";
                if (wrongIntegral != integral) {
                    options.push_back(db::base1[wrongIntegral]);
                }
            }

            // перемешиваем варианты ответа
            std::random_shuffle(options.begin(), options.end());

            // предлагаем варианты пользователю
            std::cout << "Выберите правильный ответ для интеграла " << integral << ":\n";
            for (size_t k = 0; k < options.size(); ++k) {
                std::cout << k+1 << ". " << options[k] << "\n";
            }

            // получаем ответ пользователя, ВАЖНО ПОКА ЧТО ПОЛУЧАЕМ ОТВЕТ В ВИДЕ НАПИСАННОЙ ЦИФРЫ ОТ ПОЛЬЗОВАТЕЛЯ,
            // ПОТОМ ПОМЕНЯЮ НА ИНТЕРАКТИВ С ПОМОЩЬЮ БИБЛИОТЕКИ
            int userChoice;
            std::cin >> userChoice;
            --userChoice; // приводим к индексу в векторе

            // проверка ответа
            if (options[userChoice] == db::base1[integral]) {
                std::cout << "Победа! Вы выбрали правильный ответ.\n";
                // ставим флаг, что этот интеграл пройден
                db::cards(db::base1, integral, true);
            } else {
                std::cout << "Вы ошиблись. Попробуйте еще раз.\n";
            }
        }
    }

    std::cout << "Поздравляем! Вы прошли все интегралы.\n";
}
