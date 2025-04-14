#include "fecha.hpp"
#include <iostream>

// Definición de nombres de días y meses
static const char *dias_semana[] = {
    "domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};

static const char *meses[] = {
    "enero", "febrero", "marzo", "abril", "mayo", "junio", "julio",
    "agosto", "septiembre", "octubre", "noviembre", "diciembre"};

Fecha::Fecha(int d, int m, int annio)
{
    auto now = std::chrono::system_clock::now();                   // obtenemos el tiempo actual
    std::time_t now_c = std::chrono::system_clock::to_time_t(now); // convertimos a tiempo
    std::tm *local_time = std::localtime(&now_c);                  // convertimos a estructura tm, donde tenemos fecha y hora desglosada

    if (annio == 0)
        ano = local_time->tm_year + 1900;

    else
    {

        if (annio < AnnoMinimo || annio > AnnoMaximo)
        {
            Invalida I("Anio_invalido");
            throw I;
        }

        else
            ano = annio;
    }

    if (m == 0)
        me = local_time->tm_mon + 1; // enero empieza en 0

    else
    {
        if (m < 0 || m > 12)
        {
            Invalida I("Mes_invalido");
            throw I;
        }

        else
            me = m;
    }

    if (d == 0)
        di = local_time->tm_mday;

    else
    {
        int diasmes = diasEnMes(me, ano);
        if (d < 1 || d > diasmes)
        {
            Invalida I("Dia_invalido");
            throw I;
        }

        else
            di = d; // ha dado un dia correcto
    }
}

Fecha::Fecha(int d, int m) // : di(d),me(m) NO INICIALIZO PORQUE PUEDEN OTORGAR FECHA INCORRECTA
{
    auto now = std::chrono::system_clock::now();                   // obtenemos el tiempo actual
    std::time_t now_c = std::chrono::system_clock::to_time_t(now); // convertimos a tiempo
    std::tm *local_time = std::localtime(&now_c);                  // convertimos a estructura tm, donde tenemos fecha y hora desglosada
    ano = local_time->tm_year + 1900;                              // obtenemos el anio

    if (m == 0)
        me = local_time->tm_mon + 1; // enero empieza en 0

    else
    {
        if (m < 0 || m > 12)
        {
            Invalida I("Mes_invalido");
            throw I;
        }

        else
        {
            me = m; // enero empieza en 0
        }
    }
    if (d == 0)
        di = local_time->tm_mday;

    else
    {
        int diasmes = diasEnMes(me, ano);
        if (d < 0 || d > diasmes)
        {
            Invalida I("Dia_invalido");
            throw I;
        }

        else
            di = d;
    }
}

Fecha::Fecha(int d) //: di(d) No inicializo el dia porque puede ser incorrecto
{

    auto now = std::chrono::system_clock::now();                   // obtenemos el tiempo actual
    std::time_t now_c = std::chrono::system_clock::to_time_t(now); // convertimos a tiempo
    std::tm *local_time = std::localtime(&now_c);                  // convertimos a estructura tm, donde tenemos fecha y hora desglosada

    me = local_time->tm_mon + 1;      // obtenemos el mes. Le sumamos 1 porque enero es 0
    ano = local_time->tm_year + 1900; // obtenemos el anio

    if (d == 0)
        di = local_time->tm_mday;

    else
    {
        int diasmes = diasEnMes(me, ano);
        if (d < 0 || d > diasmes)
        {
            Invalida I("Dia_invalido");
            throw I;
        }

        else
            di = d;
    }
}

Fecha::Fecha()
{
    auto now = std::chrono::system_clock::now();                   // obtenemos el tiempo actual
    std::time_t now_c = std::chrono::system_clock::to_time_t(now); // convertimos a tiempo
    std::tm *local_time = std::localtime(&now_c);                  // convertimos a estructura tm, donde tenemos fecha y hora desglosada

    di = local_time->tm_mday;
    me = local_time->tm_mon + 1;
    ano = local_time->tm_year + 1900;
}

Fecha::Fecha(const char *fe)
{
    int d, m, a;
    auto now = std::chrono::system_clock::now();                   // obtenemos el tiempo actual
    std::time_t now_c = std::chrono::system_clock::to_time_t(now); // convertimos a tiempo
    std::tm *local_time = std::localtime(&now_c);                  // convertimos a estructura tm, donde tenemos fecha y hora desglosada

    if (sscanf(fe, "%d/%d/%d", &d, &m, &a) == 3)
    {
        if (a == 0)
            ano = local_time->tm_year + 1900;

        else
        {

            if (a < AnnoMinimo || a > AnnoMaximo)
            {
                Invalida I("Anio_invalido");
                throw I;
            }

            else
                ano = a;
        }

        if (m == 0)
            me = local_time->tm_mon + 1;

        else
        {
            if (m < 0 || m > 12)
            {
                Invalida I("Mes_invalido");
                throw I;
            }
            else
            {
                me = m;
            }
        }

        int diasmes = diasEnMes(me, ano);

        if (d == 0)
            di = local_time->tm_mday;

        else
        {
            if (d < 0 || d > diasmes)
            {
                Invalida I("Dia_invalido");
                throw I;
            }

            else
                di = d;
        }
    }

    else
    {
        Invalida I("Fecha_introducida_incorrecta");
        throw I;
    }
}

bool operator<(const Fecha &f1, const Fecha &f2) // estamos comprobando que f1<f2
{
    bool dev = false;

    if (f1.ano < f2.ano)
        dev = true;

    else
    {
        if (f1.ano > f2.ano)
            dev = false;

        else // años iguales
        {
            if (f1.me < f2.me)
                dev = true;

            else
            {
                if (f1.me > f2.me)
                    dev = false;

                else // mes iguales
                {
                    if (f1.di < f2.di)
                        dev = true;

                    else
                    {
                        if (f1.di >= f2.di)
                            dev = false;
                    }
                }
            }
        }
    }

    return dev;
}

bool operator==(const Fecha &f1, const Fecha &f2)
{
    return (f1.ano == f2.ano && f1.me == f2.me && f1.di == f2.di);
}

bool operator<=(const Fecha &f1, const Fecha &f2)
{
    return (!(f2 < f1));
}

bool operator>(const Fecha &f1, const Fecha &f2)
{
    if (f1.ano > f2.ano)
        return true;
    if (f1.ano < f2.ano)
        return false;
    if (f1.me > f2.me)
        return true;
    if (f1.me < f2.me)
        return false;
    return f1.di > f2.di;
}

bool operator>=(const Fecha &f1, const Fecha &f2)
{
    return (f1 > f2) || (f1 == f2);
}

bool operator!=(const Fecha &f1, const Fecha &f2)
{
    return (!(f1 == f2));
}

/*
Fecha::Fecha(const Fecha &F) // creo que no hace falta definirlo
{

}

Fecha &Fecha::operator=(const Fecha &F) // creo que no hace falta definirlo
{
}
*/
int Fecha::dia() const noexcept
{

    return di;
}

int Fecha::mes() const noexcept
{
    return me;
}

int Fecha::anno() const noexcept
{
    return ano;
}

Fecha::Invalida::Invalida(const char *cad) : razon{new char[strlen(cad + 1)]}
{
    strcpy(razon, cad);
}

const char *Fecha::Invalida::por_que() const
{
    return razon;
}

Fecha::Invalida::~Invalida()
{
    delete[] razon;
}

bool Fecha::esBisiesto(int anio)
{
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

int Fecha::diasEnMes(int mes, int anio)
{
    static const int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mes == 2 && esBisiesto(anio))
        return 29; // Febrero en año bisiesto

    return diasPorMes[mes - 1]; // Devuelve los días del mes correspondiente
}

Fecha::Invalida::Invalida(const Invalida &I) : Fecha::Invalida{I.razon}
{
}

Fecha &Fecha::operator++()
{

    aumentaFecha(1);
    actual = false;
    return *this;
}

Fecha Fecha::operator++(int)
{
    Fecha copia(*this);
    if (ano >= AnnoMaximo || ano <= AnnoMinimo)
    {
        throw Invalida("Fecha fuera de rango");
    }
    aumentaFecha(1);
    return copia;
}

Fecha &Fecha::operator--()
{
    disminuyeFecha(1);
    actual = false;
    return *this;
}

Fecha Fecha::operator+(int n) const
{
    Fecha nueva_fecha(*this);    // Copia el objeto actual
    nueva_fecha.aumentaFecha(n); // Modifica la copia
    return nueva_fecha;          // Devuelve el objeto por valor
}

Fecha Fecha::operator-(int n) const
{

    Fecha nueva_fecha(*this);
    nueva_fecha.disminuyeFecha(n);
    return nueva_fecha;
}

Fecha Fecha::operator--(int)
{
    Fecha copia(*this);

    if (ano >= AnnoMaximo || ano <= AnnoMinimo)
    {
        throw Invalida("Fecha fuera de rango");
    }
    disminuyeFecha(1);
    return copia;
}

ostream &operator<<(ostream &os, const Fecha &f)
{
    os << f.cadena(); 
    return os;
}

istream &operator>>(istream &is, Fecha &fe)
{
    char fecha_str[11]; // Buffer de tamaño exacto "dd/mm/aaaa" + '\0'

    is.width(11);  // Limitamos la cantidad de caracteres leídos
    is >> fecha_str;

    if (is.fail()) return is; // Si la entrada ya falló, no intentamos procesar más.

    try {
        fe = Fecha(fecha_str); // Intentamos construir la fecha con la entrada
    } 
    catch (const Fecha::Invalida &e) {
        is.setstate(std::ios::failbit); // Marcamos el flujo como fallido
        throw e; // Lanzamos la excepción requerida
    }

    return is;
}



Fecha &Fecha::operator+=(int n)
{
    aumentaFecha(n);
    actual = false;

    return *this;
}

Fecha &Fecha::operator-=(int n)
{
    disminuyeFecha(n);
    actual = false;

    return *this;
}

const char *Fecha::cadena() const
{
    if (!actual)
    { // Solo recalcular si la conversión no está actualizada
        std::tm timeinfo = {};
        timeinfo.tm_mday = di;
        timeinfo.tm_mon = me - 1;      // `tm_mon` va de 0 (enero) a 11 (diciembre)
        timeinfo.tm_year = ano - 1900; // `tm_year` cuenta desde 1900
        std::mktime(&timeinfo);        // Calcula el día de la semana

        // Guardar la fecha formateada en `crep`
        std::sprintf(crep, "%s %02d de %s de %04d",
                     dias_semana[timeinfo.tm_wday], di, meses[me - 1], ano);

        actual = true; // Marcar `crep` como actualizado
    }

    return crep;
}

void Fecha::aumentaFecha(int n)
{
    while (n > 0)
    {
        int dias_mes = diasEnMes(me, ano); // Obtener días en el mes actual

        if (di + n > dias_mes)
        {                             // Si sumamos días y nos pasamos del mes
            n -= (dias_mes - di + 1); // Restamos los días que faltan para cambiar de mes
            di = 1;                   // Reiniciamos el día al primero del siguiente mes
            me++;                     // Pasamos al siguiente mes

            if (me > 12)
            { // Si pasamos diciembre, avanzamos el año
                me = 1;
                ano++;

                if (ano >= AnnoMaximo)
                { // Validación de rango máximo
                    throw Invalida("Fecha fuera de rango");
                }
            }
        }
        else
        {
            di += n; // Si los días caben en el mes actual, los sumamos directamente
            n = 0;   // Terminamos la suma
        }
    }
}

void Fecha::disminuyeFecha(int n)
{
    while (n > 0)
    {
        if (di - n <= 0)
        {            // Si el día se vuelve 0 o negativo, cambiar de mes
            n -= di; // Restamos los días restantes de este mes
            me--;    // Pasamos al mes anterior

            if (me < 1)
            { // Si pasamos de enero, retrocedemos un año
                me = 12;
                ano--;

                if (ano < AnnoMinimo)
                { // Validación de rango mínimo
                    throw Invalida("Fecha fuera de rango: año inválido");
                }
            }

            di = diasEnMes(me, ano); // Asignamos el último día del mes anterior
        }
        else
        {
            di -= n; // Si los días caben en el mes actual, simplemente los restamos
            n = 0;   // Terminamos la resta
        }
    }
}
