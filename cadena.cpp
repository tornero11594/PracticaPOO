#include "cadena.hpp"
#include <iostream>

// Cadena::vacia[0]='\0';
char Cadena::vacia[1] = {'\0'};

Cadena::Cadena(size_t longi, char car) : tam_(longi), s_(new char[longi + 1])
{
    for (size_t i = 0; i < longi; i++)
    {
        s_[i] = car;
    }
    s_[longi] = '\0'; // incluimos caracter terminador
}

Cadena::Cadena(size_t longi) : tam_(longi), s_(new char[longi + 1])
{

    for (size_t i = 0; i < longi; i++)
    {
        s_[i] = ' ';
    }

    s_[longi] = '\0'; // insertamos caracter terminador

}

Cadena::Cadena() : tam_(0), s_(vacia)
{
}

Cadena::Cadena(const char *cad) : tam_(strlen(cad))
{
    if (tam_ == 0)
    {
        s_ = vacia;
    }

    else
    {
        s_ = new char[tam_ + 1];
        std::strcpy(s_, cad);
        s_[tam_] = '\0';
    }
}

Cadena::Cadena(const Cadena &C) : tam_(C.length())
{
    if (tam_ == 0)
        s_ = vacia;

    else
    {
        s_ = new char[C.tam_ + 1];
        std::strcpy(s_, C.s_);
        s_[C.tam_] = '\0';
    }
}

Cadena::Cadena(Cadena&& c) noexcept : tam_{c.tam_}, s_{(c.s_ == vacia) ? vacia : c.s_}
{
    if (c.s_ == vacia) // Si la cadena movida estaba vacía, no tocamos vacia
        s_ = vacia;
    else
        s_ = c.s_; // Movemos el puntero

    tam_ = c.tam_;

    // Dejamos c en un estado seguro
    c.s_ = vacia; 
    c.tam_ = 0;
}


Cadena& Cadena::operator=(Cadena&& c) noexcept
{
    if (this != &c) // Evitamos autoasignación
    {
        if (s_ != vacia) // Solo liberamos memoria si s_ no es vacia
            delete[] s_;

        if (c.s_ == vacia) // Si c.s_ es vacia, evitamos asignar nullptr
            s_ = vacia;
        else
            s_ = c.s_; // Movemos la memoria

        tam_ = c.tam_;

        // Dejamos `c` en un estado válido
        c.s_ = vacia;
        c.tam_ = 0;
    }
    return *this;
}




Cadena &Cadena::operator=(const Cadena &C)
{
    if (this != &C) // Evito la autoasignación
    {

        if (C.tam_ == 0) 
        {
            if (s_ != vacia)
                delete[] s_;

            s_ = vacia;
            tam_ = 0;
        }
        else
        {
            char *p = new char[C.tam_ + 1];  // Reservamos nueva memoria correctamente

            if (s_ != vacia)
                delete[] s_;

            tam_ = C.tam_;
            s_ = p;
            std::strcpy(s_, C.s_); // Copiamos el contenido
            s_[tam_] = '\0';  // Corrección del índice
        }
    }
    return *this;
}


Cadena::operator const char *() const
{
    return s_;
}
Cadena &Cadena::operator=(const char *cad)
{
    if (!cad) //  Evitar copiar una cadena inexistente
        throw std::runtime_error("Error: Intento de asignar un puntero nulo a Cadena");


    size_t nuevoTam = std::strlen(cad);

    if (nuevoTam == 0)  // Caso especial para cadenas vacías
    {
        if (s_  && s_!= vacia)
            delete[] s_; // Liberar memoria solo si `s_` no es `vacia`

        s_ = vacia;
        tam_ = 0;
    }

    else
    {
        char *p = new char[nuevoTam + 1];  

        std::strcpy(p, cad); 

        if (s_ != vacia)
            delete[] s_;  // Se libera solo si no es `vacia`

        s_ = p;
        tam_ = nuevoTam;
        s_[tam_] = '\0';  // Se asegura de terminar correctamente la cadena
    }

    return *this;
}

Cadena &Cadena::operator+=(const Cadena &C)
{
    if (C.tam_ == 0) //  Si `C` es vacío, no hay nada que concatenar
        return *this;

   
    char *p = new char[tam_ + C.tam_ + 1];;

    std::strcpy(p, s_);   // Copiar la cadena actual
    std::strcat(p, C.s_); // Concatenar la nueva cadena

    if (s_ && s_!= vacia)
        delete[] s_; // Se libera la memoria solo si `s_` no es `vacia`

    s_ = p;
    tam_ += C.tam_; 

    return *this;
}

