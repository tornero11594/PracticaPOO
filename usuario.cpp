#include"usuario.hpp"

const char Clave::caracteres_validos[]={"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};

Clave::Clave(const char* cad)
{
    if(std::strlen(cad)<5)
    {
        Incorrecta I(CORTA);
        throw I;       
    }

    else
    {   
        /*
        static std :: random_device rd; // Para obtener una semilla aleatoria para el GNA.
        static std :: mt19937 gna{rd()}; // Usamos un buen GNA, el de Matsumoto y Nishimura,
        // por ejemplo, inicializado con el valor rd().
        static const std :: size_t n {sizeof(caracteres_validos) - 1}; // n = 64
        std :: uniform_int_distribution<std::size_t> uniforme(0, n -1); // Genera números
        // pseudoaleatorios equiprobables en el intervalo [0, 63].
        const char sal[3] = {caracteres_validos[uniforme(gna)], //aqui ya tenemos 2 caracteres pseudoaletorios y el caracter terminador
        caracteres_validos[uniforme(gna)], '\0'};
        */

        
        const char encriptar[3]={'d','c','\0'};

        if(crypt(cad,(const char*)encriptar))
            clavecifrada=crypt(cad,encriptar);   //si se ha podido cifrar correctamente, guardamos en clavecifrada  
        

        else   //si no, lanazamos excepcion
        {       
            Incorrecta I(ERROR_CRYPT);
            throw I;
        }
            
    }

}

const Cadena& Clave::clave() const noexcept
{
    return clavecifrada; 
}


bool Clave::verifica(const char*cad) const noexcept
{

    //cifro la clave a partir de los caracteres que cifre la clave original
    const char encriptar[3]={'d','c','\0'};
    Cadena nuevaclave=crypt(cad,(const char*)encriptar);

    //si ambas claves son iguales devolvemos verdadero
    if(nuevaclave==clavecifrada)
        return true;

    else 
        return false;
}


Clave::Incorrecta::Incorrecta(Razon raz) noexcept :r{raz}
{}


Clave::Razon Clave::Incorrecta::razon() const noexcept{return r;}


