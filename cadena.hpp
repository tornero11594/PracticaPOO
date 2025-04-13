#ifndef CADENA_HPP
#define CADENA_HPP
#include <cstring>
#include <stdexcept>
#include<iterator>


class Cadena
{

public:
    // -----CONSTRUCTORES -----
    Cadena(size_t, char);
    explicit Cadena(size_t); // evitar conversion implicita
    Cadena();
    Cadena(const char *);
    Cadena(const Cadena &);
    Cadena(Cadena&& c) noexcept; //constructor de movimiento




    //----- ASIGNACION DE CADENAS -----
    Cadena &operator=(const Cadena &);
    Cadena &operator=(const char *);
    Cadena& operator=(Cadena&& c) noexcept; //operador de asignación por movimiento 


    explicit operator const char *() const;

    // ----- Operadores de comparacion -----
    friend bool operator<(const Cadena &, const Cadena &);
    friend bool operator<(const Cadena &, const char *);
    friend bool operator<(const char *, const Cadena &);
    friend bool operator<=(const Cadena &, const Cadena &);
    friend bool operator<=(const char *, const Cadena &);
    friend bool operator<=(const Cadena &, const char *);
    friend bool operator>(const Cadena &, const Cadena &);
    friend bool operator>(const Cadena &, const char *);
    friend bool operator>(const char *, const Cadena &);
    friend bool operator>=(const Cadena &, const Cadena &);
    friend bool operator>=(const Cadena &, const char *);
    friend bool operator>=(const char *, const Cadena &);
    friend bool operator==(const Cadena &, const Cadena &);
    friend bool operator==(const Cadena &, const char *);
    friend bool operator==(const char *, const Cadena &);
    friend bool operator!=(const Cadena &, const Cadena &);
    friend bool operator!=(const Cadena &, const char *);
    friend bool operator!=(const char *, const Cadena &);

    // Tipos de iteradores
    using iterator = char *;
    using const_iterator = const char *;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Métodos para obtener iteradores
    iterator begin() noexcept { return s_; }
    const_iterator begin() const noexcept { return s_; }
    const_iterator cbegin() const noexcept { return s_; }

    iterator end() noexcept { return s_ + tam_; }
    const_iterator end() const noexcept { return s_ + tam_; }
    const_iterator cend() const noexcept { return s_ + tam_; }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }




    //--SALIDA ESTANDAR----
    friend std::ostream &operator<<(std::ostream &, const Cadena &);
    friend std::istream &operator>>(std::istream &, Cadena &);
    const char &operator[](size_t) const; // sobrecarga del operador de indice
    char &operator[](size_t);
    const char &at(size_t) const;
    char &at(size_t);

    //-----CONCATENACION DE CADENAS-----
    friend Cadena operator+(const Cadena &, const Cadena &);
    Cadena &operator+=(const Cadena &);

    // -----SUBSTRAER UNA CADENA-----
    Cadena substr(size_t, size_t) const;

    //----- METODOS OBSERVADORES-----
    inline size_t length() const noexcept
    {
        return strlen(s_);
    }

    // DESTRUCTOR
    ~Cadena();

    // ATRIBUTOS
private:
    static char vacia[1]; // caracter terminador, atributo de clase
    size_t tam_;
    char *s_;
};

#endif