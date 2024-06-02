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

// Глобальный вектор изображений вопросов и ответов
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


// Прототип функции button_clicked
static void button_clicked(GtkWidget* button, gpointer data);

// Функция для перемешивания изображений
void shuffleImages() {
    std::random_shuffle(images.begin(), images.end());
}

// Функция для получения случайного изображения вопроса
std::string getRandomQuestionImage() {
    int index = rand() % images.size();
    return images[index].question;
}

std::string getRandomAnswerImage(const std::string& questionImage) {
    std::vector<std::string> availableAnswerImages;

    // Добавляем все доступные ответы, кроме ответа на переданный вопрос
    for (const auto& pair : images) {
        string vopros = "image/" + pair.question;
        if (vopros != questionImage) {
            availableAnswerImages.push_back(pair.answer);
        }
    }

    // Выбираем случайный индекс из доступных ответов
    int index = rand() % availableAnswerImages.size();
    return availableAnswerImages[index];
}

// Функция для создания массива карточек с ответами
std::vector<std::string> createAnswerCards(const std::string& questionImage) {
    // Создаем вектор для хранения имен файлов изображений ответов
    std::vector<std::string> answerImages;

    // Добавляем четыре уникальных случайных ответа
    while (answerImages.size() < 4) {
        std::string randomAnswer = getRandomAnswerImage(questionImage);
        // Проверяем уникальность выбранной картинки
        if (std::find(answerImages.begin(), answerImages.end(), randomAnswer) == answerImages.end()) {
            answerImages.push_back(randomAnswer);
        }
    }

    // Выбираем случайный индекс для замены
    int indexToReplace = rand() % 4;

    // Заменяем случайный элемент на правильный ответ
    for (const auto& pair : images) {
        string vopros = "image/" + pair.question;
        if (vopros == questionImage) {
            answerImages[indexToReplace] = pair.answer;
            break;
        }
    }

    return answerImages;
}

// Функция для очистки предыдущих элементов в сетке
void clearGrid(GtkWidget *grid) {
    // Удаляем все дочерние элементы из сетки
    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(grid));
    for (iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);
}

void startNewLevel(GtkWidget *grid) {
    // Очищаем предыдущие элементы в сетке
    clearGrid(grid);

    // Получаем случайное изображение вопроса
    questionImageFile = "image/" + getRandomQuestionImage();
    std::cout << "Имя изображения вопроса: " << questionImageFile << std::endl;

    // Получаем массив карточек ответов
    std::vector<std::string> answerCards = createAnswerCards(questionImageFile);
    currentAnswerCards = answerCards;

    // Создаем изображение вопроса и добавляем его в сетку
    GtkWidget *questionImage = gtk_image_new();
    gtk_image_set_from_file(GTK_IMAGE(questionImage), questionImageFile.c_str());
    gtk_grid_attach(GTK_GRID(grid), questionImage, 0, 0, 3, 1);
    gtk_widget_set_halign(questionImage, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(questionImage, GTK_ALIGN_CENTER);

    // Создаем кнопки с изображениями ответов и добавляем их в сетку
    for (int i = 0; i < 4; ++i) {
        // Получаем текущее изображение ответа
        std::string currImage = "image/" + answerCards[i];
        std::cout << "Имя изображения ответа " << i + 1 << ": " << currImage << std::endl;

        // Создаем кнопку и устанавливаем изображение
        GtkWidget *button = gtk_button_new();
        GtkWidget *image = gtk_image_new_from_file(currImage.c_str());
        if (image == NULL) {
            g_warning("Не удалось загрузить изображение");
        } else {
            gtk_button_set_image(GTK_BUTTON(button), image);
            gtk_widget_set_halign(image, GTK_ALIGN_CENTER);
            gtk_widget_set_valign(image, GTK_ALIGN_CENTER);
            gtk_widget_set_size_request(image, -1, -1);
        }
        // Устанавливаем связанное с кнопкой изображение
        g_object_set_data(G_OBJECT(button), "image_file", g_strdup(currImage.c_str()));

        // Рассчитываем позицию кнопки в сетке и добавляем ее
        gtk_grid_attach(GTK_GRID(grid), button, i % 2, i / 2 + 1, 1, 1);
        gtk_widget_set_size_request(button, BUTTON_WIDTH, BUTTON_HEIGHT);


        // Устанавливаем обработчик события клика на кнопку
        g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), grid);
    }

    // Создаем текст и добавляем его в сетку
std::string text = "Number of correct answers on the first attempt " + std::to_string(statistic_point) + "/" + std::to_string(lvl_point);
GtkWidget *label = gtk_label_new(text.c_str());

    gtk_grid_attach(GTK_GRID(grid), label, 0, 5, 3, 1);
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label, GTK_ALIGN_CENTER);

    // Показываем все элементы сетки
    gtk_widget_show_all(grid);
        lvl_point += 1;
}



// Обработчик события клика на кнопке
static void button_clicked(GtkWidget* button, gpointer data) {
    // Получаем имя файла изображения, связанное с кнопкой
    const gchar *imageFile = (const gchar *)g_object_get_data(G_OBJECT(button), "image_file");
    cout << "Имя файла изображения, связанное с кнопкой: " << imageFile << endl;

    // Проверяем правильность ответа
    bool correctAnswer = false;
    cout<<firstTry<<" "<<statistic_point<<endl;
    for (const auto& pair : images) {
        string vopros = "image/" + pair.question;
        if (vopros == questionImageFile) {
            string otvet = "image/" + pair.answer;
            if (otvet == imageFile) {
                cout << "Правильный ответ!" << endl;
                cout<<firstTry<<" "<<statistic_point<<endl;
                correctAnswer = true;
                if (firstTry==true){
                        statistic_point+=1;
                }
                 firstTry=true;
            }
            else {
                cout << "Неправильный ответ!" << endl;
                firstTry=false;
                cout<<firstTry<<" "<<statistic_point<<endl;
            }
            break;
        }
    }

    // Если ответ правильный, начинаем новый уровень
    if (correctAnswer) {
        startNewLevel(GTK_WIDGET(data));
    }
}

// Функция для инициализации GTK и создания окна
static gboolean activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;



    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    srand(time(NULL)); // Инициализация генератора случайных чисел

    // Установка заголовка окна и его размеров
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 800);

    // Создание сетки для размещения элементов
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Запускаем первый уровень
    startNewLevel(grid);

    gtk_widget_show_all(window);

    // Запуск главного цикла обработки событий GTK
    gtk_main();

    return TRUE;
}

// Точка входа в приложение
int main(int argc, char **argv) {
    // Создание приложения GTK
    GtkApplication *app;
    int status;

    // Создание нового приложения
    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);

    // Подключение обработчика событий активации приложения
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // Запуск приложения
    status = g_application_run(G_APPLICATION(app), argc, argv);

    // Освобождение ресурсов приложения
    g_object_unref(app);

    return status;
}
