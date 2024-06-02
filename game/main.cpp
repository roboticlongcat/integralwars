#include <gtk/gtk.h>
#include <vector>
#include <utility> // ��� std::pair
#include <cstdlib> // ��� rand � srand
#include <ctime>   // ��� time
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

// ��������� ��� ������������� ����������� �������� � �������
struct ImagePair {
    std::string question; // ��� ����� ����������� �������
    std::string answer;   // ��� ����� ����������� ������
};

// ���������� ������ ����������� �������� � �������
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


// �������� ������� button_clicked
static void button_clicked(GtkWidget* button, gpointer data);

// ������� ��� ������������� �����������
void shuffleImages() {
    std::random_shuffle(images.begin(), images.end());
}

// ������� ��� ��������� ���������� ����������� �������
std::string getRandomQuestionImage() {
    int index = rand() % images.size();
    return images[index].question;
}

std::string getRandomAnswerImage(const std::string& questionImage) {
    std::vector<std::string> availableAnswerImages;

    // ��������� ��� ��������� ������, ����� ������ �� ���������� ������
    for (const auto& pair : images) {
        string vopros = "image/" + pair.question;
        if (vopros != questionImage) {
            availableAnswerImages.push_back(pair.answer);
        }
    }

    // �������� ��������� ������ �� ��������� �������
    int index = rand() % availableAnswerImages.size();
    return availableAnswerImages[index];
}

// ������� ��� �������� ������� �������� � ��������
std::vector<std::string> createAnswerCards(const std::string& questionImage) {
    // ������� ������ ��� �������� ���� ������ ����������� �������
    std::vector<std::string> answerImages;

    // ��������� ������ ���������� ��������� ������
    while (answerImages.size() < 4) {
        std::string randomAnswer = getRandomAnswerImage(questionImage);
        // ��������� ������������ ��������� ��������
        if (std::find(answerImages.begin(), answerImages.end(), randomAnswer) == answerImages.end()) {
            answerImages.push_back(randomAnswer);
        }
    }

    // �������� ��������� ������ ��� ������
    int indexToReplace = rand() % 4;

    // �������� ��������� ������� �� ���������� �����
    for (const auto& pair : images) {
        string vopros = "image/" + pair.question;
        if (vopros == questionImage) {
            answerImages[indexToReplace] = pair.answer;
            break;
        }
    }

    return answerImages;
}

// ������� ��� ������� ���������� ��������� � �����
void clearGrid(GtkWidget *grid) {
    // ������� ��� �������� �������� �� �����
    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(grid));
    for (iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);
}

void startNewLevel(GtkWidget *grid) {
    // ������� ���������� �������� � �����
    clearGrid(grid);

    // �������� ��������� ����������� �������
    questionImageFile = "image/" + getRandomQuestionImage();
    std::cout << "��� ����������� �������: " << questionImageFile << std::endl;

    // �������� ������ �������� �������
    std::vector<std::string> answerCards = createAnswerCards(questionImageFile);
    currentAnswerCards = answerCards;

    // ������� ����������� ������� � ��������� ��� � �����
    GtkWidget *questionImage = gtk_image_new();
    gtk_image_set_from_file(GTK_IMAGE(questionImage), questionImageFile.c_str());
    gtk_grid_attach(GTK_GRID(grid), questionImage, 0, 0, 3, 1);
    gtk_widget_set_halign(questionImage, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(questionImage, GTK_ALIGN_CENTER);

    // ������� ������ � ������������� ������� � ��������� �� � �����
    for (int i = 0; i < 4; ++i) {
        // �������� ������� ����������� ������
        std::string currImage = "image/" + answerCards[i];
        std::cout << "��� ����������� ������ " << i + 1 << ": " << currImage << std::endl;

        // ������� ������ � ������������� �����������
        GtkWidget *button = gtk_button_new();
        GtkWidget *image = gtk_image_new_from_file(currImage.c_str());
        if (image == NULL) {
            g_warning("�� ������� ��������� �����������");
        } else {
            gtk_button_set_image(GTK_BUTTON(button), image);
            gtk_widget_set_halign(image, GTK_ALIGN_CENTER);
            gtk_widget_set_valign(image, GTK_ALIGN_CENTER);
            gtk_widget_set_size_request(image, -1, -1);
        }
        // ������������� ��������� � ������� �����������
        g_object_set_data(G_OBJECT(button), "image_file", g_strdup(currImage.c_str()));

        // ������������ ������� ������ � ����� � ��������� ��
        gtk_grid_attach(GTK_GRID(grid), button, i % 2, i / 2 + 1, 1, 1);
        gtk_widget_set_size_request(button, BUTTON_WIDTH, BUTTON_HEIGHT);


        // ������������� ���������� ������� ����� �� ������
        g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), grid);
    }

    // ������� ����� � ��������� ��� � �����
std::string text = "Number of correct answers on the first attempt " + std::to_string(statistic_point) + "/" + std::to_string(lvl_point);
GtkWidget *label = gtk_label_new(text.c_str());

    gtk_grid_attach(GTK_GRID(grid), label, 0, 5, 3, 1);
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label, GTK_ALIGN_CENTER);

    // ���������� ��� �������� �����
    gtk_widget_show_all(grid);
        lvl_point += 1;
}



// ���������� ������� ����� �� ������
static void button_clicked(GtkWidget* button, gpointer data) {
    // �������� ��� ����� �����������, ��������� � �������
    const gchar *imageFile = (const gchar *)g_object_get_data(G_OBJECT(button), "image_file");
    cout << "��� ����� �����������, ��������� � �������: " << imageFile << endl;

    // ��������� ������������ ������
    bool correctAnswer = false;
    cout<<firstTry<<" "<<statistic_point<<endl;
    for (const auto& pair : images) {
        string vopros = "image/" + pair.question;
        if (vopros == questionImageFile) {
            string otvet = "image/" + pair.answer;
            if (otvet == imageFile) {
                cout << "���������� �����!" << endl;
                cout<<firstTry<<" "<<statistic_point<<endl;
                correctAnswer = true;
                if (firstTry==true){
                        statistic_point+=1;
                }
                 firstTry=true;
            }
            else {
                cout << "������������ �����!" << endl;
                firstTry=false;
                cout<<firstTry<<" "<<statistic_point<<endl;
            }
            break;
        }
    }

    // ���� ����� ����������, �������� ����� �������
    if (correctAnswer) {
        startNewLevel(GTK_WIDGET(data));
    }
}

// ������� ��� ������������� GTK � �������� ����
static gboolean activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;



    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    srand(time(NULL)); // ������������� ���������� ��������� �����

    // ��������� ��������� ���� � ��� ��������
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 800);

    // �������� ����� ��� ���������� ���������
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // ��������� ������ �������
    startNewLevel(grid);

    gtk_widget_show_all(window);

    // ������ �������� ����� ��������� ������� GTK
    gtk_main();

    return TRUE;
}

// ����� ����� � ����������
int main(int argc, char **argv) {
    // �������� ���������� GTK
    GtkApplication *app;
    int status;

    // �������� ������ ����������
    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);

    // ����������� ����������� ������� ��������� ����������
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // ������ ����������
    status = g_application_run(G_APPLICATION(app), argc, argv);

    // ������������ �������� ����������
    g_object_unref(app);

    return status;
}
