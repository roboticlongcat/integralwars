#include "utils.h"

int main(int argc, char* argv[]) { // начальное окно выбора
  db::fill(24, db::Data_base, false);
  db::fill(15, db::Data_base_Diff, true);
  for (auto &it : db::Data_base) {
        img.push_back(it.get_p().first);
        img.push_back(it.get_p().second);
  }
  for (auto &it : db::Data_base_Diff) {
    img.push_back(it.get_p().first);
    img.push_back(it.get_p().second);
  }
  gtk_init(&argc, &argv);
  GtkWidget *window;
  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *hbox;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_window_set_title (GTK_WINDOW (window), "Integral Wars :)");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);
  //gtk_window_set_icon_from_file (GTK_WINDOW(window), "integral_icon.png", NULL);
  button1 = gtk_button_new_with_label ("Learning mode");
  button2 = gtk_button_new_with_label ("Training mode");
  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 100);
  gtk_container_set_border_width (GTK_CONTAINER (hbox), 150);
  gtk_container_add (GTK_CONTAINER (window), hbox);
  gtk_box_pack_start (GTK_BOX (hbox), button1, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (hbox), button2, FALSE, FALSE, 0);
  g_signal_connect(button1, "clicked", G_CALLBACK(btn1_click), NULL);
  g_signal_connect(button2, "clicked", G_CALLBACK(btn2_click), NULL);
  gtk_widget_show_all (window);
  gdk_threads_enter();
  gtk_main();
  gdk_threads_leave();
  return 0;
}

