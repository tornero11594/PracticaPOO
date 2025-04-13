#include"cadena.hpp"
#include <cctype>
#include<iostream>
using namespace std;

class Numero
{

    public:

    //Constructor
    Numero(Cadena&); //recibo una copia porque lo voy a tener que modificar


    //enumeracion para excepciones
    enum Razon{LONGITUD,DIGITOS,NO_VALIDO};

    //operador de conversión de Número a cadena de bajo nivel
    /*
    Son funciones especiales dentro de una clase, que permiten que un objeto de tu clase se pueda "convertir automáticamente" a otro tipo.
    No tienen nombre.
    No reciben argumentos.
    Devuelven un tipo específico (el tipo al que quieres convertir).
    */
    operator const char*() const;


    //sobrecarga del operador menor que para comparar Numeros
    friend bool operator<(const Numero&,const Numero&);



    //clase para excepciones

    class Incorrecto
    {
        public:
        Incorrecto(Razon);
        Razon razon() const noexcept;

        private:
        Razon raz;

    };

    private:
    Cadena num;
    bool luhn(const Cadena& numero);




};


