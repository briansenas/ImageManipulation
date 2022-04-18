#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Imagen.h"

using namespace std;

int main() {
    cout << "\tPrueba de Enmarcar en Blanco a vacas.pgm, ./resultados/EnmarcarVacas.pgm" << endl;
    Imagen ejemplo("datos/vacas.pgm");
    ejemplo.Enmarcar(5, 255); // this white
    ejemplo.EscribirImagen("resultados/EnmarcarVagas.pgm");

    cout << "\tPrueba de enmarcar en Morado a flores.ppm, ./resultados/EnmarcarFlores.ppm" << endl;
    Imagen ejemplo1("datos/flores.ppm");
    ejemplo1.Enmarcar(50,125,0,125); //this is purple
    ejemplo1.EscribirImagen("resultados/EnmarcarFlores.ppm");

    cout << "\tPrueba de Negativo en cameraman.pgm, ./resultados/NegativoGris.pgm" << endl;
    Imagen ejemplo2("datos/cameraman.pgm");
    ejemplo2.Negativo();
    ejemplo2.EscribirImagen("resultados/NegativoGris.pgm");

    cout << "\tPrueba de Negativo en alhambra.ppm, ./resultados/NegativoColor.ppm" << endl;
    Imagen ejemplo3("datos/alhambra.ppm");
    ejemplo3.Negativo();
    ejemplo3.EscribirImagen("resultados/NegativoColor.ppm");

    cout << "\tPrueba de Convertir a gris de mandrill.ppm, ./resultados/ConvertirGris.ppm" << endl;
    Imagen ejemplo4("datos/mandrill.ppm");
    ejemplo4.ConvertTo_Gray();
    ejemplo4.EscribirImagen("resultados/ConvertirGris.pgm");

    cout << "\tPrueba de Implantar Escala de valores 100-170, ./resultados/EscalaParametroGris.pgm" << endl;
    Imagen ejemplo5("datos/castillo.pgm");
    ejemplo5.EscalaValores(100,170);
    ejemplo5.EscribirImagen("resultados/EscalaParametroGris.pgm");

    cout << "\tPrueba de Implantar Escala de valores 100-170, ./resultados/EscalaParametroColor.ppm" << endl;
    Imagen ejemplo6("datos/cir255.ppm");
    ejemplo6.EscalaValores(100,170);
    ejemplo6.EscribirImagen("resultados/EscalaParametroColor.ppm");

    cout << "\tPrueba de Escala automatica en board.pgm, ./resultados/EscalaAutomaticaGris.pgm" << endl;
    Imagen ejemplo7("datos/board.pgm");
    ejemplo7.EscalaAutomatica();
    ejemplo7.EscribirImagen("resultados/EscalaAutomaticaGris.pgm");

    cout << "\tPrueba de Escala automatica en peppers.ppm, ./resultados/EscalaAutomaticaColor.ppm" << endl;
    Imagen ejemplo8("datos/peppers.ppm");
    ejemplo8.EscalaAutomatica();
    ejemplo8.EscribirImagen("resultados/EscalaAutomaticaColor.ppm");

    cout << "\tPrueba de hacer zoom a vacas.pgm, ./resultados/ZoomGris.pgm" << endl;
    Imagen ejemplo9("datos/vacas.pgm");
    ejemplo9.Zoom(0,0,ejemplo9.num_columnas(),ejemplo9.num_filas());
    ejemplo9.EscribirImagen("resultados/ZoomGris.pgm");

    cout << "\tPrueba de hacer zoom a flores.ppm ./resultados/ZoomColor.ppm" << endl;
    Imagen ejemplo10("datos/flores.ppm");
    ejemplo10.Zoom(0,0,ejemplo10.num_columnas()/2,ejemplo10.num_filas()/2);
    ejemplo10.EscribirImagen("resultados/ZoomColor.ppm");

    cout << "\tPrueba de crear logo para saturno.ppm,  ./resultados/LogoSimetricoGris.pgm" << endl;
    Imagen ejemplo11("datos/saturno.pgm");
    ejemplo11.ReducirA(ejemplo11.num_filas()/2,ejemplo11.num_columnas()/2);
    ejemplo11.EscribirImagenPGM("resultados/LogoSimetricoGris.pgm");

    cout << "\tPrueba de Reducir por N (Asimétrico reducción {5,2}) para saturno.ppm,  ./resultados/LogoASimetricoGris.pgm" << endl;
    Imagen ejemplo12("datos/saturno.pgm");
    ejemplo12.ReducirPorN(5,2);
    ejemplo12.EscribirImagenPGM("resultados/LogoASimetricoGris.pgm");

    cout << "\tPrueba de Reducir por N para alhambra.ppm, ./resultados/LogoColor.ppm" << endl;
    Imagen ejemplo13("datos/alhambra.ppm");
    ejemplo13.ReducirPorN(2);
    ejemplo13.EscribirImagenPPM("resultados/LogoColor.ppm");

    cout << "\tPrueba de constraste lineal (50-200) en vacas.pgm, ./resultados/CL_Gris.pgm" << endl;
    Imagen ejemplo14("datos/vacas.pgm");
    ejemplo14.LinearContrast(50,200);
    ejemplo14.EscribirImagen("resultados/CL_Gris.pgm");

    cout << "\tPrueba de contraste lineal (30-230) en flores.ppm, ./resultados/CL_Color.ppm" << endl;
    Imagen ejemplo15("datos/flores.ppm");
    ejemplo15.LinearContrast(30,230);
    ejemplo15.EscribirImagen("resultados/CL_Color.ppm");

    cout << "\tPrueba esteganografia en gal.ppm, ./resultado/MensajeOculto.ppm" << endl;
    Imagen ejemplo16("datos/gal.ppm");
    string msg,a;
    cout << "\tVamos a codificar el mensaje del archivo ./datos/MensajeOculto.txt" << endl;
    ifstream in("datos/MensajeOculto.txt");
    while(getline(in,a)) {
        msg += a;
    }
    ejemplo16.Codificar(msg);
    cout << "\tDecodificando el mensaje en ./resultado/MensajeOculto.txt " << endl;
    ejemplo16.Decodificar(msg);
    ofstream out("resultados/MensajeOculto.txt");
    out.write(msg.c_str(),msg.length());
    ejemplo16.EscribirImagen("resultados/MensajeOculto.ppm");

    cout << "\tPrueba morphing en ./resultado/Morphing/" << endl;
    Imagen ejemplo17("datos/llave.pgm");
    Imagen ejemplo171("datos/llaves.pgm");
    ejemplo17.Morphing(ejemplo171,"resultados/Morphing/",7);

}
