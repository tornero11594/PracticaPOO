#include"cadena.hpp"
#include"fecha.hpp"
#include"tarjeta.hpp"
#include"articulo.hpp"
#include<istream>
#include<ostream>
#include<iomanip>
#include<unistd.h>
#include<random>
#include<crypt.h>
#include<map>
#include<unordered_map>
#include<unordered_set>
using namespace std;

class Usuario
{

    //declaración privada adelantada

     //tarjetas de pago que posee el usuario
     typedef map<Numero,Tarjeta*> Tarjetas;
     //contenido del carrito
     typedef unordered_map<Articulo*,unsigned int> Articulos;



    public:
    //Constructores
    Usuario(const Cadena&,const Cadena&,const Cadena&,const Cadena&,const Clave&);
    Usuario(const Usuario&)= delete; //indicamos que no exista constructor de copia
    Usuario& operator=(const Usuario&)= delete; //indicamos que no exista operador de asignación

    //Métodos observadores
    const Cadena& id() const noexcept;
    const Cadena& nombre() const noexcept;
    const Cadena& apellidos() const noexcept;
    const Cadena& direccion() const noexcept;
    const Tarjetas& tarjetas() const noexcept;
    const Articulos& compra() const noexcept; 


    //Funciones para crear asociaciones entre Tarjetas y Usuarios
    void es_titular_de(Tarjeta&); //asociar al usuario con una tarjeta
    void no_es_titular_de(Tarjeta&); //desligar al usuario con una tarjeta


    //Metodo para asociacion con Artículo
    void compra(const Articulo&,size_t cantidad=1);

    //método para vaciar el carro
    void vaciar_carro();

    //numero de artículos
    size_t n_articulos() const noexcept;

    //Imprimir info de un usuario por pantalla
    friend ostream& operator<<(ostream&os,const Usuario&);

    //mostrar el carrito de la compra de un usuario
    friend void mostrar_carro(const Articulos&a,const Usuario&);


    //Destructor. Desliga las tarjetas del usuario llamando al método Tarjeta::anula_titular()
    ~Usuario();


    //Clase para excepciones de usuario duplicado
    class Id_duplicado
    {
        public:
        Id_duplicado(const Cadena&); //constructor
        const Cadena& idd() const noexcept; //metodo que devuelve la cadena duplicada

        private:
        Cadena identifdupl;

    };





    private:
    //Atributos no modificables
    const Cadena ident;
    const Cadena nom;
    const Cadena apell;
    const Cadena dir;
    //contraseña del usuario
    Clave contrasena;
    Tarjetas tarjetas_;
    Articulos art;
   
    static unordered_set<Cadena> ids;

};





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

