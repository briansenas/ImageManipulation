/**
 * @file Imagen.cpp
 * @brief Fichero con las definiciones de las funciones.
 *
 * Permite la E/S de archivos de tipo PGM, PPM y su manipulación
 */

// _____________________________________________________________________________
//typedef unsigned char unsigned char;
#include "Imagen.h"
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
// _____________________________________________________________________________

Imagen::Imagen(){
    this->filas = 0;
    this->columnas = 0;
    this->valores = 0;
}

// _____________________________________________________________________________

Imagen::Imagen(const char * nombre){
    this->setFile(nombre);
}

// _____________________________________________________________________________

Imagen::Imagen(const Imagen& otro){
    this->tipo = otro.tipo;
    this->filas = otro.filas;
    this->columnas = otro.columnas;
    this->valores = new unsigned char*[this->filas];
    for(int i=0;i<this->filas;i++){
        this->valores[i] = new unsigned char[this->columnas];
        for(int j=0;j<this->columnas;j++){
            this->valores[i][j] = otro.valores[i][j];
        }
    }
}

// _____________________________________________________________________________

Imagen::Imagen(int nf,int nc){
    this->filas = nf;
    this->columnas = nc;
    this->valores = new unsigned char*[this->filas];
    for(int i=0;i<this->filas;i++){
        this->valores[i] = new unsigned char[this->columnas];
    }
}

// _____________________________________________________________________________

void Imagen::setFile(const char* nombre){
    this->archivo.close();
    this->archivo.open(nombre);
    this->LeerTipo();
    this->LeerCabecera();
    if(this->tipo==IMG_PGM)
        this->LeerImagenPGM();
    else if(this->tipo==IMG_PPM)
        this->LeerImagenPPM();
    this->archivo.close();
}

// _____________________________________________________________________________

const int Imagen::num_filas(){
    return this->filas;
}

// ____________________________________________________________________________

const int Imagen::num_columnas(){
    int offset = 1;
    if (this->tipo == IMG_PPM)
        offset = 3;
    return this->columnas/offset;
}

// ____________________________________________________________________________

void Imagen::asigna_pixel(int nf, int nc, unsigned char valor){
    if(nf>=0 && nf<this->filas && nc>=0 && nc<this->columnas)
        this->valores[nf][nc] = valor;
}

// ____________________________________________________________________________

unsigned char Imagen::valor_pixel(int nf,int nc){
    unsigned char result = -1;
    if(nf>0 && nf<this->filas && nc>0 && nc<this->columnas)
        result = this->valores[nf][nc];
    return result;
}

// ____________________________________________________________________________

TipoImagen Imagen::get_tipo(){
    return this->tipo;
}

// ___________________________Leer tipo de Imagen__________________________________

void Imagen::LeerTipo(){
    char c1,c2;
    TipoImagen res= IMG_DESCONOCIDO;

    if (this->archivo){
        c1=this->archivo.get();
        c2=this->archivo.get();
        if (this->archivo && c1=='P')
            switch (c2) {
                case '5': res= IMG_PGM; break;
                case '6': res= IMG_PPM; break;
                default: res= IMG_DESCONOCIDO;
            }
    }
    this->tipo = res;
}

// ___________________________Filtrar ruidos de información__________________________________

char Imagen::SaltarSeparadores (){
    char c;
    do{
        c= this->archivo.get();
    } while (isspace(c));
    this->archivo.putback(c);
    return c;
}

// ___________________________Leer Cabeceras y preparar atributos__________________________________

bool Imagen::LeerCabecera (){
    string linea; int valormax;
    while (SaltarSeparadores()=='#')
        getline(this->archivo,linea);
    this->archivo >> this->columnas >> this->filas >> valormax;

    if (/*str &&*/ this->archivo && this->filas>0 && this->filas<5000 &&
                    this->columnas>0 && this->columnas<5000){
        this->archivo.get(); // Saltamos separador
        return true;
    }
    else
        return false;
}

