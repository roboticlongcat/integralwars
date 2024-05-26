
#include "data_base/db_interals.h"
#include<string>
#include<vector>
#include <iostream>
#include <gtk/gtk.h>
 int current_image_index = 0;
 int index=0;
  GtkWidget *card_btn;
  std::vector<std::string> img;

void on_back_button_clicked(GtkWidget *widget, gpointer data)
{
  g_print("Back_Button clicked!\n");
}
void change_img(GtkWidget *widget) {
  //g_print("CHANGE IMAGE\n");
    if (current_image_index == img.size() - 1)
    current_image_index = 1;
else
    current_image_index = (current_image_index ) % img.size()+2;
  // ������� ����������� ��� ������
  GtkWidget *image3 = gtk_image_new_from_file(img[current_image_index].c_str());
  // std::cout<<img[current_image_index]<<'\n';
  // ���������, ��� ����������� ����������� �������
  if (image3 == NULL) {
      g_warning("�� ������� ��������� �����������");
  } else {
    gtk_button_set_image(GTK_BUTTON(widget), image3);
  }
}
void slide(GtkWidget *widget) {
  //g_print("CHANGE IMAGE\n");
  // ������� ����������� ��� ������
  GtkWidget *image3 = gtk_image_new_from_file(img[current_image_index+index].c_str());
  // std::cout<<img[current_image_index+index]<<'\n';
  // ���������, ��� ����������� ����������� �������
  if (image3 == NULL) {
      g_warning("�� ������� ��������� �����������");
  } else {
    gtk_button_set_image(GTK_BUTTON(widget), image3);
  }
      index = (index+1)%2;

}
G_MODULE_EXPORT void onExit(GtkWidget * w) {
    gtk_main_quit();
}

void yes_btn_click(GtkWidget *widget, gpointer data)
{
  if(current_image_index<25)db::Data_base[current_image_index/2].change_state(true);
  else db::Data_base_Diff[current_image_index/2].change_state(true);

  change_img(card_btn);
  //g_print("Yes_Button clicked!\n");
}
void no_btn_click(GtkWidget *widget, gpointer data)
{
    if(current_image_index<25)db::Data_base[current_image_index/2].change_state(true);
    else db::Data_base_Diff[current_image_index/2].change_state(true);    change_img(card_btn);
   // g_print("No_Button clicked!\n");
}
void f(int argc, char * argv[])
{
     db::fill(24, db::Data_base, false);

    db::fill(15, db::Data_base_Diff, true);

    for(auto &it : db::Data_base)
    {
        img.push_back(it.get_p().first);
        img.push_back(it.get_p().second);
    }
    for(auto &it : db::Data_base_Diff)
    {
        img.push_back(it.get_p().first);
        img.push_back(it.get_p().second);
    }
        gtk_init(&argc, &argv);


    GtkBuilder * ui_builder;
    GError * err = NULL;
    ui_builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(ui_builder, "card_window.glade", &err)) {
        g_critical ("Cannot open file UI: %s", err->message);
        g_error_free (err);
    }
    GdkRGBA color;
    gdk_rgba_parse(&color, "#EEDFEC");
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(ui_builder, "card_window"));
    gtk_widget_show_all(window);
    GtkWidget *fixed = GTK_WIDGET(gtk_builder_get_object(ui_builder, "MAIN_FIXED"));

    GtkWidget *tab1 = GTK_WIDGET(gtk_builder_get_object(ui_builder, "Tab1"));

    GtkWidget *stac = GTK_WIDGET(gtk_builder_get_object(ui_builder, "stack1"));
gtk_widget_override_background_color(stac, GTK_STATE_FLAG_NORMAL, &color);

GtkWidget *back_btn = GTK_WIDGET(gtk_builder_get_object(ui_builder, "back_btn"));
    g_signal_connect (G_OBJECT (back_btn), "clicked", G_CALLBACK (on_back_button_clicked), NULL);

GtkWidget *yes_btn = GTK_WIDGET(gtk_builder_get_object(ui_builder, "yes_btn"));
    g_signal_connect (G_OBJECT (yes_btn), "clicked", G_CALLBACK (yes_btn_click), NULL);
GtkWidget *no_btn = GTK_WIDGET(gtk_builder_get_object(ui_builder, "no_btn"));
    g_signal_connect (G_OBJECT (no_btn), "clicked", G_CALLBACK (no_btn_click), NULL);


   GtkWidget *frame_card = GTK_WIDGET(gtk_builder_get_object(ui_builder, "frame_card"));


    card_btn = gtk_button_new();
    std::string curr_image = "list_img/start.png";
    GtkWidget *image = gtk_image_new_from_file(curr_image.c_str());
    if (image == NULL) {
        g_warning("�� ������� ��������� �����������");
    } else {
          g_print("Ura");
        gtk_button_set_image(GTK_BUTTON(card_btn), image);
    }
    gtk_widget_set_halign(image, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(image, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(image, -1, -1);
    gtk_container_add(GTK_CONTAINER(frame_card), card_btn);

    gtk_widget_show_all(frame_card);

    g_signal_connect (G_OBJECT (card_btn), "clicked", G_CALLBACK (slide), NULL);
}

