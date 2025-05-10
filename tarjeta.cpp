#include "tarjeta.hpp"
#include "usuario.hpp"

set<Numero> Tarjeta::conjuntotarjetas;

// ========== IMPLEMENTACIÓN DE LA CLASE TARJETA ==========

Tarjeta::Tarjeta(const Numero& numerillo, Usuario& uuser, const Fecha& fechia, bool ac)
    : num{numerillo}, tit{&uuser}, cad{fechia}, activ{true}
{
    Fecha hoy;
    if (cad < hoy)
        throw Caducada(cad);

    auto res = conjuntotarjetas.insert(num);
    if (!res.second)
        throw Num_duplicado(num);

    uuser.es_titular_de(*this);
}

const Numero& Tarjeta::numero() const noexcept { return num; }
const Usuario* Tarjeta::titular() const noexcept { return tit; }
const Fecha& Tarjeta::caducidad() const noexcept { return cad; }
bool Tarjeta::activa() const noexcept { return activ; }

Tarjeta::Tipo Tarjeta::tipo() const noexcept {
    const char* cadena = num;
    if ((cadena[0] == '3' && cadena[1] == '4') || (cadena[0] == '3' && cadena[1] == '7'))
        return AmericanExpress;
    else if (cadena[0] == '3')
        return JCB;
    else if (cadena[0] == '4')
        return VISA;
    else if (cadena[0] == '5')
        return Mastercard;
    else if (cadena[0] == '6')
        return Maestro;
    else
        return Otro;
}

bool Tarjeta::activa(bool est) {
    activ = est;
    return activ;
}

void Tarjeta::anula_titular() {
    activ = false;
    tit = nullptr;
}

ostream& operator<<(ostream& os, const Tarjeta& t) {
    os << t.tipo() << '\n';
    os << t.numero() << '\n';

    // Convertir nombre y apellidos a mayúsculas temporalmente
    Cadena nombre = t.titular()->nombre();
    Cadena apellidos = t.titular()->apellidos();

    for (auto& c : nombre) c = toupper(static_cast<unsigned char>(c));
    for (auto& c : apellidos) c = toupper(static_cast<unsigned char>(c));

    os << nombre << " " << apellidos << '\n';
    os << "Caduca: " << setfill('0') << setw(2) << t.caducidad().mes()
       << "/" << setw(2) << (t.caducidad().anno() % 100) << '\n';

    return os;
}

ostream& operator<<(ostream& os, const Tarjeta::Tipo& tipo) {
    switch (tipo) {
        case Tarjeta::VISA: os << "VISA"; break;
        case Tarjeta::Mastercard: os << "Mastercard"; break;
        case Tarjeta::Maestro: os << "Maestro"; break;
        case Tarjeta::JCB: os << "JCB"; break;
        case Tarjeta::AmericanExpress: os << "American Express"; break;
        default: os << "Tipo indeterminado"; break;
    }
    return os;
}

bool operator<(const Tarjeta& t1, const Tarjeta& t2) {
    return t1.numero() < t2.numero();
}

Tarjeta::~Tarjeta() {
    if (tit)
        const_cast<Usuario*>(tit)->no_es_titular_de(*this);
    conjuntotarjetas.erase(num);
}


Tarjeta::Caducada::Caducada(const Fecha& f) : cad(f) {}
const Fecha& Tarjeta::Caducada::cuando() const noexcept { return cad; }

Tarjeta::Num_duplicado::Num_duplicado(const Numero& n) : nume(n) {}
const Numero& Tarjeta::Num_duplicado::que() const noexcept { return nume; }

// ========== IMPLEMENTACIÓN DE LA CLASE NÚMERO ==========

Numero::Numero(const Cadena& cade) {
    Cadena sin_espacios;
    for (size_t i = 0; i < cade.length(); ++i) {
        if (!isspace(static_cast<unsigned char>(cade[i])))
            sin_espacios += Cadena(1, cade[i]);
    }

    if (sin_espacios.length() < 13 || sin_espacios.length() > 19)
        throw Incorrecto(LONGITUD);

    for (size_t i = 0; i < sin_espacios.length(); ++i) {
        if (!isdigit(sin_espacios[i]))
            throw Incorrecto(DIGITOS);
    }

    if (!luhn(sin_espacios))
        throw Incorrecto(NO_VALIDO);

    num = sin_espacios;
}


Numero::operator const char*() const {
    return num.operator const char*();
}

bool operator<(const Numero& n1, const Numero& n2) {
    return n1.num < n2.num;
}

Numero::Incorrecto::Incorrecto(Razon ra) : raz(ra) {}
Numero::Razon Numero::Incorrecto::razon() const noexcept { return raz; }

bool Numero::luhn(const Cadena& numero) {
    int suma = 0;
    bool alt = false;
    for (int i = int(numero.length()) - 1; i >= 0; --i) {
        int d = numero[size_t(i)] - '0';
        if (alt) {
            d *= 2;
            if (d > 9) d = (d % 10) + 1;
        }
        alt = !alt;
        suma += d;
    }
    return (suma % 10) == 0;
}
