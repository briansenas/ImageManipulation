/**
  * @file Image.h
  * @brief Fichero cabecera para la E/S y manipulación de imágenes
  *
  * Permite la E/S de archivos de tipo PGM,PPM y su manipulación.
  *
  */

#ifndef PRACTICA2_IMAGEN_H
#define PRACTICA2_IMAGEN_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**
  * @brief Tipo de imagen
  *
  * Declara una serie de constantes para representar los distintos tipos
  * de imágenes que se pueden manejar.
  *
  * @see LeerTipoImagen
  */
enum TipoImagen {IMG_DESCONOCIDO, IMG_PGM, IMG_PPM};

/**
 * @brief T.D.A Imágenes
 *
 * Una instance @e c del tipo de datos abstracto @c Imagen es
 * una representación de un conjunto de números en forma matricial
 * que puede ser interpretado.
 *
 * Lo representamos mediante un número dado de filas (nf) y número dado
 * de columnas (nc). Además, es necesario especificar el valor de alcance
 * máximo (max ~ 255).
 *
 * Para el caso de las imágenes con colores ( RGB ) tenemos que tener en cuenta
 * que los valores son tuplas de 0-max.
 *
 * Se especifica el tipo de Imagen ( PGM or PPM ) según la cabecera del archivo,
 * es decir, P5 o P6 respectivamente.
 * @see TipoImagen
 *
 * @author Brian Sena Simions 2ºB-B2.
 * @date Change when finished.
 */

class Imagen{
private:
    int filas, columnas;
    unsigned char** valores;
    TipoImagen tipo;
    ifstream archivo; //Para no tener que pasarlo como parámetro siempre

    /**
     * @brief Dado un archivo, podemos leer el tipo de imagen a trabajar.
     * @param f Archivo sobre el cual trabajamos.
     */
    void LeerTipo();

    /**
     * @brief Leemos las primeras líneas del archivo dónde se indica el valor
     * máximo, el número de filas y el número de columnas;
     * @return Succeso / error
     */
    bool LeerCabecera ();

    /**
    * @brief Lee una imagen de tipo PPM ( Tener en cuenta que tenemos que
     * multiplicar el nº de columnas por 3, ya que los valores son tuplas ).
    */
    void LeerImagenPPM();

    /**
    * @brief Leer una imagen de tipo PGM
    */
    void LeerImagenPGM();

    /**
     * @brief Leer el archivo ignorando los espacios en blanco que tenga.
     * @return
     */
    inline char SaltarSeparadores ();

    /**
     * @brief Calculamos el valor medio partiendo de una posicion de columnas dado
     * @param type 0 = red, 1 = green, 2 = blue
     * @return Media de valor del color indicado
     */
    inline double mediumValue(int type=0);

    /**
     * @brief Liberamos toda la memoria dinámica que hayamos reservado.
     */
    inline void HardReset();

public:

    /**
     * @brief Constructor sin parámetros para inicializar los valores a 0.
     * @return La instancia inicializada.
     */
    Imagen();

    /**
     * @brief Leemos datos de entrada desde el nombre de un archivo
     * @see setFile()
     * @param nombre Nombre del archivo que vamos a utilizar
     */
    Imagen(const char* nombre);

    /**
     * @brief Constructor de copia.
     * @param otro Imagen a copiar.
     * @return La instancia inicializada.
     */
    Imagen(const Imagen& otro);

    /**
     * @brief Constructor con parámetros para inicializar los valores a 0.
     * @pre nf y nc deben ser valores positivos.
     * @param nf Indica el número de filas de la matriz.
     * @param nc Indica el número de columnas de la matriz.
     * @return la instancia inicializada.
     */
    Imagen(int nf, int nc);

    /**
     * @brief Destructor de la clase, para liberar la memoria almacenada.
     */
    ~Imagen();

    /**
     * @brief Cambiamos el archivo sobre el que trabajamos y volvemos a leer los datos
     * @see LeerCabecera(), LeerImagenPPM(), LeerTipo()
     * @param nombre Nombre del archivo que vamos a utilizar.
     */
    void setFile(const char* nombre);

    /**
     * @brief Devuelve el número de filas utilizados.
     * @return Número de filas en uso.
     */
    const int num_filas();

    /**
     * @brief Devuelve el número de columnas utilizadas.
     * ( Devuelve el nº de columnas, no el nº de valores ( Tuplas en PPM ) )
     * @return Número de columnas en uso.
     */
    const int num_columnas();

    /**
     * @brief Asignar el valor "valor" al pixel ("nf,nc") de la imagen.
     * @pre nf y nc deben ser valores positivos y menores que el tamaño de
     * la matriz bidimensional. PD:(Esta función no funcionaría para los tipos
     * de colores si no escribimos tuplas de datos).
     * @param nf Fila a escribir.
     * @param nc Columna a escribir.
     * @param valor Nuevo valor de la posición dada.
     */
    void asigna_pixel(int nf, int nc,unsigned char valor);

    /**
     * @brief Devuelve el valor de la matriz en una posición dada.
     * @pre nf y nc deben ser valores positivos y menores que el tamaño de
     * la matriz bidimensional. Además, no se modifica ningún valor.
     * @param nf Fila a leer.
     * @param nc Columna a leer.
     * @return Valor en la posición dada.
     */
    unsigned char valor_pixel(int nf, int nc);

    /**
     * @brief Nos indica sobre que tipo de imagen trabajamos
     * @return TipoImagen Tipo de imagen sobre el que trabajamos
     */
    TipoImagen get_tipo();