// ___________________________Leer ImagenTipo PGM__________________________________

void Imagen::LeerImagenPGM(){
    if (this->tipo == IMG_PGM){
        unsigned char** resultado = new unsigned char*[this->filas];
        for (int i = 0; i < this->filas; i++) {
            resultado[i] = new unsigned char[this->columnas];
            this->archivo.read(reinterpret_cast<char *>(resultado[i]), this->columnas);

        }
        this->valores = resultado;
    }else{
        this->valores = 0;
    }
}

// ___________________________Leer ImagenTipo PPM__________________________________

void Imagen::LeerImagenPPM (){
    if (this->tipo == IMG_PPM){
        this->columnas *= 3;
        unsigned char** resultado = new unsigned char*[this->filas];
        for (int i = 0; i < this->filas; i++) {
            resultado[i] = new unsigned char[this->columnas];
            this->archivo.read(reinterpret_cast<char *>(resultado[i]), this->columnas);
        }
        this->valores = resultado;
    }else{
        this->valores = 0;
    }
}

// ___________________________Método para distinguir tipos y evitar errores__________________________________

bool Imagen::EscribirImagen(const char* nombre){
    bool resultado = false;
    if(this->tipo==IMG_PGM)
        resultado = this->EscribirImagenPGM(nombre);
    else
       resultado = this->EscribirImagenPPM(nombre);
    return resultado;
}

// ___________________________Escribir Imagen con un nombre dado__________________________________

bool Imagen::EscribirImagenPPM (const char* nombre){
    ofstream f(nombre);
    bool res = false;
    if(this->tipo==IMG_PPM) {
        int num_columnas = this->columnas / 3; //Escribimos el nº de columnas, no de tuplas.
        res = true;
        if (f) {
            f << "P6" << endl;
            f << num_columnas << ' ' << this->filas << endl;
            f << 255 << endl;
            for (int i = 0; i < this->filas; i++) {
                f.write(reinterpret_cast<const char *>(this->valores[i]), this->columnas);
            }
            if (!f)
                res = false;
        }
    }
    return res;
}

// ___________________________Escribir Imagen con un nombre dado__________________________________

bool Imagen::EscribirImagenPGM (const char* nombre){
    ofstream f(nombre);
    bool res = false;
    if(this->tipo == IMG_PGM) {
        res = true;
        if (f) {
            f << "P5" << endl;
            f << this->columnas << ' ' << this->filas << endl;
            f << 255 << endl;
            for (int i = 0; i < this->filas; i++) {
                f.write(reinterpret_cast<const char *>(this->valores[i]), this->columnas);
            }
            if (!f)
                res = false;
        }
    }
    return res;
}

// ___________________________Liberamos Memoria allocated_________________________________

void Imagen::HardReset(){
    for(int i=0;i<this->filas;i++){
        delete [] this->valores[i];
    }
    delete [] this->valores;
}

// ___________________________Enmarcar las fotos__________________________________

void Imagen::Enmarcar(int width,int R,int G,int B){
    int offset = 1;
    if( this->tipo == IMG_PPM)
        offset = 3;

    int sizeRow = this->filas + 2*width;
    int sizeCol = this->columnas + 2*offset*width;

    unsigned char** resultado = new unsigned char*[sizeRow];
    for(int i=0;i<sizeRow;i++){
        resultado[i] = new unsigned char[sizeCol];
        for(int j=0;j<sizeCol;j++){
            if(i < width || i >= sizeRow-width || j < width*offset  || j >= sizeCol-width*offset) {
                if (j % offset == 0) //En caso de tipo PGM siempre se cumple ( entonces solo hay 1 color de 0-maxvalue)
                    resultado[i][j] = R;
                else if(j % offset == 1)
                    resultado[i][j] = G;
                else if(j % offset == 2)
                    resultado[i][j] = B;
            }
            else
                resultado[i][j] = this->valores[i-width][j-width*offset];
        }
    }

    this->HardReset();
    this->valores = resultado;
    this->filas = sizeRow;
    this->columnas = sizeCol;

}

