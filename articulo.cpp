#include"articulo.hpp"

//ctor
Articulo::Articulo(Cadena cod,Cadena tit,Fecha f,double prec,size_t exist):codigo{cod},tituloArt{tit},fechapublicacion{f},precioArt{prec},numejemplares{exist}
{}





//Metodos observadores
Cadena Articulo::referencia() const noexcept{return codigo;}
Cadena Articulo::titulo() const noexcept{return tituloArt;}
Fecha Articulo::f_publi() const noexcept{return fechapublicacion;}
size_t Articulo::stock() const noexcept{return numejemplares;}



//Operador de inserción CORREGIR EL FORMATO, PREGUNTAR POR CORREO AL PROFESOR

std::ostream& operator<<(std::ostream& os,const Articulo&art)
{
    os<<"["<<art.codigo<<"]"<<" "<<art.tituloArt<<", "<<art.fechapublicacion<<". "<<fixed<<setprecision(2)<<art.precioArt<<" €"



}
