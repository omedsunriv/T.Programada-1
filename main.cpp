/* Programa creado por los estudiantes del ITCR: Víctor Sánchez y Yoel Apú
Su función es leer archivos de texto generados por shpdump de archivos con formato shp.
Es necesario instalar el shpdump y generar archivos de texto por medio de éste.
Después de leer estos archivos, se dibujan en la pantalla para poder observar los mapas
y tiene funciones para hacer zoom y pan.*/

//librerías y archivos importados
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <Fl/fl_ask.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Wizard.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Text_Display.H>
#include <fstream>
#include <string>
#include <locale>
/////////////////////////////
//variables globales
using namespace std;
Fl_Wizard* tab;//diferentes wizards para mostrar los dibujos
Fl_Double_Window* ventana;//la ventana principal
int cantZoom=9;//la cantidad de zoom
int* puntero = &cantZoom;
int posX=0;//la posición en el eje x donde va a estar el mapa
int* punterox = &posX;
int posY=0;//la posición en el eje y donde va a estar el mapa
int* punteroy = &posY;
string nomArchivo;// el nombre del archivo del mapa en formato txt
string* pArchivo = &nomArchivo; 
int inicioLimites=14;// en esta posición de el archivo de texto se declaran los límites de la figura
int maxX=0;//el máximo del X obtenido del archivo de texto
int maxY=0;//el máximo del Y obtenido del archivo de texto
int minX=0;//el mínimo del X obtenido del archivo de texto
int minY=0;//el mínimo del Y obtenido del archivo de texto
//////////////////////////////
//función para zoom
void zoomOut(){
     (*puntero)++;}//se incrementa la variable del zoom
void zoomIn(){
      (*puntero)--;}// se decrementa la variable del zoom
void moverDerecha(){//se incrementa la posición en X para moverse por el mapa
       (*punterox)+=10;}
void moverIzquierda(){//se decrementa la posición en Y para moverse por el mapa
      (*punterox)-=10;}
void moverArriba(){//se incrementa la posición en Y para moverse por el mapa
     (*punteroy)-=10;}
void moverAbajo(){//se decrementa la posición en X para moverse por el mapa
       (*punteroy)+=10;}
//////////////////////////////
////Lista con enlaces//
//elementos de la lista//
class Nodo
{
      public:
          int dato;
          Nodo* next;
          Nodo(int,Nodo*);
          };
      
      Nodo::Nodo(int pDato,Nodo* siguiente){
                dato=pDato;
                next=siguiente;}
//lista principal para almacenar las coordenadas, los vértices y las posiciones en que empieza un nuevo vértice
class Lista
{     
      public:
          Nodo* first;
          Nodo* last;
          Nodo* current;
          int size;          
          void append(int);
          void borrar();          
          int getValor(int);
          void moveToPos(int);
          Lista();
              };
              
      Lista::Lista(){
            current = new Nodo(NULL,NULL);
            last=current;first=current;size=0;}   
               
      void  Lista:: append (int pDato){
           last->next= new Nodo (pDato,NULL);           
           last = last -> next;
           size++;}
      
      int Lista::getValor(int pos){
           current=first;
           int i=0;
           while (i<pos){
                 current=current->next;
                 i+=1;}
           return current->dato;
                 }
      void Lista::moveToPos(int pos){
           current=first;
           int i=0;
           while (i<pos){
                 current=current->next;
                 i+=1;}}
      
      void  Lista:: borrar(){
           while (first!=NULL){
                 current=first;                 
                 first = first->next;                 
                 current=NULL;}
           current = new Nodo(NULL,NULL);
            last=current;first=current;size=0;           
           }
//Se inicializan las listas
Lista lista;//lista de coordenadas
Lista vertices;//lista de vértices
Lista mases; //lista de posiciones donde se debe comenzar una nueva línea 
///////////////////////////////////////
//Se crea la clase para poder dibujar
class ClaseCanvas : public Fl_Widget {
public:
     ClaseCanvas(int X,int Y,int W,int H,const char* L=0):Fl_Widget(X,Y,W,H,L) {
     }
     
