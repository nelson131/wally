#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget* window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Wally");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);

    gtk_window_set_modal(GTK_WINDOW(window), TRUE);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char** argv) {
    GtkApplication* app;
    int             status;

    app = gtk_application_new("com.github.nelson131.wally",
                              G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
