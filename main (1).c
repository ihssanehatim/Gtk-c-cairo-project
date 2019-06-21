#include"outils.h"

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *darea;
    gtk_init(&argc, &argv);
   GtkWidget *table;
   GtkWidget *frame;
   GtkWidget *label[2];

   table=gtk_table_new(40,40,0);
    //srand(15);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_icon_from_file(GTK_WINDOW(window),"icon.png",NULL);
    gtk_container_add(GTK_CONTAINER (window), table);
    darea = gtk_drawing_area_new();
    frame=gtk_frame_new("");
    gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_OUT);
    gtk_container_add(GTK_CONTAINER(frame),darea);
    gtk_table_attach_defaults(table,frame,10,40,0,40);
    g_signal_connect(G_OBJECT(darea), "draw",G_CALLBACK(do_drawing), NULL);
    //g_signal_connect(quitter, "destroy",G_CALLBACK (gtk_main_quit), NULL);
    gtk_widget_add_events(darea, GDK_BUTTON_PRESS_MASK);
    g_signal_connect(darea, "button-press-event",G_CALLBACK(clicked), NULL);
    label[0] = gtk_label_new("MOUSE FOLLOW: <b>OFF</b>");
    label[1] = gtk_label_new("FISH CONTROL: <b>OFF</b>");
    g_signal_connect(G_OBJECT (window), "key_press_event", G_CALLBACK (on_key_press), label);
    g_signal_connect (G_OBJECT (darea), "motion-notify-event",G_CALLBACK (mouse_moved), NULL);
    gtk_widget_add_events(darea, GDK_POINTER_MOTION_MASK);

    //gtk_window_set_default_size(window,1000,600);
    gtk_window_fullscreen(window);
    gtk_window_set_title(GTK_WINDOW(window), "Banc Poisson");
    palette(table);

    gtk_label_set_use_markup(label[1],TRUE);
    gtk_label_set_use_markup(label[0],TRUE);
    gtk_table_attach_defaults(table,label[1],0,2,30,32);
    gtk_table_attach_defaults(table,label[0],0,2,32,34);

    g_timeout_add(50,time_handler,window);
    g_timeout_add(50,palette,table);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