     void draw() {     
    const char* file = nomArchivo.c_str();//se convierte el string del nombre nombre del archivo en const char* para que lo pueda leer     
    ifstream myfile (file);//se lee el archivo de texto
    vertices.borrar();//se elimina cualquier información guardada en la lista de vértices    
    lista.borrar();//se elimina cualquier información guardada en la lista de coordenadas 
    mases.borrar();//se elimina cualquier información guardada en la lista de mases 
    string linea;//la línea del archivo
    int i=0;//posición para saber en que línea se está leyendo    
    string temp="";//temporal para almacenar los dígitos de cada número 
    string temp2=""; //temporal2 para almacenar los dígitos de cada número
    int pos=0;//índice para conocer la parte del la línea que se lee       
    if (myfile.is_open())//comprueba que el archivo se pueda leer
  {
    while ( myfile.good() ){//se ejecuta mientras no se termine de leer todo el archivo                            
          if(i==0){ getline(myfile,linea);i+=1;} // no lee la primera línea y se la brinca
        //obtiene los límites mínimos y los guarda en variables               
        else if (i==2){
            getline(myfile,linea);
            while (linea[inicioLimites]!='.'){
                temp.push_back(linea[inicioLimites]);
                inicioLimites+=1;}
            minX = atoi(temp.c_str());
            while (linea[inicioLimites]!=','){
                  inicioLimites+=1;}
            inicioLimites+=1;
             while (linea[inicioLimites]!='.'){
                temp2.push_back(linea[inicioLimites]);
                inicioLimites+=1;}
            minY = atoi(temp2.c_str());       
            temp="";temp2="";
            inicioLimites=14;
            i+=1;}
    //obtiene los límites máximos y los guarda en variables 
        else if (i==3){
           getline(myfile,linea);
           while (linea[inicioLimites]!='.'){
                temp.push_back(linea[inicioLimites]);
                inicioLimites+=1;}
            maxX = atoi(temp.c_str());
            while (linea[inicioLimites]!=','){
                  inicioLimites+=1;}
            inicioLimites+=1;
             while (linea[inicioLimites]!='.'){
                temp2.push_back(linea[inicioLimites]);
                inicioLimites+=1;}
            maxY = atoi(temp2.c_str());       
            temp="";temp2="";
            i+=1;
            inicioLimites=14;
            }
        else{  //se obtienen las coordenadas y se guardan en el vector       
                getline(myfile,linea);
                if (linea.length()==0) i+=1;//se brinca las líneas en blanco
                // si encuentra una S entonces se encuentra en la línea donde están definidos los vértices
                //esta línea se recorre hasta obtener el vértice de la figura
                else if(linea[pos]=='S'){                     
                     while(linea[pos]!='='){                                                              
                        pos+=1;}                     
                     pos+=1;
                     while(linea[pos]!=','){
                        temp.push_back(linea[pos]);
                        pos+=1;}                       
                        vertices.append(atoi(temp.c_str()));
                        i+=1;
                        pos=0;
                        temp="";}
                //se obtienen las posiciones donde se inicia un nuevo vértice y las coordenadas 
                else{
                    while (linea[pos]!='('&&linea[pos]!='+'){
                          if (pos+1==linea.length()) break;
                          else if (linea[pos]=='B'||linea[pos]=='t')break;
                          else pos+=1;}
                    //si encuentra un + entonces inicia un nuevo vértice y almacena su posición para
                    //saber a cual coordenada le corresponde y lo guarda en una lista de "mases"
                    if (linea[pos]=='+'){mases.append(lista.size+1);}             
                    while (linea[pos]!='('){
                          if (pos+1==linea.length()) break;
                          else if (linea[pos]=='B'||linea[pos]=='t')break;
                          else pos+=1;}
                    pos+=1;
                    //revisa que sea una línea que contenga coordenadas, si no se la brinca
                    if (pos==linea.length()||!isdigit(linea[pos])||linea[pos]=='B'||linea[pos]=='t'){
                       i+=1;pos=0;}
                    //se obtienen las coordenadas
                    else {
                         //se guarda la posición en x                         
                         while (linea[pos]!='.'&&linea[pos]!=','){
                                 temp.push_back(linea[pos]);
                                 pos+=1;
                                 }
                           lista.append(atoi(temp.c_str()));                                                      
                           while (linea[pos]!=','){
                               pos+=1;}
                           pos+=1;
                           //se guarda la posición en Y                                                     
                           while (linea[pos]!='.'&&linea[pos]!=','){
                              temp2.push_back(linea[pos]);
                              pos+=1;}
                            lista.append(atoi(temp2.c_str()));                                  
                           temp="";temp2="";
                           i+=1;
                           pos=0;                                                 
                           }
                }
        }
    }
  }          
         //Fondo canvas        
         fl_color(FL_WHITE);
         //Tamaño canvas
         fl_rectf(0,25,w(),h());
         //Indices para accesar a las listas               
         int j=1;//empiezan en 1 porque el primer elemento está vacío (es la cabeza)
         int v=1;
         int m=1;
         int k=lista.size;         
         fl_color(FL_BLACK);//líneas negras
         //se dibuja         
         while (j<k){
               if (j+3>k)break;
               //si el vértice es 2 entonces no se usa más el último punto utilizado
               else if (vertices.getValor(v)<=2){
                    fl_line((lista.getValor(j)-minX)/(*puntero)+(*punterox),
                 ((maxY-lista.getValor(j+1))/(*puntero))+25+(*punteroy),
                 (lista.getValor(j+2)-minX)/(*puntero)+(*punterox),
                 ((maxY-lista.getValor(j+3))/(*puntero))+25+(*punteroy));
                 j+=4;
                 v+=1;}                 
               else{
                 //se revisa la lista de mases, si está vacía y se acceda ocurría un error, por eso se verifica que no esté vacía
                 if (mases.size==0){
                 fl_line((lista.getValor(j)-minX)/(*puntero)+(*punterox),
                 ((maxY-lista.getValor(j+1))/(*puntero))+25+(*punteroy),
                 (lista.getValor(j+2)-minX)/(*puntero)+(*punterox),
                 ((maxY-lista.getValor(j+3))/(*puntero))+25+(*punteroy));                                      
                 j+=2;
                 vertices.moveToPos(v);vertices.current->dato-=1;}
                 //si hay un más en esa posición, entonces no se dibuja nada y se salta la coordenada
                 else if (mases.getValor(m)==j+2){j+=2;
                 vertices.moveToPos(v);vertices.current->dato-=1;;m+=1;}
                 //se dibujan los vértices y se guarda la última coordenada dibuja para dibujar la próxima línea desde ese punto
                 else{             
                 fl_line((lista.getValor(j)-minX)/(*puntero)+(*punterox),
                 ((maxY-lista.getValor(j+1))/(*puntero))+25+(*punteroy),
                 (lista.getValor(j+2)-minX)/(*puntero)+(*punterox),
                 ((maxY-lista.getValor(j+3))/(*puntero))+25+(*punteroy));                                      
                 j+=2;
                 vertices.moveToPos(v);vertices.current->dato-=1;}
                                 }             
             }         
         }
};
//Se crea un canvas para poder dibujar en el
ClaseCanvas* canvas;
//diferentes funciones para los botones del zoom y del pan
void botonZoomOut(Fl_Widget*w,void*){
     zoomOut();
     tab->prev();
     tab->next(); }
