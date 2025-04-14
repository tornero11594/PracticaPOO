#include"tarjeta.hpp"


//IMPLEMENTACIÓN DE LA CLASE TARJETA
Tarjeta::Tarjeta(const Numero&numerillo, Usuario&uuser,const Fecha&fechia,bool ac):num{numerillo},tit{&uuser},cad{fechia},activ{true}
{
    //comprobamos primero si la tarjeta está caducada
    Fecha hoy;

    if(cad<hoy)
    {
        Caducada I(cad);
        throw I;
    }

    else
    {
        //no está caducada, miramos si ya existe una tarjeta con ese número
        typedef set<Numero>::iterator iterador;
        std::pair<iterador,bool> res=conjuntotarjetas.insert(num);

        if(!res.second) //inserción fallida, lanzamos excepción de número duplicado
        {
            Num_duplicado I(num);
            throw I;
        }
        uuser.es_titular_de(*this);

    }
}

//métodos observadores
const Numero& Tarjeta::numero() const noexcept{return num;}
const Usuario* Tarjeta::titular() const noexcept{return tit;}
const Fecha& Tarjeta::caducidad() const noexcept{return cad;}
bool Tarjeta::activa() const noexcept{return activ;}
Tarjeta::Tipo Tarjeta::tipo() const noexcept
{   
    const char* cadena=num;

    if((cadena[0]=='3' && cadena[1]=='4') || (cadena[0]=='3' && cadena[1]=='7'))
    return AmericanExpress;

    else
    {
        if(cadena[0]=='3' && (cadena[1]!='7' && cadena[1]!='4'))
        return JCB;

        else 
        {
            if(cadena[0]=='4')
            return VISA;

            else
            {
                if(cadena[0]=='5')
                return Mastercard;

                else
                {
                    if(cadena[0]=='6')
                        return Maestro;

                    return Otro;
                }
            }

        }

    }
}

//Método para activar/desactivar una tarjeta
bool Tarjeta::activa(bool est) 
{
    activ=est;
    return activ;
}


//modificador para poner la tarjeta en false y el puntero de titular a nulo
void Tarjeta::anula_titular()
{
    activ=false;
    tit=nullptr;
    
}

//operador para mostrar la tarjeta por pantalla
ostream& operator<<(ostream&os, const Tarjeta&t)
{
    
    os<<t.tipo()<<endl;
    os<<t.num<<endl;
    os<<t.titular()->nombre() << " " << t.titular()->apellidos()<<endl;
    os<<"Caduca: "<<t.cad.mes()<<"/"<<t.cad.anno()%100<<endl;


    return os;
}

//comparar dos tarjetas
bool operator<(const Tarjeta&t1,const Tarjeta&t2)
{
    return(t1.num<t2.num);
}


//destructor que desvinculará al usuario
Tarjeta::~Tarjeta()
{
    if (tit) // si hay titular
    {
        const_cast<Usuario*>(tit)->no_es_titular_de(*this);
    }
    conjuntotarjetas.erase(num);
}





//IMPLEMENTACIÓN DE LA CLASE NÚMERO
Numero::Numero(Cadena& cad) //no inicializo porque puede ser incorrecto
{

    //depuración
    //cout<<cad.length()<<endl;

    if(cad.length() >=13 && cad.length()<=19) //comprobamos que cumpla el minimo
    {
        //primero, debemos quitar los espacios en blanco
        size_t j=0;
        for(size_t i=0;i<=cad.length();++i)
        {
            if(cad[i]!=' ') //solo movemos cuando no sea espacio
            {
                cad[j++]=cad[i];
            }
        }
        
        //depuración
        //cout<<cad.length()<<endl;
        //cout<<cad<<endl;
        //luego, hemos de ver si hay algún caracter no dígito
        bool flag=false;

        for(size_t i=0;i<cad.length() && !flag;++i ) //no tenemos en cuenta los espacios eliminados
        {
            if(!(isdigit(cad[i]))) //comprobamos si es un digito, si lo es lanzamos excepcion a partir de la bandera
            {
                flag=true;
            }
        }

        if(cad.length() <13) //comprobamos que cumpla el minimo al quitarle los espacios
        {
            Incorrecto I(LONGITUD);
            throw I;
        }


        if(flag)
        {
            Incorrecto I(DIGITOS);
            throw I;
        }

       //posteriormente comprobamos si el numero de tarjeta comprendido entre 13 y 19 caracteres sin letras es valido
        if(!luhn(cad))
        {
            Incorrecto I(NO_VALIDO);
            throw I;
        }

        else
        {
            num=cad;
        }

    }
    
    else
    {
        Incorrecto I(LONGITUD);
        throw I;
    }

}

Numero::operator const char*() const
{
   return num.operator const char *();

}



bool operator<(const Numero&n1, const Numero&n2)
{
    return(n1.num<n2.num);
}


Numero::Incorrecto::Incorrecto(Razon ra):raz{ra}
{}

Numero::Razon Numero::Incorrecto::razon() const noexcept
{
    return raz;
}


bool Numero::luhn(const Cadena&numero)
{
    size_t n = numero.length();
    size_t suma = 0;
    bool alt = false;
    for (int i = n - 1; i > -1; --i) {
      n = numero[size_t(i)] - '0';
      if (alt) {
        n *= 2;
        if (n > 9)
      n = (n % 10) + 1;
      }
      alt = !alt;
      suma += n;
    }
    return !(suma % 10);

}