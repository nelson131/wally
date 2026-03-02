#ifndef WALLY_H
#define WALLY_H

#include <gtk-layer-shell/gtk-layer-shell.h>
#include <gtk/gtk.h>

GtkWidget* wally_create_shell(GtkApplication* app);
void       wally_render(GtkWidget* window);

#endif
