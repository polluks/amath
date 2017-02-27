/*
 * Copyright (c) 2014-2017 Carsten Sonne Larsen <cs@innolan.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifdef GTK
#include <gtk/gtk.h>
#include "system/graph_gtk.h"

GtkGraphWindow::GtkGraphWindow(UserFunction* function)
{

}

GtkGraphWindow::~GtkGraphWindow()
{

}

/* Backing pixmap for drawing area */
static GdkPixmap *pixmap = NULL;

/* Create a new backing pixmap of the appropriate size */
static gboolean configure_event( GtkWidget         *widget,
                                 GdkEventConfigure *event )
{
    if (pixmap)
        g_object_unref (pixmap);

    pixmap = gdk_pixmap_new (widget->window,
                             widget->allocation.width,
                             widget->allocation.height,
                             -1);

    gdk_draw_rectangle (pixmap,
                        widget->style->white_gc,
                        TRUE,
                        0, 0,
                        widget->allocation.width,
                        widget->allocation.height);

    return TRUE;
}

/* Redraw the screen from the backing pixmap */
static gboolean expose_event( GtkWidget      *widget,
                              GdkEventExpose *event )
{
    gdk_draw_drawable (widget->window,
                       widget->style->fg_gc[gtk_widget_get_state (widget)],
                       pixmap,
                       event->area.x, event->area.y,
                       event->area.x, event->area.y,
                       event->area.width, event->area.height);

    return FALSE;
}

/* Draw a rectangle on the screen */
static void draw_brush( GtkWidget *widget,
                        gdouble    x,
                        gdouble    y)
{
    GdkRectangle update_rect;

    update_rect.x = x - 5;
    update_rect.y = y - 5;
    update_rect.width = 10;
    update_rect.height = 10;

    gdk_draw_rectangle (pixmap,
                        widget->style->black_gc,
                        TRUE,
                        update_rect.x, update_rect.y,
                        update_rect.width, update_rect.height);

    gtk_widget_queue_draw_area (widget,
                                update_rect.x, update_rect.y,
                                update_rect.width, update_rect.height);
}

static gboolean button_press_event( GtkWidget      *widget,
                                    GdkEventButton *event )
{
    if (event->button == 1 && pixmap != NULL)
        draw_brush (widget, event->x, event->y);

    return TRUE;
}

/*
static gboolean motion_notify_event( GtkWidget *widget,
                                     GdkEventMotion *event )
{
    int x, y;
    GdkModifierType state;

    if (event->is_hint)
        gdk_window_get_pointer (event->window, &x, &y, &state);
    else
    {
        x = event->x;
        y = event->y;
        state = event->state;
    }

    if (state & GDK_BUTTON1_MASK && pixmap != NULL)
        draw_brush (widget, x, y);

    return TRUE;
}
*/

//void quit ()
//{
//    exit (0);
//}

void GtkGraphWindow::DrawGraph()
{
    GtkWidget *window;
    GtkWidget *drawing_area;
    GtkWidget *vbox;

    GtkWidget *button;

    gtk_init (NULL, NULL);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_name (window, "Test Input");

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    g_signal_connect (window, "destroy",
                      G_CALLBACK (gtk_main_quit), NULL);

    /* Create the drawing area */

    drawing_area = gtk_drawing_area_new ();
    gtk_widget_set_size_request (GTK_WIDGET (drawing_area), 200, 200);
    gtk_box_pack_start (GTK_BOX (vbox), drawing_area, TRUE, TRUE, 0);

    gtk_widget_show (drawing_area);

    /* Signals used to handle backing pixmap */

    //g_signal_connect (drawing_area, "expose_event",
    //                  G_CALLBACK (expose_event), NULL);
    //g_signal_connect (drawing_area, "configure_event",
    //                  G_CALLBACK (configure_event), NULL);

    /* Event signals */

    //g_signal_connect (drawing_area, "motion_notify_event",
    //                  G_CALLBACK (motion_notify_event), NULL);
    //g_signal_connect (drawing_area, "button_press_event",
    //                  G_CALLBACK (button_press_event), NULL);

    gtk_widget_set_events (drawing_area, GDK_EXPOSURE_MASK
                           | GDK_LEAVE_NOTIFY_MASK
                           | GDK_BUTTON_PRESS_MASK
                           | GDK_POINTER_MOTION_MASK
                           | GDK_POINTER_MOTION_HINT_MASK);

    /* The following call enables tracking and processing of extension
       events for the drawing area */
    gtk_widget_set_extension_events (drawing_area, GDK_EXTENSION_EVENTS_CURSOR);

    /* .. And some buttons */
    button = gtk_button_new_with_label ("Input Dialog");
    gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);

    //g_signal_connect (button, "clicked",
    //                  G_CALLBACK (create_input_dialog), NULL);
    gtk_widget_show (button);

    button = gtk_button_new_with_label ("Quit");
    gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);

    g_signal_connect_swapped (button, "clicked",
                              G_CALLBACK (gtk_widget_destroy),
                              window);
    gtk_widget_show (button);

    gtk_widget_show (window);

    gtk_main ();
}
#endif