// ___________________________Invertir Intesidad de Colores__________________________________

void Imagen::Negativo(){
    for (int i = 0; i < this->filas; i++) {
        for (int j = 0; j < this->columnas; j++) {
            this->valores[i][j] = 255 - this->valores[i][j];
        }
    }
}

// ___________________________Conversión de Precisión a Gris__________________________________

bool Imagen::ConvertTo_Gray(){
    bool res = false;
    if(this->tipo==IMG_PPM){
        this->tipo=IMG_PGM;
        res = true;
        int cont = 0;
        unsigned char** resultado = new unsigned char*[this->filas];
        for(int i=0;i<this->filas;i++){
            resultado[i] = new unsigned char[this->columnas/3];
            for(int j=3;j<this->columnas;j+=3){
                resultado[i][cont] =    0.2989*this->valores[i][j-3]+
                                        0.579*this->valores[i][j-2] +
                                        0.114*this->valores[i][j-1] ;
                cont++;
            }
            cont = 0;
        }
        this->columnas /= 3;
        this->HardReset();
        this->valores = resultado;
    }
    return res;
}

// ___________________________Umbral de Intensidad de Color__________________________________

void Imagen::EscalaValores(int T1, int T2){
    int offset = 1;
    if(this->tipo==IMG_PPM)
        offset = 3;

    for(int i=0;i<this->filas;i++) {
        for (int x = 0; x < offset; x++) {
            for (int j = x; j < this->columnas; j+=offset) {
                if (this->valores[i][j] < T1)
                    this->valores[i][j] = T1;
                else if (this->valores[i][j] > T2)
                    this->valores[i][j] = T2;
            }
        }
    }
}

// ___________________________Media de intensidad de Color__________________________________

double Imagen::mediumValue(int type){
    int offset = 1;
    if(this->tipo==IMG_PPM)
        offset = 3;
    double sum = 0;
    for(int i=0;i<this->filas;i++){
        for(int j=type;j<this->columnas;j+=offset)
            sum += (int)this->valores[i][j];
    }
    return sum/(this->filas*this->columnas);
}

// ___________________________Escala Automática de Colores__________________________________

void Imagen::EscalaAutomatica(){
    int offset = 1;
    if (this->tipo==IMG_PPM)
        offset = 3;

    for(int x=0;x<offset;x++) {
        double mu1, mu2, error = 0.001;
        double T, T1 = this->mediumValue(x);
        Imagen I_1(*this), I_2(*this);
        I_1.EscalaValores(0, T1);
        I_2.EscalaValores(T1, 255);
        do {
            T = T1;
            mu1 = I_1.mediumValue(x);
            mu2 = I_2.mediumValue(x);
            T1 = (mu1 + mu2) / 2;
            I_1.EscalaValores(0, T1);
            I_2.EscalaValores(T1, 255);
        } while (fabs(T1 - T) >= error);

        for (int i = 0; i < this->filas; i++) {
            for (int j = x; j < this->columnas; j += offset) {
                if (this->valores[i][j] <= T1)
                    this->valores[i][j] = 0;
            }
        }
    }
}

// ___________________________Realizar zoom sobre coordenadas dadas__________________________________

