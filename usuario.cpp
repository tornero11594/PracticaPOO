#include "usuario.hpp"
#include "tarjeta.hpp"
unordered_set<Cadena> Usuario::ids;
const char Clave::caracteres_validos[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";

// IMPLEMENTACIÓN DE LA CLASE USUARIO
// Constructor
Usuario::Usuario(const Cadena &iden, const Cadena &nombr, const Cadena &apelli, const Cadena &direcc, const Clave &cl) : ident{iden}, nom{nombr}, apell{apelli}, dir{direcc}, contrasena{cl}
{
    // vamos a comprobar antes de inicializar si un usuario está duplicado
    typedef unordered_set<Cadena>::iterator iterador;
    std::pair<iterador, bool> res = ids.insert(ident);
    if (!res.second) // la insercion no se ha llevado a cabo correctamente
    {
        Id_duplicado I(ident); // corregir este error
        throw I;
    }
}

// Metodos observadores
const Cadena &Usuario::id() const noexcept { return ident; }
const Cadena &Usuario::nombre() const noexcept { return nom; }
const Cadena &Usuario::apellidos() const noexcept { return apell; }
const Cadena &Usuario::direccion() const noexcept { return dir; }
const Usuario::Articulos &Usuario::compra() const noexcept { return art; }

void Usuario::no_es_titular_de(Tarjeta& tar) {
    tarjetas_.erase(tar.numero());
}


void Usuario::es_titular_de(Tarjeta& tar)
{
    if (tar.titular() != this) return; // no te quedes tarjetas de otro
    tarjetas_.insert({tar.numero(), &tar});
}

// Metodo para asociacion con Artículo
void Usuario::compra(Articulo &artic, size_t cantidad)
{
    Articulo *p = &artic;

    if (cantidad == 0) // eliminamos los ariticulos del carrito
    {
        art.erase(p);
    }

    else
    {
        auto resultado = art.insert({p, cantidad});

        if (!resultado.second)
            resultado.first->second = cantidad;
    }
}

// método para vaciar el carro
void Usuario::vaciar_carro()
{
    art.clear();
}

// numero de artículos en el carrito del usuario
size_t Usuario::n_articulos() const noexcept
{
    return art.size();
}

// Imprimir info de un usuario por pantalla
ostream &operator<<(ostream &os, const Usuario &user)
{
    os << user.ident << " [" << user.contrasena << "] " << user.nom << " " << user.apell << endl;
    os << user.dir << endl;
    os << "Tarjetas:" << endl;

    auto it = user.tarjetas_.begin();
    while (it != user.tarjetas_.end()) // recorremos las tarjetas de un usuario para imprimirlas
    {
        os << *it->second << endl;
        ++it;
    }

    return os;
}

const Usuario::Tarjetas &Usuario::tarjetas() const noexcept
{
    return tarjetas_;
}

Usuario::~Usuario()
{
    auto it = tarjetas_.begin();

    while (it != tarjetas_.end())
    {
        it->second->anula_titular();
        it++;
    }

    ids.erase(ident); // eliminamos al usuario del conjunto
}

// IMPLEMENTACIÓN DE LA CLASE PARA EXCEPCIONES
Usuario::Id_duplicado::Id_duplicado(const Cadena &dup) : identifdupl{dup}
{
}
const Cadena &Usuario::Id_duplicado::idd() const noexcept { return identifdupl; }

void mostrar_carro(ostream &os, const Usuario &u)
{
    os << "Carrito de compra de " << u.id() << " [Artículos: " << u.n_articulos() << "]\n";
    os << "Cant. Artículo\n";
    os << "===========================================================\n";
    for (const auto &par : u.compra())
        os << par.second << " " << *par.first << endl;
}

// IMPLEMENTACIÓN DE LA CLASE Clave
Clave::Clave(const char *cad)
{
    if (std::strlen(cad) < 5)
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

        static std::random_device rd;
        static std::mt19937 gna{rd()};
        static const size_t n = sizeof(caracteres_validos) - 1; // n = 64
        std::uniform_int_distribution<size_t> uniforme(0, n - 1);

        char sal[3] = {
            caracteres_validos[uniforme(gna)],
            caracteres_validos[uniforme(gna)],
            '\0'};

        char *cif = crypt(cad, sal);

        if (cif)
            clavecifrada = cif;
        else
            throw Incorrecta(ERROR_CRYPT);
    }
}

const Cadena &Clave::clave() const noexcept
{
    return clavecifrada;
}

bool Clave::verifica(const char* cad) const noexcept {
    return Cadena(crypt(cad, (const char*)clavecifrada)) == clavecifrada;
}


Clave::Incorrecta::Incorrecta(Razon raz) noexcept : r{raz}
{
}

Clave::Razon Clave::Incorrecta::razon() const noexcept { return r; }

ostream &operator<<(ostream &os, const Clave &clav)
{
    os << clav.clavecifrada;
    return os;
}
