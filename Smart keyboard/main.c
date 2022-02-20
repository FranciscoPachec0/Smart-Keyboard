#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <ctype.h>
#include "struct.h"

GtkWidget* window;
GtkWidget* grid;
GtkWidget* button;
GtkWidget *conteudo, *conteudo1, *conteudo2;
GtkWidget *label_user, *label_password;
char buffer[15];
char buffer3[40];
char bufferr[40];
List tab[99999];
int j=0;

char* to_code(char *s, char code[]){
    int size=0;
    while(*s != '\0'){
        if (*s == 'a' || *s == 'A' || *s == 'b' || *s == 'B' || *s == 'c' || *s == 'C') {
            code[size++] = '2';
        }
        if (*s == 'd' || *s == 'D' || *s == 'e' || *s == 'E' || *s == 'f' || *s == 'F') {
            code[size++] = '3';
        }
        if (*s == 'g' || *s == 'G' || *s == 'h' || *s == 'H' || *s == 'i' || *s == 'I') {
            code[size++] = '4';
        }
        if (*s == 'j' || *s == 'J' || *s == 'k' || *s == 'K' || *s == 'l' || *s == 'L') {
            code[size++] = '5';
        }
        if (*s == 'm' || *s == 'M' || *s == 'n' || *s == 'N' || *s == 'o' || *s == 'O') {
            code[size++] = '6';
        }
        if (*s == 'p' || *s == 'P' || *s == 'q' || *s == 'Q' || *s == 'r' || *s == 'R' || *s == 's' || *s == 'S') {
            code[size++] = '7';
        }
        if (*s == 't' || *s == 'T' || *s == 'u' || *s == 'U' || *s == 'v' || *s == 'V') {
            code[size++] = '8';
        }
        if (*s == 'w' || *s == 'W' || *s == 'x' || *s == 'X' || *s == 'y' || *s == 'Y' || *s == 'z' || *s == 'Z') {
            code[size++] = '9';
        }
        s++;
    }
    code[size] = '\0';
    return code;
}

int analisar(char string[]){
    for (int i = 0; i<strlen(string); i++) {
        //if (atoi(string) == 0) return 1;
        if(string[i]>=48 && string[i]<=57) return 1;
    }
    return 0;
}

void ver (List *tab){
    for(int i=2; i<99999; i++){
        if(!list_empty(tab[i])){
            list_print(tab[i]);
        }
    }
}

char convertch(wint_t char1){
    //printf("%d",char1);
    char ch;
    int char2 = char1;
    if(iswpunct(char1)){
        ch = '*';
        return ch;
    }
    switch (char2){
        case 225: case 224: case 227 : case 226 :
            ch = 'a';
            return ch;
        case 232 : case 233 : case 234 :
            ch = 'e';
            return ch;
        case 236 : case 237 : case 238 :
            ch = 'i';
            return ch;
        case 243: case 242 : case 244 : case 245 :
            ch = 'o';
            return ch;
        case 249 : case 250 : case 251 :
            ch = 'u';
            return ch;
        case 231:
            ch = 'c';
            return ch;
        default:
            ch = char2;
            return ch;
    }
}

void aux(char string[],char code[],List tab[]){
    long int posicao;
    if (!isalpha(string[strlen(string)-1])) string[strlen(string)-1] = '\0';
    Palavra temp;
    for(int i=0;i<strlen(string);i++) string[i] = (char)tolower(string[i]);
    strcpy(temp.palavra, string);
    to_code(string, code);
    strcpy(temp.code_orignal, code);
    if (strlen(code) > 5) {
        code[5] = '\0';
    }
    strcpy(temp.code, code); // tou a guardar o codigo pequene e nao o original
    temp.ocur = 1;
    posicao = atoi(code);
    list_insert(tab[posicao], temp);
}