    /**
     * @brief Funcion auxiliar para llamar a la funcion de escritura adecuada.
     * @param name Lugar/nombre de donde se guarda la imagen
     * @return succeso / error
     */
    bool EscribirImagen(const char* name);

    /**
    * @brief Escribe una imagen de tipo PPM
    * @return Si ha tenido éxito en la escritura.
    */
    bool EscribirImagenPPM(const char* nombre);

    /**
    * @brief Escribe una imagen de tipo PGM
    * @return Si ha tenido éxito en la escritura.
    */
    bool EscribirImagenPGM(const char* nombre);

    /**
     * @brief Añadimos una línea de color "valor" alrededor de la imagen
     * @note Todos tienen valor por defecto 0, en caso de que no se especifiquen
     * los paramétros 2,3 entonces aplicamos solo el primero como intensidad de gris
     * en las imagenes .PGM
     * @param width grosor del enmarcamiento
     * @param R cantidad de rojo del enmarcamiento
     * @param B cantidad de azul del enmarcamiento
     * @param G cantidad de verde del enmarcamiento
     */
    void Enmarcar(int width=1,int R=0, int G=0, int B=0);

    /**
     * @brief Debemos restar al valor máximo aquel valor en cada posición
     * de nuestra matriz de valores de imagen. ( Max - valor ).
     */
     void Negativo();

    /**
     * @brief Debemos superponer los valores RGB ( tuplas ) cada cual con su constante para
     * tener como resultado una imagen de tipo PGM ( en escala de grises ).
     * @note const R = 0.2989, const G = 0.579 and const B = 0.114; Tal que la
     * suma entre esos valores es menor o igual a 255 ( valor máximo ).
     * @return succeso / error
     */
    bool ConvertTo_Gray();

    /**
     * @brief Debemos reajustar los valores de la imagen para que esté contenido
     * entre los intervalos T1 y T2
     * @param T1 Extremo inferior
     * @param T2 Extremo superior
     */
    void EscalaValores(int T1, int T2);

    /**
     * @brief Si la imagen tiene un nivel de gris menor que nuestro umbral
     * (o al revés si se prefiere) se deja el valor y en caso contrario se pone
     * a 0 ( o a maxvalue);
     * @note Calculamos un Umbral T1 con el valor medio de una Imagen. Luego creamos dos
     * Imagenes, una con valores inferiores y otra con valores superiores. Volvemos a calcular
     * la media de ambas y el nuevo valor de T1 es la media de las medias. Ejecutamos este algoritmo
     * recursivamente hasta que T(t+1)-T(t) <= epsilon.
     * @see mediumValue()
     *
     */
    void EscalaAutomatica();

    /**
     * @brief creamos una matriz cuadrada de dimensiones 2N-1 mediante interpolación de columnas
     * y luego interpolación de columnas.
     * @note Por interpolar entendemos que debemos calcular la media entre los valores y poner esta media
     * entre ellos. Además, cabe recordar que en caso de las imagenes con colores tenemos que tener en cuenta
     * un offset entre los respectivos colores de valor = 3. R G B R1 G1 B1....Rn Gn Bn.
     * @param x1 Punto inicial del zoom respecto del eje de ordenadas
     * @param y1 Punto inicial del zoom respecto del eje de abcisas
     * @param x2 Punto final del zoom respecto del eje de ordenadas
     * @param y2 Punto final del zoom respecto del eje de abcisas
     * @return succeso / error
     */
    bool Zoom(int x1,int y1, int x2, int y2);

    /**
     * @brief Debemos hacer una reducción de tamaño n sobre nuestras imagenes.
     * Para ello calculamos la media de n valores sumados, para todos los valores.
     * @note Debemos tener cuidado con el overflow de los bytes, ya que max = 255.
     * Para ello utilizamos un arr de <int> que luego convertimos en <byte> tras realizar la
     * media de los valores sumados.
     * @param n Tamaño de la reducción
     */
    void ReducirPorN(int nf, int nc=0);

    /**
     * @brief Reducimos a un tamaño de pixel dado, hacemos uso de ReducirPorN
     * @see ReducirPorN()
     * @param sizeRow Número de filas de la imagen resultante.
     * @param sizeCol Número de columnas de la imagen resultante.
     */
    void ReducirA(int sizeRow,int sizeCol=0);

    /**
     * @brief Aplicamos una transformación lineal sobre los valores de la imagen
     * @note t(z) = min + ((max-min)/(b-a))*(z-a); Donde a y b son los valores máx y min
     * de la imagen actual.
     * @param min Nuevo minimo de la imagen
     * @param max Nuevo maximo de la imagen
     */
    void LinearContrast(int min, int max);

    /**
     * @brief Debemos ir transformando linealmente los valores durante n_iter iteraciones aplicando
     * para ello la fórmula (1-x)origen + xDestino. Utilizamos string para poder ir mmodificando el
     * nombre de la imagen de salida cada paso.
     * @param otro Imagen Destino.
     * @param nombre
     * @param n_iter Número de Iteraciones .
     * @return succeso / error
     */
    bool Morphing( Imagen& otro, string nombre,int n_iter);

    /**
     * @brief Cambiamos el último bit de cada byte para que sea los bits de cada byte
     * del mensaje que enviamos. Utilizamos operaciones booleanas.
     * @param msg Mensaje a codificar
     */
    void Codificar(string msg);

    /**
     * @brief Leyemos los últimos bits de cada byte para ir formulando nuestro mensaje
     * codificado. Utilizamos operaciones booleanas.
     * @param msg String donde almacenaremos el resultado de la decodificación
     */
    void Decodificar(string &msg);
};

#endif //PRACTICA2_IMAGEN_H
