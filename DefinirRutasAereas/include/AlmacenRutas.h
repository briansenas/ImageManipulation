#ifndef RUTAS_AEREAS_ALMACENRUTAS_H
#define RUTAS_AEREAS_ALMACENRUTAS_H

#include <string>
#include <iostream>
#include "Ruta.h"
using namespace std;

class Almacen_Rutas{
private:
    list<Ruta> rutas;

public:
    Almacen_Rutas():rutas(0){}
    Almacen_Rutas(list<Ruta> nrutas){
        rutas = nrutas;
    }

    int getSize(){return rutas.size();}
    list<Ruta> getRutas(){return rutas;}
    Ruta& operator[](unsigned int i){
        if(i>=0 && i<rutas.size()){
            Almacen_Rutas::iterator it;
            it.m_Ptr = rutas.begin();
            return it[i];
        }
    }

    Ruta GetRuta(string code){
        Ruta res;
        for(typename list<Ruta>::iterator it=rutas.begin();
            it!=rutas.end();it++){
            if(it->getName() == code)
                res = *it;
        }
        return res;
    }

    list<Ruta> GetRutas_Con_Punto(Punto punto){
        list<Ruta> res;
        for(typename list<Ruta>::iterator it=rutas.begin();
            it != rutas.end(); it++){
            for(int i=0; i < it->getSize();i++){
                if((*it)[i] == punto) {
                    res.push_back(*it);
                    break;
                }
            }
        }
        return res;
    }

    void AddRoute(Ruta toAdd){
        rutas.push_back(toAdd);
    }

    void DelRoute(unsigned int toDel){
        assert(toDel>=0 && toDel < rutas.size());
        typename list<Ruta>::iterator it = rutas.begin();
        for(unsigned int i=0;i<toDel;i++)
            it++;
        rutas.erase(it);
    }
    void DelRoute(Ruta toDel){
        typename list<Ruta>::iterator it = rutas.begin();
        for(; it != rutas.end(); it++){
            if( *it == toDel)
                break;
        }
        rutas.erase(it);
    }

    friend ostream& operator<<(ostream& out, Almacen_Rutas& obj){
        for(typename list<Ruta>::iterator it = obj.rutas.begin();
            it != obj.rutas.end(); it++){
            out << *it << endl;
        }
        return out;
    }

    friend istream& operator>>(istream& in, Almacen_Rutas& obj){
        Ruta temp;
        if (in.peek()=='#'){
            string whatever;
            getline(in,whatever);
        }
        while (in>>temp){
            obj.AddRoute(temp);
            temp.Erase();
        }
        return in;
    }

    class iterator {
    public:
        using ValueType = Ruta;
        using PointerType = ValueType *;
        using ReferenceType = ValueType &;
    public:
        iterator() : m_Ptr(0) {}

        iterator(list<Ruta>::iterator ptr) : m_Ptr(ptr) {}

        iterator &operator++() {
            m_Ptr++;
            return *this;
        }

        iterator operator++(int) {
            iterator it;
            it.m_Ptr = this->m_Ptr;
            this->m_Ptr++;
            return it;
        }

        iterator &operator--() {
            m_Ptr--;
            return *this;
        }

        iterator operator--(int) {
            iterator it;
            it.m_Ptr = this->m_Ptr;
            this->m_Ptr--;
            return it;
        }

        ReferenceType operator[](int index) {
            for (int i = 0; i < index; i++) {
                m_Ptr++;
            }
            return *m_Ptr;
        }

        ReferenceType operator->() {
            return *m_Ptr;
        }

        ReferenceType operator*() {
            return *m_Ptr;
        }

        bool operator==(const iterator &other) const {
            return m_Ptr == other.m_Ptr;
        }

        bool operator!=(const iterator &other) const {
            return m_Ptr != other.m_Ptr;
        }

        friend class Almacen_Rutas;

        //friend class ConstIterator;
    private:
        typename list<Ruta>::iterator m_Ptr;
    };

    iterator begin() {
        Almacen_Rutas::iterator it;
        it.m_Ptr = rutas.begin();
        return it;
    }

    iterator end() {
        Almacen_Rutas::iterator it;
        it.m_Ptr = rutas.end();
        return it;
    }
};
#endif //RUTAS_AEREAS_ALMACENRUTAS_H
