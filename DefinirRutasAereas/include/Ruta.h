#ifndef RUTAS_AEREAS_RUTAS_H
#define RUTAS_AEREAS_RUTAS_H

#include <string>
#include "Punto.h"
#include <list>
#include <assert.h>

using namespace std;

class Ruta {
private:
    string name;
    list <Punto> puntos;

public:
    Ruta() : name("") {}

    Ruta(string name, list <Punto> route) {
        this->name = name;
        puntos = route;
    }

    Ruta(string name, Punto punto) {
        this->name = name;
        puntos.push_back(punto);
    }

    int getSize() { return puntos.size(); }

    string getName() { return name; }

    list <Punto> getPuntos() { return puntos; }

    Punto &operator[](unsigned int i) {
        assert(i >= 0 && i < puntos.size());
        Ruta::iterator it;
        it.m_Ptr = puntos.begin();
        return it[i];


    }

    void AddPunto(Punto toAdd) {
        puntos.push_back(toAdd);
    }

    void DelPunto(unsigned int toDel) {
        typename list<Punto>::iterator it = puntos.begin();
        assert(toDel >= 0 && toDel < puntos.size());
        for (unsigned int i = 0; i < toDel; i++)
            it++;
        puntos.erase(it);
    }

    void DelPunto(Punto toDel) {
        typename list<Punto>::iterator it = puntos.begin();
        for (; it != puntos.end(); it++) {
            if (*it == toDel)
                break;
        }
        puntos.erase(it);
    }

    bool operator==(const Ruta &obj) {
        if (puntos.size() != obj.puntos.size())
            return false;
        else {
            typename list<Punto>::const_iterator it = puntos.begin(), it2 = obj.puntos.begin();
            while (it != puntos.end()) {
                if (*it != *it2)
                    return false;
                it++;
                it2++;
            }
        }
        return true;
    }

    friend ostream &operator<<(ostream &out, Ruta &obj) {
        out << obj.name << " " << obj.getSize() << " ";
        for (typename list<Punto>::iterator it = obj.puntos.begin();
             it != obj.puntos.end(); it++) {
            out << *it << " ";
        }
        return out;
    }

    friend istream &operator>>(istream &in, Ruta &obj) {
        int size;
        in >> obj.name >> size;
        Punto temp;
        for (int i = 0; i < size; i++) {
            in >> temp;
            obj.AddPunto(temp);
        }
        return in;
    }

    void Erase(){
        puntos.clear();
    }

    class iterator {
    public:

        iterator() : m_Ptr(0) {}

        iterator(list<Punto>::iterator ptr) : m_Ptr(ptr) {}

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

        Punto &operator[](int index) {
            for (int i = 0; i < index; i++) {
                m_Ptr++;
            }
            return *m_Ptr;
        }

        Punto &operator->() {
            return *m_Ptr;
        }

        Punto &operator*() {
            return *m_Ptr;
        }

        bool operator==(const iterator &other) const {
            return m_Ptr == other.m_Ptr;
        }

        bool operator!=(const iterator &other) const {
            return m_Ptr != other.m_Ptr;
        }

        friend class Ruta;

        //friend class ConstIterator;
    private:
        typename list<Punto>::iterator m_Ptr;
    };

    iterator begin() {
        Ruta::iterator it;
        it.m_Ptr = puntos.begin();
        return it;
    }

    iterator end() {
        Ruta::iterator it;
        it.m_Ptr = puntos.end();
        return it;
    }
};

#endif //RUTAS_AEREAS_RUTAS_H