// Comparadores
bool operator<(const Cadena &C1, const Cadena &C2)
{
    return (std::strcmp(C1.s_, C2.s_) < 0);
}

bool operator<(const Cadena &C1, const char *C2)
{
    Cadena c(C2);
    return (C1 < c);
}

bool operator<(const char *C1, const Cadena &C2)
{
    Cadena c(C1);
    return (c < C2);
}

bool operator==(const Cadena &C1, const Cadena &C2)
{
    return (strcmp(C1.s_, C2.s_) == 0);
}

bool operator==(const Cadena &C1, const char *C2)
{
    Cadena c(C2);

    return (C1 == c);
}

bool operator==(const char *c2, const Cadena &C1)
{
    Cadena c(c2);

    return (c == C1);
}

bool operator>(const Cadena &C1, const Cadena &C2)
{
    return (std::strcmp(C1.s_,C2.s_)>0);
}

bool operator>(const Cadena &C1, const char *C2)
{
    Cadena c(C2);
    return (!(C1 < c));
}

bool operator>(const char *C1, const Cadena &C2)
{
    Cadena c(C1);
    return (!(c < C2));
}

bool operator>=(const Cadena &C1, const Cadena &C2)
{
    return (std::strcmp(C1.s_,C2.s_)>=0);
}

bool operator>=(const Cadena &C1, const char *C2)
{
    Cadena c(C2);
    return (!(C1 < c));
}

bool operator>=(const char *C1, const Cadena &C2)
{

    Cadena c(C1);

    return (!(c < C2));
}

bool operator<=(const Cadena &C1, const Cadena &C2)
{
    return (!(C2 < C1));
}

bool operator<=(const char *C1, const Cadena &C2)
{
    Cadena c(C1);
    return (!(C2 < c));
}

bool operator<=(const Cadena &C1, const char *C2)
{
    Cadena c(C2);
    return (!(c < C1));
}

bool operator!=(const Cadena &C1, const Cadena &C2)
{
    return (!(C1 == C2));
}

bool operator!=(const char *C1, const Cadena &C2)
{
    Cadena c(C1);
    return (!(c == C2));
}

bool operator!=(const Cadena &C1, const char *C2)
{
    Cadena c(C2);
    return (!(C1 == c));
}

char &Cadena::operator[](size_t i)
{
    return s_[i];
}

const char &Cadena::operator[](size_t i) const
{
    return s_[i];
}

std::ostream &operator<<(std::ostream &os, const Cadena &cad)
{
    os << cad.s_;
    return os;
}


std::istream& operator >>(std::istream& is, Cadena& cade)
{
    char cad1[33], cad2[32], c;
    int i = 0, j = 0;

    cad1[0] = '\0';
    
    while(is.get(c) && std::isspace(c));

    if (is)
    {
        cad1[0] = c;
        is.get(cad1 + 1, 32, ' ');
    }

    for(i= 0; i <= 32 && cad1[i] != '\0' && !(j != 0 && std::isspace(cad1[i])); ++i)
    {
        if (!std::isspace(cad1[i]))
        {
            cad2[j] = cad1[i];
            ++j;
        }
    }
    cad2[j] = '\0';
    if(j == 0)
    {
        cade = Cadena{};
    }
    else
    {
        cade = Cadena(cad2);
    }
    return is;
}
char &Cadena::at(size_t i)
{
    if (i >= length())
        throw std::out_of_range("Indice fuera de rango");

    else
        return s_[i];
}

const char &Cadena::at(size_t i) const
{
    if (i >= length())
        throw std::out_of_range("Indice fuera de rango");

    else
        return s_[i];
}

Cadena operator+(const Cadena &C1, const Cadena &C2)
{

    Cadena c3(C1.tam_ + C2.tam_, ' ');

    std::strcpy(c3.s_, C1.s_);
    std::strcat(c3.s_, C2.s_);

    return c3;
}

Cadena Cadena::substr(size_t indice, size_t tama) const
{
    if (indice >= tam_)
        throw std::out_of_range("Indice fuera de rango");

    if (tama > tam_ - indice) //  Evita desbordamiento de `size_t`
        throw std::out_of_range("Tamano fuera de rango");

    if (tama == 0)  //  Si `tama == 0`, devuelve una cadena vacía
        return Cadena();

    Cadena c(tama); //  Crea cadena con tamaño correcto

    for (size_t i = 0; i < tama; i++)
        c[i] = s_[indice + i];

    return c;
}



Cadena::~Cadena()
{
    if (s_ && s_ != vacia)
    {
        delete[] s_;
        s_ = vacia;
        tam_=0;
    }
}
