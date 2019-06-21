#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cairo.h>
#include<math.h>
#include<gtk/gtk.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#define MaxElem 1000



void file_error()
{
    GtkWidget *dialog = NULL;
    dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL,
             GTK_MESSAGE_WARNING, GTK_BUTTONS_CLOSE, "Le fichier  n'a pu etre charge");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

void no_file()
{
    GtkWidget *dialog = NULL;
    dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL,
             GTK_MESSAGE_WARNING, GTK_BUTTONS_CLOSE, "veuillez de selectionner un fichier de direction");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

void syntaxe_error()
{
    GtkWidget *dialog = NULL;
    dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL,
             GTK_MESSAGE_WARNING, GTK_BUTTONS_CLOSE, "Syntaxe erreur");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}


/////////////////////
int  tirer_nbre(char *newc){
    char chaine[20];
     int i=0;
    newc=strrchr(newc,'=');
if(newc)
{
            newc++; /// la position suivante
        while(*newc==' ') newc++;
if(*newc!='#'){
        /// le caractere est un nbre

    while(*newc!='\n' && *newc!='#' && *newc !=' ')
        {
            chaine[i]= *newc ;
                i++;
            newc++;
        }
    }
}
if(i!=0){
        strncpy(chaine,chaine,i);
        chaine[i+1]='\0';
        i=(int)atoi((char*)chaine);
}
    else
        i=1;
    return i;
}
////////////////////////
void ajouter(int tab[MaxElem],int *ligne,int n,int direct){
    if(*ligne>0)
        (*ligne)--;
 while(n>0)
{
    tab[*ligne]=direct;
    printf("\n le contenu de cette ligne(%d) === %d\n",*ligne,tab[*ligne]);
    (*ligne)++;
    n--;
}
}
/////////////////////
int remplir_tableau(int tab[MaxElem],char *f)
{
        FILE *fich=fopen(f,"r");
        char *newc=(char *)malloc(sizeof(char));
        char chaine[20];
        int n,global=0;
        if(!fich)
            return;
        char *txt=(char *)malloc(sizeof(char));
        int ligne=-1 ;
        rewind(fich);/// remettre le curseur au debut
        while(fgets(txt,255,fich)!=NULL){

            while(*txt!='\n'){
            ligne++;
            while(*txt==' ') txt++; /// igniorer le blanc

            if(*txt=='#')
            {
                ligne--;
                break;
            }
            /// sinon :: il s agit d une chaine à prendre
        else{
               if(strstr(txt,"up")!=NULL) /// si la chaine up existe ;;
               {
                   if(strstr(txt,"left")!=NULL) /// up left
                    {///
                        newc=strstr(txt,"left");
                      // tab[ligne]=1;
                        /// retourne la chaine qui contient le nbre
                        n=(int)tirer_nbre(newc); /// stocker le nbre de fois
                        ajouter(tab,&ligne,n,1); /// ajouter la dir n fois dans le tab
                        printf("\nno up left");
                    }
                   else if(strstr(txt,"right")!=NULL){
                    /// up right
                         // tab[ligne][0]=3;
                          newc=strstr(txt,"right");
                            n=(int)tirer_nbre(newc);
                             ajouter(tab,&ligne,n,3);
                             printf("\nno up right");
                   }
                   else /// pas de right et left ::
                        /// up ::
                        {
                             //tab[ligne][0]=2;
                          newc=strstr(txt,"up");
                                n=(int)tirer_nbre(newc);
                             ajouter(tab,&ligne,n,2);
                             printf("\nno up ");
                        }
                        global+=n;

                        break;
               }
                if(strstr(txt,"down")!=NULL) /// si la chaine down existe ;;
               {
                   if(strstr(txt,"left")!=NULL) /// down left
                    {///
                        newc=strstr(txt,"left");
                       //tab[ligne][0]=7;
                        /// retourne la chaine qui contient le nbre
                       n=(int)tirer_nbre(newc);
                             ajouter(tab,&ligne,n,7);/// stocker le nbre dans le tab
                             printf("\nno down left");
                    }
                   else if(strstr(txt,"right")!=NULL){
                    /// up right
                          //tab[ligne][0]=5;
                          newc=strstr(txt,"right");

                            n=(int)tirer_nbre(newc);
                             ajouter(tab,&ligne,n,5);
                             printf("\nno down right");
                   }
                   else /// pas de right et left ::
                        /// up ::
                        {
                            // tab[ligne][0]=6;
                          newc=strstr(txt,"down");
                                 n=(int)tirer_nbre(newc);
                             ajouter(tab,&ligne,n,6);
                             printf("\nno down");
                        }
                         global+=n;

                        break;
               }
                if(strstr(txt,"left")!=NULL)
                {
                        //tab[ligne][0]=0;
                        newc=strstr(txt,"left");
                        n=(int)tirer_nbre(newc);
                             ajouter(tab,&ligne,n,0);
                              global+=n;
                        break;
                }
                 if(strstr(txt,"right")!=NULL)
                {
                      //  tab[ligne][0]=4;
                        newc=strstr(txt,"right");
                        n=(int)tirer_nbre(newc);
                             ajouter(tab,&ligne,n,4);
                              global+=n;
                        break;
                }

        }
        /// parcourir la meme ligne
        txt++;
    }
}
    //printf("\nglobal = %d",global);
return global;
}
