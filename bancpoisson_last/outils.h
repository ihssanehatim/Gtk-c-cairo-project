#include "file_direction.h"

int speed=50;
int mouse_follow = 0;

typedef struct Fish
{
    cairo_surface_t *img; /// l'image du poisson
    int x; ///coordonnée X
    int y;///coordonnée Y
    int direction;///La direction à suivre
    int control;///si le poisson est contrôlé ou non
    int color;///changer la couleur lors d'un clique
    struct fish *following;///le poisson à suivre (peut être NULL)
    struct fish *suivant;
}fish;

typedef struct dir
{
    int tab[MaxElem];
    int der;///nombre de direction
    int c;///un Compteur
    fish *f;///l'adresse du 1er poisson
}direction;




fish *l = NULL;
direction *d=NULL;




void read_file(GtkWidget *btn, gpointer data)
{
    char *f,*filename;;
    xmlChar *propertyContent;
    int nbr;
    f=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(data));
    filename=(char *)malloc(sizeof(char)*strlen(f));
    strcpy(filename,f);
    filename=strrchr(filename,'.');
    if(!strcmp(filename,".xml"))
    {
            xmlDoc *doc=xmlReadFile(f,NULL,0);
            if(doc == NULL)
            {
                file_error();
                return;
            }
            xmlNode *root = xmlDocGetRootElement(doc);
            if(xmlStrcmp(root->name,"directions"))
            {
                syntaxe_error();
                return;
            }
            if(!d)
                if(!d)
                {
                    d=(direction*)malloc(sizeof(direction));
                    /// initialiser le tableau ;;
                    for(int i=0; i< MaxElem ; i++)
                    {
                            d->tab[i]=-1;
                    }
                }
            d->der=-1;
            d->c=0;
            xmlNode *widgetNode = root->children;
            xmlChar *valeur;
            for( ; widgetNode; widgetNode = widgetNode->next)
            {
                if((!xmlStrcmp(widgetNode->name,"gauche")))
                {
                    valeur =xmlNodeGetContent(widgetNode);
                    nbr=(int)atoi((char*)valeur);
                    if(nbr>0)
                    {
                        for(int i=0;i<nbr;i++)
                        {
                            d->der++;
                            d->tab[d->der]=0;
                        }
                    }

                }
                if((!xmlStrcmp(widgetNode->name,"gaucheHaut")))
                {
                    valeur =xmlNodeGetContent(widgetNode);
                    nbr=(int)atoi((char*)valeur);
                    if(nbr>0)
                    {
                        for(int i=0;i<nbr;i++)
                        {
                            d->der++;
                            d->tab[d->der]=1;
                        }
                    }

                }
                if((!xmlStrcmp(widgetNode->name,"haut")))
                {
                    valeur =xmlNodeGetContent(widgetNode);
                    nbr=(int)atoi((char*)valeur);
                    if(nbr>0)
                    {
                        for(int i=0;i<nbr;i++)
                        {
                            d->der++;
                            d->tab[d->der]=2;
                        }
                    }

                }
                if((!xmlStrcmp(widgetNode->name,"droitHaut")))
                {
                    valeur =xmlNodeGetContent(widgetNode);
                    nbr=(int)atoi((char*)valeur);
                    if(nbr>0)
                    {
                        for(int i=0;i<nbr;i++)
                        {
                            d->der++;
                            d->tab[d->der]=3;
                        }
                    }

                }
                if((!xmlStrcmp(widgetNode->name,"droit")))
                {
                    valeur =xmlNodeGetContent(widgetNode);
                    nbr=(int)atoi((char*)valeur);
                    if(nbr>0)
                    {
                        for(int i=0;i<nbr;i++)
                        {
                            d->der++;
                            d->tab[d->der]=4;
                        }
                    }

                }
                if((!xmlStrcmp(widgetNode->name,"droitBas")))
                {
                    valeur =xmlNodeGetContent(widgetNode);
                    nbr=(int)atoi((char*)valeur);
                    if(nbr>0)
                    {
                        for(int i=0;i<nbr;i++)
                        {
                            d->der++;
                            d->tab[d->der]=5;
                        }
                    }

                }
                if((!xmlStrcmp(widgetNode->name,"bas")))
                {
                    valeur =xmlNodeGetContent(widgetNode);
                    nbr=(int)atoi((char*)valeur);
                    if(nbr>0)
                    {
                        for(int i=0;i<nbr;i++)
                        {
                            d->der++;
                            d->tab[d->der]=6;
                        }
                    }

                }
                if((!xmlStrcmp(widgetNode->name,"gaucheBas")))
                {
                    valeur =xmlNodeGetContent(widgetNode);
                    nbr=(int)atoi((char*)valeur);
                    if(nbr>0)
                    {
                        for(int i=0;i<nbr;i++)
                        {
                            d->der++;
                            d->tab[d->der]=7;
                        }
                    }

                }

            }

    }
     else if(!strcmp(filename,".txt"))
    {
          if(!d)
        {
            d=(direction*)malloc(sizeof(direction));
            /// initialiser le tableau ;;
            for(int i=0; i< MaxElem ; i++)
            {
                    d->tab[i]=-1;
            }
        }
        d->c=0;
    /// remplir le tableau depuis le fichier ::
           d->der=remplir_tableau(d->tab,f) - 1;
           //printf("indice dernier = %d",d->der);
    }



}