void button_clicked(GtkWidget *widget, gpointer data) {
    char buffer2[2];
    int a = (int) data;
    char code[20];
    sprintf(buffer2, "%d", a);
    //printf("buffer2 %s\n",  buffer2);
    //printf("buffera %s\n",  buffer);
    int i =0;
    for(i = 0;i<15;i++) if(buffer[i] == '\0') break;
    g_print("clicked %d\n",  a);
    if(a == 12){
        j=0;
        buffer[strlen(buffer)-1] = '\0';
        buffer3[strlen(buffer3)-1]='\0';
        gtk_label_set_text((GtkLabel*)label_user,buffer3);
    }else if(a==10){
        j++;
        //printf("!");
        int posicao=0;
        //printf("!");

        char string[30];
        if(isalpha(buffer[0])) strcpy(buffer,to_code(buffer,code));
        strcpy(string,buffer);
        //printf("!");
        int flag=0;
        if (strlen(string)<2){
            flag=1;
        }else{
            char string_posicao[20];
            //printf("!");
            strcpy(string_posicao, string);
            //printf("!");
            if (strlen(string)<=5){
                List lista = tab[atoi(string)];
                list_print(lista);
                if(!list_empty(lista)){
                    for(int h=0;h<j;h++){
                        if(lista->next != NULL){
                            lista = lista->next;
                        }else{
                            printf("esta\n\n");
                            lista = tab[atoi(string)];
                            lista = lista->next;
                            list_print(lista);
                            j=1;
                        }
                    }
                }
                strcpy(buffer, lista->info.palavra);
            } else if (strlen(string)>5){
                string_posicao[5]='\0';
                posicao = atoi(string_posicao);
                List lista2 = tab[posicao];
                list_print(lista2);
                if(!list_empty(lista2)){
                    for(int h=0;h<j;h++){
                        if((lista2->next != NULL) && (strstr(lista2->info.code_orignal, string) != NULL)){
                            lista2 = lista2->next;
                        }else if((lista2->next != NULL)){
                            lista2 = lista2->next;
                            h--;
                        }else{
                            printf("esta\n\n");
                            lista2 = tab[posicao];
                            lista2 = lista2->next;
                            list_print(lista2);
                            j=1;
                        }
                    }
                }
                strcpy(buffer,lista2->info.palavra);
            }
        }
        printf("%d\n",j);
        printf("buffer : %s\n",buffer);
        printf("buffer3 : %s\n",buffer3);
        strcpy(bufferr,buffer3);
        if(!flag){
            int sizeint=0;
            for(int i=0;i<strlen(bufferr);i++) if(isdigit(bufferr[i])) sizeint++;
            bufferr[strlen(bufferr)-sizeint]= '\0';
            strcat(bufferr,buffer);
            strcat(bufferr," ");
        }
        gtk_label_set_text((GtkLabel*)label_user,bufferr);
    }else if(a==11){
        j=0;
        strcpy(buffer3,bufferr);
        gtk_label_set_text((GtkLabel*)label_user,buffer3);
        buffer[0]='\0';
    }else{
        j=0;
        buffer[i] = buffer2[0];
        buffer[i+1] = '\0';
        strcat(buffer3,buffer2);
        gtk_label_set_text((GtkLabel*)label_user,buffer3);
    }
}
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "en_US.UTF-8");
    char string[30], code[20];
    //int i = 0;
    long int posicao;

    FILE *fp = fopen("input.txt", "r");

    /*if (argc<2){
        printf("Argumentos insuficientes\n");
        return -1;
    }*/

    if (fp == NULL){
        printf("Problemas na leitura do ficheiro\n");
        return -1;
    }

    for(int i=2; i<99999; i++) tab[i] = list_new();
    wint_t wc;
    char *token;
    char ch;
    int u=0;
    while((wc=fgetwc(fp))!=WEOF){
        char line[200] = {'\0'};
        int i=0;
        wc = towlower(wc);
        ch = convertch(wc);
        if(ch!='*') {
            line[i++] = ch;
        }
        u++;
        while(((wc=fgetwc(fp))!='\n' && wc !=WEOF)){
            wc = towlower(wc);
            ch = convertch(wc);
            if(ch!='*'){
                line[i++] = ch;
            }
        }
        if(!isdigit(line[0]) && !isdigit(line[1]) && !isdigit(line[2])){
            token = strtok(line, " ");
            if(token!=NULL && isalpha(*token)) aux(token,code,tab);
            while( token != NULL ) {
                token = strtok(NULL, " ");
                if(token!=NULL && isalpha(*token)) aux(token,code,tab);
            }
        }

    }
    //ver(tab);
    list_print(tab[32]);
    list_print(tab[33]);
    gchar* values[12] = { "1", "2", "3", "4", "5", "6","7", "8", "9","*", "0", "#"};
    gtk_init(&argc, &argv);
    buffer[0] = '\0';
    window= gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 5, 5);
    gtk_window_set_title(GTK_WINDOW(window), "Phone");
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);
    GtkWidget* vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,1);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    conteudo1=gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(vbox), conteudo1);
    label_user = gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(vbox), label_user, FALSE, FALSE, 5);
    grid= gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 2);
    //gtk_grid_set_col_spacing(GTK_GRID(grid), 2);
    int i = 0;
    int j = 0;
    int pos= 0;
    int num=0;
    for (i=0; i < 4; i++) {
        for (j=0; j < 3; j++) {
            num++;
            button= gtk_button_new_with_label(values[pos]);
            g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(button_clicked), num);
            gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1);
            pos++;
        }
    }
    gtk_container_add(GTK_CONTAINER(vbox), grid);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}