bool Imagen::Zoom(int x1,int y1, int x2, int y2) {
    bool result = false;

    int offset = 1;
    if (this->tipo == IMG_PPM)
        offset = 3;

    x1 = x1 * offset;
    x2 = x2 * offset;

    if (x1 >= 0 && x2 >= 0 && y1 >= 0 && y2 >= 0 &&
        x1 < x2 && x2 <= this->columnas && y1 < y2 && y2 <= this->filas) {
        result = true;

        int sizeCol = 2 * (x2 - x1) - 1;
        int sizeRow = 2 * (y2 - y1) - 1;
        unsigned char **resultado = new unsigned char* [sizeRow];

        for(int i = 0; i < sizeRow; i++){
            resultado[i] = new unsigned char[sizeCol];
        }

        /*Interpolamos entre columnas primero ( en caso de los colores hay que distinguir entre los distintos colores
         * haciendo un salto de 3 ( offset ) entre los valores.
         * */
        int f = 0, c = 0;
        for (int i = y1; i < y2; i++) {
                c = 0;
                for (int j = x1; j < x2; j++) {
                    if (j != x1 && c%offset==0) {
                        for(int x=0;x<offset;x++) {
                            resultado[f][c] = (this->valores[i][j - offset + x] + this->valores[i][j + x]) / 2;
                            c++;
                        }
                    }
                    resultado[f][c] = this->valores[i][j];
                    c++;
                }
                f += 2; //Dejamos hueco para la interpolación por filas.
            }

        //Finalmente debemos hacer una interpolación de las filas;
        f = 1;
        for (int i = 1; i < sizeRow-1; i+=2) {
            for (int j = 0; j < sizeCol; j++) {
                resultado[f][j] = (resultado[i - 1][j] + resultado[i+1][j]) / 2;
            }
            f+=2;
        }

        this->HardReset();
        this->valores = resultado;
        this->filas = sizeRow;
        this->columnas = sizeCol;
    }
    return result;
}

// ___________________________Reducir Una Imagen a un tamaño dado__________________________________

void Imagen::ReducirA(int sizeRow, int sizeCol){
    if(sizeCol==0)
        sizeCol = sizeRow;

    int nc = ceil((this->columnas / sizeCol));
    int nf = ceil((this->filas / sizeRow));

    this->ReducirPorN(nf,nc);
    this->filas = sizeRow;
    this->columnas = sizeCol;
}

// ___________________________Reducir Por un factor de reducción__________________________________

void Imagen::ReducirPorN(int nf, int nc){
    int offset = 1;
    if (this->tipo==IMG_PPM)
        offset = 3;

    if(nc==0)
        nc = nf;

    int checkRow, checkCol;
    bool modf = false, modc = false;

    int sizeCol = this->columnas / nc;
    if(this->columnas % nc != 0){
        checkCol = sizeCol;
        sizeCol+=1;
        modc = true;
    }
    int sizeRow = this->filas / nf;
    if(this->filas % nf != 0){
        checkRow = sizeRow;
        sizeRow += 1;
        modf = true;
    }

    int** resultado = new int*[sizeRow];
    for(int i=0;i<sizeRow;i++){
        resultado[i] = new int[sizeCol];
        for(int j=0;j<sizeCol;j++){
            resultado[i][j]=0;
        }
    }

    for(int i=0;i<this->filas;i++){
        for(int z=0;z<offset;z++) {
            for (int j = z; j < this->columnas; j+=offset) {
                resultado[i / nf][j / nc] += (int) this->valores[i][j];
            }
        }
    }

    this->HardReset();
    int sz = nf*nc;
    this->valores = new unsigned char*[sizeRow];
    for(int i=0;i<sizeRow;i++){
        this->valores[i] = new unsigned char[sizeCol];
        if(i>checkRow && modf)
            sz = sz / nf * this->filas % nf;
        for(int j=0;j<sizeCol;j++){
            if(i>checkCol && modc)
                sz = sz / nc * this->columnas % nc;
            resultado[i][j] = resultado[i][j]/sz + 0.5;
            this->valores[i][j] = resultado[i][j];
        }
    }

    //Liberamos memoria, ya que hemos hecho una copia real del valor, no de referencia.
    //Además en la conversión de int a unsigned char, dejamos 3 unsigned char perdidos....
    for(int i=0;i<sizeRow;i++)
        delete [] resultado[i];
    delete [] resultado;

    this->filas = sizeRow;
    this->columnas = sizeCol;
}