fish *create_fish()
{
    fish *n;
    n = (fish*)malloc(sizeof(fish));
    n->x = rand()%1060;
    n->y = rand()%750;
    n->control = 0;
    n->color = 0;
    n->direction=rand()%8;
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
    {
        l = f;
        if(!d)
        {
            d=(direction*)malloc(sizeof(direction));
            d->der=-1;
        }
        d->f=f;
    }
    else
    {
        f->suivant = l;
        l = f;
    }
}
void addFish(int x,int y)
{
    fish *f;
    f = create_fish();
    f->x=x;
    f->y=y;
   if(!l)
    {
        l = f;
        if(!d)
        {
            d=(direction*)malloc(sizeof(direction));
            d->der=-1;
        }
        d->f=f;
    }
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
fin = TRUE;

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

void mouse_moved(GtkWidget *w,GdkEvent *event){
     if(event->type==GDK_MOTION_NOTIFY){
        if(mouse_follow == 1){
        GdkEventMotion* e=(GdkEventMotion*)event;
        fish* tmp;
            tmp = l;
            while(tmp)
            {
                if(!tmp->following)
                {
                    if(((double)tmp->x - e->x)>=0 && ((double)tmp->y - (guint)e->y)>=0){
                        if(((double)tmp->x - e->x)==0 && ((double)tmp->y - e->y)!=0)
                            tmp->direction = 2;
                        else if((double)(tmp->x - e->x)!=0 && ((double)tmp->y - e->y) ==0){

                            tmp->direction = 0;
                        }
                        else{

                            tmp->direction = 1;
                        }
                    }
                    else if(((double)tmp->x - e->x)<=0 && ((double)tmp->y - e->y)<=0){
                        if(((double)tmp->x - e->x)==0 && ((double)tmp->y - e->y)!=0){

                            tmp->direction = 6;
                        }
                        else if(((double)tmp->x - e->x)!=0 && ((double)tmp->y -e->y) ==0){

                            tmp->direction = 4;
                        }
                        else{

                            tmp->direction = 5;
                        }
                    }
                    else if(((double)tmp->x - e->x)<=0 && ((double)tmp->y - e->y)>=0){
                        if(((double)tmp->x - e->x)==0 && ((double)tmp->y - e->y)!=0){

                            tmp->direction = 2;
                        }
                        else if(((double)tmp->x -e->x)!=0 && ((double)tmp->y - e->y) ==0){

                            tmp->direction = 4;
                        }
                        else{

                            tmp->direction = 3;
                        }
                    }
                    else if(((double)tmp->x - e->x)>=0 && ((double)tmp->y -e->y)<=0){
                        if(((double)tmp->x - e->x)==0 && ((double)tmp->y - e->y)!=0){

                            tmp->direction = 6;
                        }
                        else if(((double)tmp->x -e->x)!=0 && ((double)tmp->y - e->y) ==0){

                            tmp->direction = 2;
                        }
                        else{

                            tmp->direction = 7;
                        }
                    }
                }
                tmp = tmp->suivant;
            }
        }
     }
}

void do_drawing(GtkWidget *w, cairo_t *cr)
{

    srand(time(NULL));
    fish *tmp;
    fish *tmp2;
    tmp = tmp2 = l;
    //int i=1;
    cairo_surface_t *img;
    img= cairo_image_surface_create_from_png("water2.png");
    cairo_set_source_surface(cr,img,0,0);
    cairo_paint(cr);
    while(tmp)
    {
        if(tmp->following==NULL && !tmp->control)
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
        if((d->der>0) && (d->c<=d->der) && (tmp==d->f) && (!tmp->control) )
        {
                    tmp->direction=d->tab[d->c];
                    d->c++;
        }else if(!tmp->following && !tmp->control){
                if(mouse_follow == 0){
                    int u, q = tmp->direction;
                    int tab[3];
                    switch(q)
                    {
                        case 0: tab[0]=0;tab[1]=1;tab[2]=7;//tab[3]=6;tab[4]=7;
                                u = rand()%3;
                                tmp->direction = tab[u];break;
                        case 1: tab[0]=1;tab[1]=0;tab[2]=2;//tab[3]=3;tab[4]=7;
                                u = rand()%3;
                                tmp->direction = tab[u];break;
                        case 2: tab[0]=2;tab[1]=1;tab[2]=3;//tab[3]=3;tab[4]=4;
                                u = rand()%3;
                                tmp->direction = tab[u];break;
                        case 3: tab[0]=3;tab[1]=2;tab[2]=4;//tab[3]=4;tab[4]=5;
                                u = rand()%3;
                                tmp->direction = tab[u];break;
                        case 4: tab[0]=4;tab[1]=3;tab[2]=5;//tab[3]=5;tab[4]=6;
                                u = rand()%3;
                                tmp->direction = tab[u];break;
                        case 5: tab[0]=5;tab[1]=4;tab[2]=6;//tab[3]=6;tab[4]=7;
                                u = rand()%3;
                                tmp->direction = tab[u];break;
                        case 6: tab[0]=6;tab[1]=7;tab[2]=5;//tab[3]=5;tab[4]=7;
                                u = rand()%3;
                                tmp->direction = tab[u];break;
                        case 7: tab[0]=7;tab[1]=0;tab[2]=6;//tab[3]=0;tab[4]=1;
                                u = rand()%3;
                                tmp->direction = tab[u];break;
                    }
                }
            }
            else if(!tmp->control)
            {
                fish *f=tmp->following;
                tmp->direction =f->direction;
            }

        switch(tmp->direction)
        {
            case 0: //if(mouse_follow == 0 || tmp->following || tmp->control){
                    if(tmp->x < 10) //turn left
                        tmp->x = 1059;
                    else
                        tmp->x -=10;
                    if(tmp->color)
                        tmp->img = cairo_image_surface_create_from_png("left_cyan.png");
                    else if(tmp->following)
                            tmp->img = cairo_image_surface_create_from_png("left.png");
                    else    tmp->img = cairo_image_surface_create_from_png("left_jaune.png");
                    break;
            case 1: //if(mouse_follow == 0 || tmp->following || tmp->control){
                    if(tmp->x < 10) //turn up left
                        tmp->x = 1059;
                    else
                        tmp->x -=10;
                    if(tmp->y < 10)
                        tmp->y = 749;
                    else
                        tmp->y -=10;
                     if(tmp->color)
                        tmp->img = cairo_image_surface_create_from_png("up_left_cyan.png");
                    else if(tmp->following)
                            tmp->img = cairo_image_surface_create_from_png("up_left.png");
                    else    tmp->img = cairo_image_surface_create_from_png("up_left_jaune.png");
                    break;
            case 2: //if(mouse_follow == 0 || tmp->following || tmp->control){
                    if(tmp->y < 10) //turn up
                        tmp->y = 749;
                    else
                        tmp->y -=10;
                     if(tmp->color)
                            tmp->img = cairo_image_surface_create_from_png("up_cyan.png");
                     else if(tmp->following)
                            tmp->img = cairo_image_surface_create_from_png("up.png");
                    else    tmp->img = cairo_image_surface_create_from_png("up_jaune.png");
                    break;
            case 3: //if(mouse_follow == 0 || tmp->following || tmp->control){
                    if(tmp->x > 1050) //turn up right
                        tmp->x = 0;
                    else
                        tmp->x +=10;
                    if(tmp->y < 10)
                        tmp->y = 749;
                    else
                        tmp->y -=10;
                     if(tmp->color)
                        tmp->img = cairo_image_surface_create_from_png("up_right_cyan.png");
                     else if(tmp->following)
                            tmp->img = cairo_image_surface_create_from_png("up_right.png");
                    else    tmp->img = cairo_image_surface_create_from_png("up_right_jaune.png");
                    break;
            case 4: //if(mouse_follow == 0 || tmp->following || tmp->control){
                    if(tmp->x > 1050) //turn right
                        tmp->x = 0;
                    else
                        tmp->x +=10;
                     if(tmp->color)
                        tmp->img = cairo_image_surface_create_from_png("right_cyan.png");
                    else if(tmp->following)
                            tmp->img = cairo_image_surface_create_from_png("right.png");
                    else    tmp->img = cairo_image_surface_create_from_png("right_jaune.png");
                    break;
            case 5: //if(mouse_follow == 0 || tmp->following || tmp->control){
                    if(tmp->x > 1050) //turn down right
                        tmp->x = 0;
                    else
                        tmp->x +=10;
                    if(tmp->y > 740)
                        tmp->y = 0;
                    else
                        tmp->y +=10;
                    if(tmp->color)
                        tmp->img = cairo_image_surface_create_from_png("down_right_cyan.png");
                    else if(tmp->following)
                            tmp->img = cairo_image_surface_create_from_png("down_right.png");
                    else    tmp->img = cairo_image_surface_create_from_png("down_right_jaune.png");
                    break;
            case 6: //if(mouse_follow == 0 || tmp->following || tmp->control){
                    if(tmp->y > 740) //turn down
                        tmp->y = 0;
                    else
                        tmp->y +=10;
                    if(tmp->color)
                        tmp->img = cairo_image_surface_create_from_png("down_cyan.png");
                     else if(tmp->following)
                            tmp->img = cairo_image_surface_create_from_png("down.png");
                    else    tmp->img = cairo_image_surface_create_from_png("down_jaune.png");
                    break;
            case 7: //if(mouse_follow == 0 || tmp->following || tmp->control){
                    if(tmp->x < 10) //turn down left
                        tmp->x = 1059;
                    else
                        tmp->x -=10;
                    if(tmp->y > 740)
                        tmp->y = 0;
                    else
                        tmp->y +=10;
                      if(tmp->color)
                        tmp->img = cairo_image_surface_create_from_png("down_left_cyan.png");
                    else if(tmp->following)
                            tmp->img = cairo_image_surface_create_from_png("down_left.png");
                    else    tmp->img = cairo_image_surface_create_from_png("down_left_jaune.png");
                    break;

        }
        cairo_set_source_surface(cr, tmp->img, tmp->x, tmp->y);
        cairo_paint(cr);
        cairo_surface_destroy(tmp->img);
        tmp = tmp->suivant;

    }
   cairo_surface_destroy(img);
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

static void changeVitesse(GtkWidget *range,GtkWidget *w)
{
    speed = gtk_range_get_value(range);
}

void play(GtkWidget *b, GtkWidget *w)
{
    fin = TRUE;
    g_timeout_add(speed,time_handler,w);
}

void remove_all()
{
    while(l)
    {
        remove_fish();
    }
}

GtkWidget * creer_bouton_image(char *designation)
{
    GtkWidget *img,*bouton;
                    img=gtk_image_new_from_file(designation);
                    bouton= gtk_button_new();
                    gtk_button_set_image(GTK_BUTTON (bouton),img);
                    return bouton;
}

void clicked(GtkWidget *widget, GdkEventButton *event,
    gpointer user_data)
{
    if (event->button == 1) {
       int x,y;
       x=event->x;
       y=event->y;
       addFish(x,y);
    }
    else if(event->button == 2)
    {
        double u = event->x;
        double k=event->y;
        fish *tmp = l;
        while(tmp){
            if((abs(tmp->x - u) <= 32) &&(abs(tmp->y - k) <= 35))
            {
                if(tmp->color)
                    tmp->color=0;
                else
                    tmp->color=1;
            }
            tmp=tmp->suivant;
        }
    }
    else if(event->button == 3)
    {
        double u = event->x;
        double k=event->y;
        fish *tmp = l;
        fish *p;
        fish *tmp2 = l;
        while(tmp){
            if((abs(tmp->x - u) <= 32) &&(abs(tmp->y - k) <= 35))
            {
                while(tmp2)
                {
                    if(tmp2->following == tmp)
                    {
                        if(tmp->following)
                            tmp2->following = tmp->following;
                        else
                        {
                            tmp2->following = NULL;

                        }
                    }
                    tmp2 = tmp2->suivant;
                }
                if(tmp == l)
                {
                    l = l->suivant;
                    tmp->suivant = NULL;
                    free(tmp);
                    break;
                }
                else
                {
                    p->suivant = tmp->suivant;
                    tmp->suivant = NULL;
                    free(tmp);
                    break;
                }
            }
            p = tmp;
            tmp = tmp->suivant;
        }
    }
}

void on_key_press(GtkWidget *w, GdkEventKey *event)
{
    fish *tmm;
    tmm = l;
    if(event->keyval == GDK_KEY_d)
        mouse_follow = 1;
    else if(event->keyval == GDK_KEY_f)
        mouse_follow = 0;
    else if(l){
        while(tmm->suivant)
            tmm = tmm->suivant;
        if(event->keyval == GDK_KEY_s)
                tmm->control = 1;
        if(event->keyval == GDK_KEY_q)
                tmm->control = 0;
        if(tmm->control)
        {
            if(event->keyval == GDK_KEY_Up)
                tmm->direction = 2;
            if(event->keyval == GDK_KEY_Down)
                tmm->direction = 6;
            if(event->keyval == GDK_KEY_Left)
                tmm->direction = 0;
            if(event->keyval == GDK_KEY_Right)
                tmm->direction = 4;
        }
    }
}

void palette(GtkWidget *table)
{


    GtkWidget *widget[7];
    GtkWidget *speed;
    GtkWidget *frame;
    GtkWidget *vbox;
    GtkWidget *box;
    GtkWidget *quit;
    quit = gtk_button_new_with_label("Quit");

    widget[6]=creer_bouton_image("add.png");
    widget[1]=creer_bouton_image("pause.png");
    widget[0]=creer_bouton_image("play.png");
    widget[3]=creer_bouton_image("clear.png");
    widget[2]=creer_bouton_image("refresh.png");
    box=gtk_hbox_new(1,1);
    gtk_box_pack_start(GTK_BOX(box),widget[6],0,1,1);
    gtk_box_pack_start(GTK_BOX(box),widget[0],0,1,1);
    gtk_box_pack_start(GTK_BOX(box),widget[1],0,1,1);
    gtk_box_pack_start(GTK_BOX(box),widget[3],0,1,1);
    gtk_box_pack_start(GTK_BOX(box),widget[2],0,1,1);
    g_signal_connect(G_OBJECT(widget[1]),"clicked",G_CALLBACK(stop), NULL);
    g_signal_connect(G_OBJECT(widget[0]),"clicked",G_CALLBACK(play), table);
    g_signal_connect(G_OBJECT(quit),"clicked",G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(widget[3]),"clicked",G_CALLBACK(remove_fish), NULL);
    g_signal_connect(G_OBJECT(widget[2]),"clicked",G_CALLBACK(remove_all), NULL);
    g_signal_connect(G_OBJECT(widget[6]),"clicked",G_CALLBACK(add_fish), NULL);
    gtk_table_attach_defaults(table,box,0,2,1,3);
    /* Création du widget GtkHScale */
    frame= gtk_frame_new("Vitesse");
    gtk_frame_set_shadow_type(frame,GTK_SHADOW_IN);
    speed = gtk_hscale_new_with_range(20,1000,20);
    gtk_container_add(GTK_CONTAINER(frame), speed);
    g_signal_connect(G_OBJECT(speed), "value-changed",G_CALLBACK (changeVitesse),table);
    gtk_table_attach_defaults(table,frame,0,2,5,7);
    frame=gtk_frame_new("Direction");
    box=gtk_hbox_new(1,10);
    widget[4]=gtk_file_chooser_button_new("Parcourir ...",GTK_FILE_CHOOSER_ACTION_OPEN);///fichier de direction
    widget[5]=creer_bouton_image("upload.png");
    g_signal_connect(G_OBJECT(widget[5]),"clicked",G_CALLBACK(read_file),GTK_WIDGET(widget[4]));
    gtk_box_pack_start(GTK_BOX(box),widget[4],1,1,10);
    gtk_box_pack_start(GTK_BOX(box),widget[5],1,1,10);
    gtk_container_add(GTK_CONTAINER(frame),box);
    gtk_table_attach_defaults(table,frame,0,2,8,10);
    gtk_table_attach_defaults(table,quit,0,2,38,40);
    GtkWidget *label;
    label = gtk_label_new("<small><b><big><u>Autres Option:</u></big></b></small>");
    gtk_table_attach_defaults(table,label,0,2,10,12);
    gtk_label_set_use_markup(label,TRUE);
    label = gtk_label_new("<small><small><b>Touche s</b>: Pour diriger un poisson leader \navec <i>les touches de direction</i>.</small></small>");
    gtk_table_attach_defaults(table,label,0,2,12,14);
    gtk_label_set_use_markup(label,TRUE);
    label = gtk_label_new("<small><small><b>Touche q</b>: Pour liberer le poisson \ncontroler par <i>la touche s.</i></small></small>");
    gtk_table_attach_defaults(table,label,0,2,14,16);
    gtk_label_set_use_markup(label,TRUE);
    label = gtk_label_new("<small><small><b>Touche d</b>: Pour activer le MOUSE FOLLOW.</small></small>");
    gtk_table_attach_defaults(table,label,0,2,16,18);
    gtk_label_set_use_markup(label,TRUE);
    label = gtk_label_new("<small><small><b>Touche f</b>: Pour desactiver le MOUSE FOLLOW.</small></small>");
    gtk_table_attach_defaults(table,label,0,2,18,20);
    gtk_label_set_use_markup(label,TRUE);
    label = gtk_label_new("<small><small><b>Clic Gauche</b>: Pour ajouter un nouveau poisson.</small></small>");
    gtk_table_attach_defaults(table,label,0,2,20,22);
    gtk_label_set_use_markup(label,TRUE);
    label = gtk_label_new("<small><small><b>Clic Droit</b>: Pour supprimer un poisson.</small></small>");
    gtk_table_attach_defaults(table,label,0,2,22,24);
    gtk_label_set_use_markup(label,TRUE);
    label = gtk_label_new("<small><small><b>Clic Molette</b>: Pour changer la couleur d'un poisson.</small></small>");
    gtk_table_attach_defaults(table,label,0,2,24,26);
    gtk_label_set_use_markup(label,TRUE);
    GtkWidget *vv;
    vv = gtk_image_new_from_file("left_jaune.png");
    label = gtk_label_new("<small><small>Un leader:</small></small>");
    gtk_label_set_use_markup(label,TRUE);
    box = gtk_hbox_new(0,2);
    gtk_box_pack_start(box,label,1,0,0);
    gtk_box_pack_start(box,vv,1,0,0);
    vv = gtk_image_new_from_file("left.png");
    label = gtk_label_new("<small><small>Un suiveur:</small></small>");
    gtk_label_set_use_markup(label,TRUE);
    gtk_box_pack_start(box,label,1,0,0);
    gtk_box_pack_start(box,vv,1,0,0);
    gtk_table_attach_defaults(table,box,0,2,26,28);
    box = gtk_hbox_new(0,2);
    vv = gtk_image_new_from_file("left_cyan.png");
    label = gtk_label_new("<small><small>Couleur autoriser pour les deux:</small></small>");
    gtk_label_set_use_markup(label,TRUE);
    gtk_box_pack_start(box,label,1,0,0);
    gtk_box_pack_start(box,vv,1,0,0);
    gtk_table_attach_defaults(table,box,0,2,28,30);
}
