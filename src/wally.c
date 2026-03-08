#include "wally.h"

#include <gtk-layer-shell/gtk-layer-shell.h>
#include <stdio.h>
#include <stdlib.h>

static void factory_setup(GtkSignalListItemFactory* factory,
                          GtkListItem* list_item, gpointer user_data) {
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget* image = gtk_image_new();
    GtkWidget* label = gtk_label_new("");

    gtk_box_append(GTK_BOX(box), image);
    gtk_box_append(GTK_BOX(box), label);

    gtk_list_item_set_child(list_item, box);
}

static void factory_bind(GtkSignalListItemFactory* factory,
                         GtkListItem* list_item, gpointer user_data) {
    GtkWidget* box = gtk_list_item_get_child(list_item);
    GtkWidget* image = gtk_widget_get_first_child(box);
    GtkWidget* label = gtk_widget_get_last_child(box);

    guint position = gtk_list_item_get_position(list_item);

    if (position == 0) {
        gtk_image_set_from_icon_name(GTK_IMAGE(image), "list-add-symbolic");
        gtk_label_set_text(GTK_LABEL(label), "Add");
    } else {
        gtk_image_set_from_icon_name(GTK_IMAGE(image),
                                     "image-x-generic-symbolic");
        gtk_label_set_text(GTK_LABEL(label), "Wallpaper");
    }
}

GtkWidget* wally_create_shell(GtkApplication* app) {
    GtkWidget* window = gtk_application_window_new(app);

    gtk_layer_init_for_window(GTK_WINDOW(window));
    gtk_layer_set_layer(GTK_WINDOW(window), GTK_LAYER_SHELL_LAYER_TOP);

    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, TRUE);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, TRUE);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, TRUE);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, TRUE);

    gtk_layer_auto_exclusive_zone_enable(GTK_WINDOW(window));

    gtk_layer_set_margin(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, 40);
    gtk_layer_set_margin(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, 40);
    gtk_layer_set_margin(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, 20);
    gtk_layer_set_margin(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, 0);

    GListStore* store = g_list_store_new(G_TYPE_OBJECT);

    /*
    for (size_t i = 0; i < 10; i++) {
        GObject* obj = g_object_new(G_TYPE_OBJECT, NULL);
        g_list_store_append(store, obj);
        g_object_ref(obj);
    }*/

    GObject* obj = g_object_new(G_TYPE_OBJECT, NULL);
    g_list_store_append(store, obj);
    g_object_ref(obj);

    GtkSelectionModel* selection =
        GTK_SELECTION_MODEL(gtk_single_selection_new(G_LIST_MODEL(store)));

    GtkListItemFactory* factory = gtk_signal_list_item_factory_new();

    g_signal_connect(factory, "setup", G_CALLBACK(factory_setup), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(factory_bind), NULL);

    GtkWidget* grid = gtk_grid_view_new(selection, factory);

    gtk_grid_view_set_max_columns(GTK_GRID_VIEW(grid), 6);
    gtk_grid_view_set_min_columns(GTK_GRID_VIEW(grid), 3);

    gtk_grid_view_set_enable_rubberband(GTK_GRID_VIEW(grid), TRUE);

    GtkWidget* scrolled = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), grid);

    gtk_window_set_child(GTK_WINDOW(window), scrolled);

    return window;
}

void wally_render(GtkWidget* window) {
    if (window) {
        gtk_window_present(GTK_WINDOW(window));
    }
}
