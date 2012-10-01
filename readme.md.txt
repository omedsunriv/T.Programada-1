#Vizualizador de Archivos Shpefile
Por Víctor Sánchez y Yoel Apú.

##INTRODUCCION

El proyecto realizado en un visualizador de información geográfica en formato shapefile. El mismo 
esta creado en lenguaje de programación de c++, y con ayuda de algunas de sus librerías.

###Descripción de Contenido a desplegar

Con este proyecto se podrán visualizar información geográfica en formato de shapefile. Dicha información podrán ser ciudades (polígonos), países (polígonos), calles (líneas), ríos (líneas), entre otros archivos.
El archivo puede cargar en cualquier momento un archivo en el formato indicado anteriormente. Por medio de un explorador que se encuentra en al parte superior izquierda de la pantalla.
El visualizador es capaz de representar información de líneas las cuales podrían representar ríos, calles, caminos.
Además de representar información de polígonos los cuales pueden representar países o ciudades.
También se pueden representar edificios importantes, entre otros archivos  en formato shafile.

####Definición de Estructuras de Datos

La estructura de datos que se quiso implementar para realizar la simplificación es un árbol binario.
Esta estructura permite acceso y actualización eficiente en grandes colecciones.
Esta compuesto de un conjunto finito de elementos llamados nodos. El primer elemento se conoce como raíz y esta compuesto por subárboles.
Dicha estructura se quería implementar para la simplificación, ya que con dicha estructura se permita  guardar en cada nivel del árbol un conjunto de coordenadas las cuales implicaban a su vez el nivel de simplificación.

#####Forma de Compilación ejecución y utilización

Para poder compilar esta aplicación se deben agregar todas las clases aun mismo proyecto además
de poseer la librería "shapefile C library", además de la librería FLTK 1.3.0 para c++, además del IDE
dev-c++.
Una vez compiladas las clases y cumplir con los requerimiento anteriores, pasamos al siguiente paso.

Se debe abrir el archivo atreves del explorador implementado en la parte superior izquierda de la pantalla y  seleccionar el archivo.
Una vez seleccionado el archivo, el mismo se desplegara en la pantalla. 
Después de que el archivo se desplego se tiene varias funcionalidades para manipular el archivo.
- Zoom in: para acercar el archivo y poder mayor detalle del mismo.
- Zoom out: para alejar el archivo y no ver tanto detalle.
- derecha: es para mover el archivo hacia la derecha.
-Izquierda: permite mover el archivo hacia la derecha.
- abajo: permite movilizar el archivo hacia abajo.
- arriba: permite mover el archivo hacia arriba.
Dichas funcionalidades son con el fin de que sea más fácil el visualizar el archivo desplegado.
Para salir de esta aplicación solo se debe dar clic en la esquina derecha, en la "X".

######Ejemplos como prueba

Como ejemplo para la prueba se puede utilizar archivos shafiles de la ciudad de San José, Costa Rica. Tales como distritos edificios, calles, calles principales entre otros archivos de esta región.

#######Limitaciones observadas y posibles mejoras.

1-Entre una de las principales limitaciones esta la poca información encontrada en bibliografías de consulta.
2-Entre las posibles mejoras se puede mencionar la implementación del árbol binario para simplificación.
3- Al abrir archivos shapefile de gran tamaño el programa puede dejar de funcionar.
4-Otra mejora puede ser lograr abrir archivos de más grande tamaño.
5- Por otro lado una mejora la cual podría ser implementada sería  la de utilizar el algoritmo de Ramer-Douglas-Peucker para la simplificación.