// ___________________________Contraste Lineal entre 2 valores__________________________________

void Imagen::LinearContrast(int min,int max){
    int offset = 1;
    if(this->tipo==IMG_PPM)
        offset = 3;
    double a = 0, b = 255;
    double valor = 0;
    double diff = (max - min) / (b - a);
    for(int x=0;x<offset;x++) {
        for(int i=0;i<this->filas;i++){
            for(int j=x;j<this->columnas;j+=offset){
                valor = (min + diff*(this->valores[i][j]-a));
                this->valores[i][j] = (unsigned char)((int)valor);
            }
        }
    }
}

// ___________________________Transformación lineal entre imagenes__________________________________

bool Imagen::Morphing(Imagen& otro, string nombre, int n_iter){
    bool result = false;
    if(this->tipo == otro.tipo) {
        result = true;
        string type = ".pgm";
        if (this->tipo == IMG_PPM) {
            type = ".ppm";
        }

        //Comprobamos que son del mismo tamaño.
        if(this->filas >= otro.filas && this->columnas >= otro.columnas)
            this->ReducirA(otro.filas,otro.columnas);
        else if(this->filas > otro.filas && this->columnas < otro.columnas) {
            this->ReducirA(otro.filas, this->columnas);
            otro.ReducirA(otro.filas,this->columnas);

        }
        else if(this->filas < otro.filas && this->columnas > otro.columnas){
            this->ReducirA(this->filas, otro.columnas);
            otro.ReducirA(this->filas,otro.columnas);
        }
        else{
            otro.ReducirA(this->filas,this->columnas);
        }

        //Creamos la Imagen resultado, y vamos guardando los cambios cada iteración.
        Imagen resultado(*this);
        float factor = 0; string donde;
        for(int x=0;x<=n_iter;x++){
            if(x!=0)
                factor += 1.0/(n_iter*1.0);
            for(int i=0;i<this->filas;i++){
                for(int j=0;j<this->columnas;j++){
                    resultado.asigna_pixel(i,j,(1-factor)*this->valores[i][j] + factor*otro.valores[i][j]);
                }
            }
            donde = nombre +"Iter" + to_string(x) + type;
            resultado.EscribirImagenPGM(donde.c_str());
        }
    }
    return result;
}

// ___________________________Codificar Mensaje Oculto__________________________________

void Imagen::Codificar(string msg){
    int k = 0, cont = 0, len = msg.length();
    bool run = true;
    for(int i=0;i<this->filas && run;i++){
        for(int j=0;j<this->columnas && run;j++){
            this->valores[i][j] = this->valores[i][j] & 254; // Ultimo bit a 0
            this->valores[i][j] = this->valores[i][j] | (((unsigned char)msg[k])>> 7); //Añadimos ultimo bit
            msg[k] = msg[k] << 1;
            cont++;
            if(k>len) { //En caso
               run = false;
            }
            if(cont == 8) {
                cont = 0;
                k+=1;
            }
        }
    }
}

// ___________________________Decodificar Mensaje Oculto__________________________________

void Imagen::Decodificar(string& msg){
    msg = "";
    unsigned char a = 0, b = 0; int s = 7;
    for(int i=0;i<this->filas;i++){
        for(int j=0;j<this->columnas;j++){
            b = this->valores[i][j] & 1; // Cogemos un unsigned char de todo a 0 excepto el ultimo
            a = a | ( b << s); //Movemos el ultimo bit s posiciones a la izquierda y lo sumamos
            s--;
            if(s<0){
                s = 7;
                msg += a; //Una vez sumado los 8 bits, tenemos nuestro char
                a = 0;
            }
        }
    }
}

// ___________________________Destructor de Atributos__________________________________

Imagen::~Imagen(){
    this->archivo.close();
    this->HardReset();
    this->filas = 0;
    this->columnas = 0;
}

// ____________________________________________________________________________
/* Fin Fichero: Imagen.cpp */
