#include "ui.h"

#include <gtk-layer-shell/gtk-layer-shell.h>
#include <stdio.h>
#include <stdlib.h>

void ui_create(GtkApplication* app) {
    GtkWidget* window = gtk_application_window_new(app);

    gtk_layer_is_layer_window(GTK_WINDOW(window));
    gtk_layer_set_layer(GTK_WINDOW(window), GTK_LAYER_SHELL_LAYER_TOP);
    gtk_layer_auto_exclusive_zone_enable(GTK_WINDOW(window));

    gtk_layer_set_margin(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, 40);
    gtk_layer_set_margin(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, 40);
    gtk_layer_set_margin(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, 20);
    gtk_layer_set_margin(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, 0);

    GtkWidget* label = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(label),
                         "<span font_desc=\"100.0\">"
                         "GTK Layer\nShell example!"
                         "</span>");

    gtk_window_set_child(GTK_WINDOW(window), label);
    gtk_label_set_markup(GTK_LABEL(label),
                         "<span font_desc=\"100.0\">"
                         "GTK Layer\nShell example!"
                         "</span>");

    gtk_window_present(GTK_WINDOW(window));
}
