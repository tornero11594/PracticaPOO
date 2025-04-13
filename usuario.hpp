#include"cadena.hpp"
#include"fecha.hpp"
#include<istream>
#include<ostream>
#include<iomanip>
#include<unistd.h>
#include<random>
#include<crypt.h>

using namespace std;


class Clave
{
    public:

    //Constructor
    Clave(const char*); 

     //observador para devolver la clave cifrada
    const Cadena& clave() const noexcept;

    //verfica si la clave cifrada es correcta
    bool verifica(const char*) const noexcept; 


    private:
    Cadena clavecifrada;
    static const char caracteres_validos[];


    enum Razon{CORTA,ERROR_CRYPT}; //enumerado para la clase Incorrecta


    public:
    //clase para excepciones
    class Incorrecta
    {
     
        private:
        Razon r;
        
        
        public:
        //Constructor
        Incorrecta(Razon raz) noexcept;


        //Observador
        Razon razon() const noexcept;

    };
};

