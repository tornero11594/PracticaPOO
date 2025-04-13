#include"tarjeta.hpp"

Numero::Numero(Cadena& cad) //no inicializo porque puede ser incorrecto
{

    //depuración
    //cout<<cad.length()<<endl;

    if(cad.length() >=13 && cad.length()<=19) //comprobamos que no esté vacía
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