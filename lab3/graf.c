/* Kompilacja: gcc graf.c -o graf `pkg-config --cflags --libs gtk+-2.0` */
 
#include <gtk/gtk.h>
 
#define MIN_X 20
#define MIN_Y 20
#define PROMIEN 5
 
static gboolean rysuj(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
  GtkAllocation allocation;
  gint szer, wys, x, y;
  guint i;
 
  cr = gdk_cairo_create(gtk_widget_get_window(widget));
 
  gtk_widget_get_allocation (widget, &allocation); // Pobiera dane o kontrolce: X, Y, szerokosc, wysokosc
  szer = allocation.width;
  wys = allocation.height;
  x =  allocation.x;
  y = allocation.y;
 
  /* Rysowanie linii pionowych */
  cairo_set_source_rgb( cr, 0.8, 0.8, 0.8 ); // Ustawia kolor "szary"
  for ( i = x + MIN_X; i < szer; i += MIN_X )
  {
 
    cairo_move_to ( cr, i, y); // Ustawia pióro na wsp. x,y
    cairo_line_to ( cr, i, wys ); // Rysuje linie
  }
  cairo_stroke ( cr ); // Wyswietla na kontrolce
 
  /* Rysowanie linii poziomych */
  for ( i = y + MIN_Y; i < wys; i += MIN_Y )
  {
    cairo_move_to ( cr, x, i);
    cairo_line_to ( cr, szer, i );
 
 
  }
  cairo_stroke ( cr ); // Wyswietla na kontrolce
 
  /* Rysowanie "grafu" :) */
  cairo_set_source_rgb( cr, 1.0, 0.0, 0.0 ); // Ustawia kolor czerwony
  cairo_arc( cr, 80, 150, PROMIEN, 0, 2 * G_PI ); // Rysuje okrag
  cairo_arc( cr, 50, 60, PROMIEN, 0, 2 * G_PI ); // Rysuje okrag
  cairo_stroke ( cr ); // Wyswietla na kontrolce
 
  cairo_destroy(cr);
 
  return FALSE;
}
 
 
int main (int argc, char *argv[])
{
  GtkWidget *okno, *kontener_vbox, *obszar_rysunkowy;
 
  gtk_init (&argc, &argv);
 
  okno = g_object_new ( GTK_TYPE_WINDOW, "window-position", GTK_WIN_POS_CENTER, "title", "Graf", NULL );
  g_signal_connect ( okno, "destroy", G_CALLBACK (gtk_main_quit), NULL );
 
  kontener_vbox = g_object_new( GTK_TYPE_VBOX, "spacing", 5, NULL );
  gtk_container_add( GTK_CONTAINER( okno ), kontener_vbox );
 
  obszar_rysunkowy = gtk_drawing_area_new ();
  gtk_box_pack_start ( GTK_BOX(kontener_vbox), obszar_rysunkowy, TRUE, TRUE, 0 );
  g_signal_connect(obszar_rysunkowy, "expose-event", G_CALLBACK(rysuj), NULL);
 
  gtk_widget_show_all ( okno );
  gtk_main ();
 
  return 0;
}
