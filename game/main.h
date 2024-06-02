#ifndef HEADER_H
#define HEADER_H

#include <gtk/gtk.h>
#include <vector>
#include <utility> // для std::pair
#include <cstdlib> // для rand и srand
#include <ctime>   // для time
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

// Структура для представления изображений вопросов и ответов
struct ImagePair {
    std::string question; // Имя файла изображения вопроса
    std::string answer;   // Имя файла изображения ответа
};
std::vector<ImagePair> images = {
    {"1.png", "ans1.png"},
    {"2.png", "ans2.png"},
    {"3.png", "ans3.png"},
    {"4.png", "ans4.png"},
    {"5.png", "ans5.png"},
    {"6.png", "ans6.png"},
    {"7.png", "ans7.png"},
    {"8.png", "ans8.png"},
    {"9.png", "ans9.png"},
    {"10.png", "ans10.png"},
    {"11.png", "ans11.png"},
    {"12.png", "ans12.png"},
    {"13.png", "ans13.png"},
    {"14.png", "ans14.png"},
    {"15.png", "ans15.png"},
    {"16.png", "ans16.png"},
    {"17.png", "ans17.png"},
    {"18.png", "ans18.png"},
    {"19.png", "ans19.png"},
    {"20.png", "ans20.png"}
};

std::string questionImageFile;
std::vector<std::string> currentAnswerCards;
int statistic_point=0;
int lvl_point=0;
    GtkTextBuffer *buffer;
    GtkWidget *view;
bool firstTry=true;
const int BUTTON_WIDTH = 750;
const int BUTTON_HEIGHT = 200;


// Функции
void shuffleImages();
std::string getRandomQuestionImage();
std::string getRandomAnswerImage(const std::string& questionImage);
std::vector<std::string> createAnswerCards(const std::string& questionImage);
void clearGrid(GtkWidget *grid);
void startNewLevel(GtkWidget *grid);
static void button_clicked(GtkWidget* button, gpointer data);

#endif // HEADER_H
