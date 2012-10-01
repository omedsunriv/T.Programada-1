#Vizualizador de Archivos Shpefile
Por V�ctor S�nchez y Yoel Ap�.

##INTRODUCCION

El proyecto realizado en un visualizador de informaci�n geogr�fica en formato shapefile. El mismo 
esta creado en lenguaje de programaci�n de c++, y con ayuda de algunas de sus librer�as.

###Descripci�n de Contenido a desplegar

Con este proyecto se podr�n visualizar informaci�n geogr�fica en formato de shapefile. Dicha informaci�n podr�n ser ciudades (pol�gonos), pa�ses (pol�gonos), calles (l�neas), r�os (l�neas), entre otros archivos.
El archivo puede cargar en cualquier momento un archivo en el formato indicado anteriormente. Por medio de un explorador que se encuentra en al parte superior izquierda de la pantalla.
El visualizador es capaz de representar informaci�n de l�neas las cuales podr�an representar r�os, calles, caminos.
Adem�s de representar informaci�n de pol�gonos los cuales pueden representar pa�ses o ciudades.
Tambi�n se pueden representar edificios importantes, entre otros archivos  en formato shafile.

####Definici�n de Estructuras de Datos

La estructura de datos que se quiso implementar para realizar la simplificaci�n es un �rbol binario.
Esta estructura permite acceso y actualizaci�n eficiente en grandes colecciones.
Esta compuesto de un conjunto finito de elementos llamados nodos. El primer elemento se conoce como ra�z y esta compuesto por sub�rboles.
Dicha estructura se quer�a implementar para la simplificaci�n, ya que con dicha estructura se permita  guardar en cada nivel del �rbol un conjunto de coordenadas las cuales implicaban a su vez el nivel de simplificaci�n.

#####Forma de Compilaci�n ejecuci�n y utilizaci�n

Para poder compilar esta aplicaci�n se deben agregar todas las clases aun mismo proyecto adem�s
de poseer la librer�a "shapefile C library", adem�s de la librer�a FLTK 1.3.0 para c++, adem�s del IDE
dev-c++.
Una vez compiladas las clases y cumplir con los requerimiento anteriores, pasamos al siguiente paso.

Se debe abrir el archivo atreves del explorador implementado en la parte superior izquierda de la pantalla y  seleccionar el archivo.
Una vez seleccionado el archivo, el mismo se desplegara en la pantalla. 
Despu�s de que el archivo se desplego se tiene varias funcionalidades para manipular el archivo.
- Zoom in: para acercar el archivo y poder mayor detalle del mismo.
- Zoom out: para alejar el archivo y no ver tanto detalle.
- derecha: es para mover el archivo hacia la derecha.
-Izquierda: permite mover el archivo hacia la derecha.
- abajo: permite movilizar el archivo hacia abajo.
- arriba: permite mover el archivo hacia arriba.
Dichas funcionalidades son con el fin de que sea m�s f�cil el visualizar el archivo desplegado.
Para salir de esta aplicaci�n solo se debe dar clic en la esquina derecha, en la "X".

######Ejemplos como prueba

Como ejemplo para la prueba se puede utilizar archivos shafiles de la ciudad de San Jos�, Costa Rica. Tales como distritos edificios, calles, calles principales entre otros archivos de esta regi�n.

#######Limitaciones observadas y posibles mejoras.

1-Entre una de las principales limitaciones esta la poca informaci�n encontrada en bibliograf�as de consulta.
2-Entre las posibles mejoras se puede mencionar la implementaci�n del �rbol binario para simplificaci�n.
3- Al abrir archivos shapefile de gran tama�o el programa puede dejar de funcionar.
4-Otra mejora puede ser lograr abrir archivos de m�s grande tama�o.
5- Por otro lado una mejora la cual podr�a ser implementada ser�a  la de utilizar el algoritmo de Ramer-Douglas-Peucker para la simplificaci�n.







