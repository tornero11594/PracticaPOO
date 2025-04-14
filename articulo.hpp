#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include"cadena.hpp"
#include"fecha.hpp"
#include<istream>
#include<ostream>
#include<iomanip>
using namespace std;


class Articulo
{

    public:

    //Constructor
    Articulo(Cadena cod,Cadena tit,Fecha f,double prec,size_t exist=0);

    //Metodos observadores
    Cadena referencia() const noexcept;
    Cadena titulo() const noexcept;
    Fecha f_publi() const noexcept;
    double precio() const noexcept;
    size_t stock() const noexcept;


    //Operador de insercion
    friend std::ostream& operator<<(std::ostream& os,const Articulo&art);





    //Pare privada
    private:
    const Cadena codigo; //atributo inmodificable
    const Cadena tituloArt; //atributo inmodificable
    const Fecha fechapublicacion; //atributo inmodificable
    double precioArt;
    size_t numejemplares;



};

#endif