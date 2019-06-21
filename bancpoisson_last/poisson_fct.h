#include<stdio.h>
#include<stdlib.h>
#include<cairo.h>
#include<math.h>
#include<gtk/gtk.h>

typedef struct Fish
{
    cairo_surface_t *img;
    int x;
    int y;
    int direction;
    struct fish *following;
    struct fish *suivant;
}fish;

fish *l = NULL;

fish *create_fish()
{
    fish *n;
    n = (fish*)malloc(sizeof(fish));
    n->x = 0;
    n->y = 0;
    n->direction=rand()%7;
    n->suivant = NULL;
    n->img = NULL;
    n->following = NULL;
    return n;
}

void add_fish()
{
    fish *f;
    f = create_fish();
    if(!l)
        l = f;
    else
    {
        f->suivant = l;
        l = f;
    }
}

void remove_fish()
{
    fish *tmp;
    if(l)
    {
        tmp = l;
        l = l->suivant;
        tmp->suivant = NULL;
        free(tmp);
    }
}

gboolean fin;

int follow(fish *tmp, fish *tmp2)
{
    fish *tmp3;

    tmp3 = tmp2->following;
    while(tmp3)
    {
        if(tmp3 == tmp)
            return 0;
        tmp3 = tmp3->following;
    }
    return 1;
}

void do_drawing(GtkWidget *w, cairo_t *cr)
{
    fish *tmp;
    fish *tmp2;
    fish *tmp3;
    tmp = tmp2 = l;
    int i=1;
    /*cairo_surface_t *img;
    img= cairo_image_surface_create_from_png("water2.png");
    cairo_set_source_surface(cr,img,0,0);
    cairo_paint(cr);*/
    while(tmp)
    {
        if(tmp->following==NULL)
        {
            while(tmp2)
            {
                if(tmp2!=tmp)
                {
                    if(follow(tmp,tmp2))
                    {
                        if(abs(tmp->x-tmp2->x)<=30 && abs(tmp->y-tmp2->y)<=30)
                        {
                               tmp->following=tmp2;
                               break;
                        }
                    }
                }
                tmp2=tmp2->suivant;
            }
        }
        //direction = rand()%7;
        if(!tmp->following)
            tmp->direction = rand()%7;
        else
            tmp->direction = tmp->following->direction;

        switch(tmp->direction)
        {
            case 0: if(tmp->x < 30) //turn left
                        tmp->x = 968;
                    else
                        tmp->x -=10;
                    tmp->img = cairo_image_surface_create_from_png("left.png");
                    break;
            case 1: if(tmp->x < 30) //turn up left
                        tmp->x = 968;
                    else
                        tmp->x -=10;
                    if(tmp->y < 30)
                        tmp->y = 565;
                    else
                        tmp->y -=10;
                    tmp->img = cairo_image_surface_create_from_png("up_left.png");
                    break;
            case 2: if(tmp->y < 30) //turn up
                        tmp->y = 565;
                    else
                        tmp->y -=10;
                    tmp->img = cairo_image_surface_create_from_png("up.png");
                    break;
            case 3: if(tmp->x > 968) //turn up right
                        tmp->x = 0;
                    else
                        tmp->x +=10;
                    if(tmp->y < 30)
                        tmp->y = 600;
                    else
                        tmp->y -=15;
                    tmp->img = cairo_image_surface_create_from_png("up_right.png");
                    break;
            case 4: if(tmp->x > 968 ) //turn right
                        tmp->x = 0;
                    else
                        tmp->x +=15;
                    tmp->img = cairo_image_surface_create_from_png("right.png");
                    break;
            case 5: if(tmp->x > 968) //turn down right
                        tmp->x = 0;
                    else
                        tmp->x +=10;
                    if(tmp->y > 565)
                        tmp->y = 0;
                    else
                        tmp->y +=10;
                    tmp->img = cairo_image_surface_create_from_png("down_right.png");
                    break;
            case 6: if(tmp->y > 565) //turn down
                        tmp->y = 0;
                    else
                        tmp->y +=10;
                    tmp->img = cairo_image_surface_create_from_png("down.png");
                    break;
            case 7: if(tmp->x <= 0) //turn down left
                        tmp->x = 968;
                    else
                        tmp->x -=10;
                    if(tmp->y > 565)
                        tmp->y = 0;
                    else
                        tmp->y +=10;
                    tmp->img = cairo_image_surface_create_from_png("down_left.png");
                    break;

        }
        cairo_set_source_surface(cr, tmp->img, tmp->x, tmp->y);
        cairo_paint(cr);
        tmp = tmp->suivant;
    }
   //cairo_surface_destroy(img);
}

static gboolean time_handler(GtkWidget *widget)
{
    gtk_widget_queue_draw(widget);
    return fin;
}

void stop()
{
    fin = FALSE;
}

void play(GtkWidget *b, GtkWidget *w)
{
    fin = TRUE;
    g_timeout_add(300,time_handler,w);
}

