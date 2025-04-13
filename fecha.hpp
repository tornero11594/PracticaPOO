#ifndef FECHA_HPP
#define FECHA_HPP

#include<chrono>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;


class Fecha
{

    public:

    //-----CONSTRUCTORES------
    Fecha(int,int,int);
    Fecha(int,int); 
    explicit Fecha(int); //evitar conversiones implicitas
    //Fecha(const Fecha&);
    Fecha(const char*);
    Fecha();


    /*Una Fecha (constante o no) podrá convertirse implícitamente a una cadena de caracteres  de bajo nivel en el formato "DIASEM DD de MES de AAAA"*/


    // -----OPERADORES-----
    //Fecha& operator=(const Fecha&);
    Fecha& operator++(); //++f (Incremeto prefijo)
    Fecha& operator--(); //--f (Decremento prefijo)
    Fecha operator++(int); //f++(Incremento sufijo)
    Fecha operator--(int); //f--(Decremento sufijo)
    Fecha operator+(int) const; //fecha + un numero
    Fecha operator-(int) const; //fecha - un numero
    Fecha& operator+=(int);
    Fecha& operator-=(int);
    const char* cadena() const; //operador de conversión

    friend ostream& operator<<(ostream& os, const Fecha&); //operador para mostrar el flujo 
    friend istream& operator>>(istream& os, Fecha&); //operador para inyectar el flujo



    friend bool operator<(const Fecha&,const Fecha&);
    friend bool operator==(const Fecha&,const Fecha&);
    friend bool operator<=(const Fecha&,const Fecha&);
    friend bool operator>(const Fecha&,const Fecha&);
    friend bool operator>=(const Fecha&,const Fecha&);
    friend bool operator!=(const Fecha&,const Fecha&);
    


    //-----METODOS OBSERVADORES-----
     int dia() const noexcept;
     int mes() const noexcept;
     int anno() const noexcept;

    //----- ATRIBUTOS DE CLASE -----
    static const int AnnoMinimo=1902; //atributo de clase
    static const int AnnoMaximo=2037; //atributo de clase


    //------DESTRUCTOR ------


    // -----CLASE PARA EXCEPCIONES -----
    class Invalida
    {
        public:
        Invalida(const char*);
        Invalida(const Invalida&);
        const char* por_que() const;
        ~Invalida();


        private:
        char* razon;

    };

    //atributos
    private:
    int di,me,ano;
    bool esBisiesto(int); //funcion auxiliar para saber si un año es bisiesto
    int diasEnMes(int,int); //funcion auxiliar para determinar los dias de un mes en un año determinado
    void aumentaFecha(int) ; //funcion auxiliar para aumentar una fehca
    void disminuyeFecha(int); //funcion auxiliar para disminuir una fecha
    mutable char crep[50];
    mutable bool actual;
    

};



#endif