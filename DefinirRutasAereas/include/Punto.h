#ifndef RUTAS_AEREAS_PUNTO_H
#define RUTAS_AEREAS_PUNTO_H

#include <iostream>
using namespace std;

class Punto{
private:
    double latitud;
    double longitud;
public:
    Punto():latitud(0),longitud(0){}
    Punto(double vx, double vf):latitud(vx),longitud(vf){}
    double GetLatitud(){return latitud;}
    double GetLongitud(){return longitud;}

    bool operator==(const Punto& obj) const{
        return (latitud==obj.latitud && longitud == obj.longitud);
    }

    bool operator != (const Punto& obj) const{
        return !((*this)==obj);
    }

    friend istream& operator >>(istream &in, Punto& obj);
    friend ostream& operator <<(ostream &out, const Punto& obj);
};

istream& operator >>(istream &in, Punto& obj){
    char parentesis, comma;
    in >> parentesis >> obj.latitud >> comma >> obj.longitud >> parentesis;
    return in;
}

ostream& operator <<(ostream &out, const Punto& obj){
    out << "( " << obj.latitud << ", " << obj.longitud << " )";
    return out;
}


#endif //RUTAS_AEREAS_PUNTO_H
