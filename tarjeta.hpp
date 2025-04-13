#include"cadena.hpp"
#include"usuario.hpp"
#include"fecha.hpp"
#include <cctype>
#include<iostream>
#include<set>
using namespace std;

class Tarjeta
{
    public:
    enum Tipo{Otro,VISA,Mastercard,Maestro,JCB,AmericanExpress};
    //constructores 
    Tarjeta(const Numero&, Usuario*,const Fecha&,bool ac=true);
    Tarjeta(const Tarjeta&)=delete;
    Tarjeta& operator=(const Tarjeta&)=delete;




    //métodos observadores
    const Numero& numero() const noexcept;
    const Usuario* titular() const noexcept;
    const Fecha& caducidad() const noexcept;
    bool activa() const noexcept;
    Tipo tipo() const noexcept;

    //activar o desactivar una tarjeta
    bool activa(bool est);

    //modificador  pone la tarjeta en false y el puntero de titular a nulo
    void anula_titular();


    //operador de inserción para tarjeta
    friend ostream& operator<<(ostream&os,const Tarjeta&t);

    //operador de inserción para tipo
    friend ostream& operator<<(ostream&os, const Tipo&);

    //operador de menor para dos tarjetas
    friend bool operator<(const Tarjeta&t1,const Tarjeta&t2);

    //destructor
    ~Tarjeta();

    //clases para excepciones
    //tarjeta caducada
    class Caducada
    {
        public:
        Caducada(const Fecha&);
        const Fecha& cuando() const noexcept;

        private:
        Fecha cad;
    };

    //numero de tarjeta iguales
    class Num_duplicado
    {
        public:
        Num_duplicado(const Numero&);
        const Numero& que() const noexcept;

        private:
        Numero nume;
    };



    private:
    const Numero num;
    const Usuario* tit;
    const Fecha cad;
    bool activ;
    static set<Numero> conjuntotarjetas;


};





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