void botonZoomIn(Fl_Widget*w,void*){
     zoomIn();
     tab->prev();
     tab->next(); }
void botonD(Fl_Widget*w,void*){
     moverDerecha();
      tab->prev();
     tab->next(); }
void botonI(Fl_Widget*w,void*){
     moverIzquierda();
      tab->prev();
     tab->next(); }
void botonAb(Fl_Widget*w,void*){
     moverArriba();
      tab->prev();
     tab->next(); }
void botonAr(Fl_Widget*w,void*){
     moverAbajo();
     tab->prev();
     tab->next();}
//funciones para los botones del menú     
void abrirAyuda(Fl_Widget*w,void*){          
          fl_message_title("AYUDA");fl_message("Escoja abrir y seleccione un archivo");       
          }
//se obtiene el nombre del archivo y se almacena en una variable
void abrirArchivo(Fl_Widget* w, void*){
     Fl_Native_File_Chooser explorador;explorador.filter("*.txt");          
     explorador.show();(*pArchivo)= explorador.filename();
     //se "refresca la pantalla"
     tab->prev();
     tab->next();
               }          
void Menu_CB_Quit(Fl_Widget* w, void*){
          exit(0);}
//función principal
int main() {
      //Se crea la ventana y el Wizard
      Fl_Double_Window ventana(600,500);
      tab = new Fl_Wizard(0,0,600,500);   
      //Tab # 1
      {Fl_Group *grupo = new Fl_Group(0,0,600,500);    
      Fl_Text_Buffer *buffer2 = new Fl_Text_Buffer();
      //se muestra en texto de bienvenida
      Fl_Text_Display *texto = new Fl_Text_Display(20, 20, 600, 440, "Bienvenidos");      
      texto->buffer(buffer2);
      ventana.resizable(*texto);
      texto->textsize(100);
      texto->textcolor(FL_BLUE);
      //se escribe el texto a ser mostrado      
      buffer2->text("\n"                
                 "  Shapefile\n"
                   "      Viewer");    
      Fl_Button *botonAyuda = new Fl_Button(70,0,70,25,"Ayuda"); botonAyuda->callback(abrirAyuda);
      Fl_Button *botonAyuda2 = new Fl_Button(0,0,70,25,"Abrir"); botonAyuda2->callback(abrirArchivo);
      grupo->end();}
       //Tab # 2
       {Fl_Group *grupo = new Fl_Group(0,0,600,500);
       // Se crean los diferentes botones      
      Fl_Button *botonzoomin = new Fl_Button(70,0,70,25,"Zoom In+");botonzoomin->callback(botonZoomIn);
      Fl_Button *botonzoomout = new Fl_Button(140,0,70,25,"Zoom Out-");botonzoomout->callback(botonZoomOut);
      Fl_Button *botonDer = new Fl_Button(210,0,70,25,"Derecha");botonDer->callback(botonD);
      Fl_Button *botonIzq = new Fl_Button(280,0,70,25,"Izquierda");botonIzq->callback(botonI);
      Fl_Button *botonArr= new Fl_Button(350,0,70,25,"Abajo");botonArr->callback(botonAr);
      Fl_Button *botonAba = new Fl_Button(420,0,70,25,"Arriba");botonAba->callback(botonAb);
      Fl_Button *botonAyuda2 = new Fl_Button(0,0,70,25,"Abrir"); botonAyuda2->callback(abrirArchivo);
      //se dibuja el canvas      
      canvas = new ClaseCanvas(0,25,600,500);    
      grupo->end();}
     //nombre de la ventana
     ventana.label("Shapefile Viewer");         
     ventana.end();
     //se muestra la ventana
     ventana.show();
     //comando predeterminado de FLTK para correr nuestro programa
     return(Fl::run());
}

