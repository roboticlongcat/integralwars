#include "data_base/db_interals.h"
#include <string>
#include <vector>
#include <iostream>
#include <gtk/gtk.h>
#include <utility> // для std::pair
#include <cstdlib> // для rand и srand
#include <ctime>   // для time
#include <algorithm>
#include <glib.h> // Для g_print
#include <windows.h>

void* thread_func(void * data) {
  for (;;) {
    Sleep(500);
  }
}

void btn1_click() {
  DWORD tid;
  g_idle_add(learn_mode, NULL);
  CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_func, (LPVOID)NULL, 0, &tid);
}

void btn2_click() {
  DWORD tid;
  g_idle_add(train_mode, NULL);
  CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_func, (LPVOID)NULL, 0, &tid);
}
