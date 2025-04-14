#include"usuario.hpp"
#include"tarjeta.hpp"


//IMPLEMENTACIÓN DE LA CLASE USUARIO
//Constructor
Usuario::Usuario(const Cadena& iden,const Cadena& nombr,const Cadena& apelli,const Cadena& direcc,const Clave& cl):ident{iden},nom{nombr},apell{apelli},dir{direcc},contrasena{cl}
{
    //vamos a comprobar antes de inicializar si un usuario está duplicado
    typedef unordered_set<Cadena>::iterator iterador;
    std::pair<iterador,bool> res=ids.insert(ident); 
    if(!res.second) //la insercion no se ha llevado a cabo correctamente
    {
        Id_duplicado I(ident); //corregir este error
        throw I;
    }
}



//Metodos observadores
const Cadena& Usuario::id() const noexcept{return ident;}
const Cadena& Usuario::nombre() const noexcept{return nom;}
const Cadena& Usuario::apellidos() const noexcept{return apell;}
const Cadena& Usuario::direccion() const noexcept{return dir;}
const Usuario::Articulos& Usuario::compra() const noexcept {return art;}


void Usuario::es_titular_de(Tarjeta& tar)
{
    tarjetas_.insert(make_pair(tar.numero(),&tar)); //insertamos la tarjeta en el diccionario
}


void Usuario::no_es_titular_de(Tarjeta& tar)
{
    tarjetas_.erase(tar.numero()); //borramos por numero de la tarjeta
    tar.anula_titular();
}



//Metodo para asociacion con Artículo
void Usuario::compra(Articulo& artic, size_t cantidad)
{
    Articulo* p=&artic;


    if(cantidad==0) //eliminamos los ariticulos del carrito
    {
        art.erase(p);
    }

    else    
    {
        auto resultado=art.insert({p,cantidad});

        if(!resultado.second)
            resultado.first->second=cantidad;

    }

}


//método para vaciar el carro
void Usuario::vaciar_carro()
{
    art.clear();    
}


 //numero de artículos en el carrito del usuario
size_t Usuario::n_articulos() const noexcept
{
    return art.size();
}


//Imprimir info de un usuario por pantalla
ostream& operator<<(ostream&os, const Usuario& user)
{
    os<<user.ident<<" [" <<user.contrasena<<"] "<<user.nom<<" "<<user.apell<< endl;
    os<<user.dir<<endl;
    os<<"Tarjetas:"<<endl;

    auto it=user.tarjetas_.begin();
    while(it!=user.tarjetas_.end()) //recorremos las tarjetas de un usuario para imprimirlas
    {
        os<<*it->second<<endl;
        ++it;
    }

    return os;
}




Usuario::~Usuario()
{
    auto it=tarjetas_.begin();    

    while(it!=tarjetas_.end())
    {
            it->second->anula_titular();
            it++;
    }

    ids.erase(ident); //eliminamos al usuario del conjunto
}



//IMPLEMENTACIÓN DE LA CLASE PARA EXCEPCIONES
Usuario::Id_duplicado::Id_duplicado(const Cadena&dup):identifdupl{dup}
{}
const Cadena& Usuario::Id_duplicado::idd() const noexcept{return identifdupl;}


     

void mostrar_carro(const Usuario::Articulos&a, const Usuario& user)
{
    cout<<"Carrito de compra de "<<user.ident<<" [Articulos]"<<a.size()<<endl;
    cout<<"Cant. Artículo"<<endl;
    cout<<"==========================================================="<<endl;

    auto it=user.art.begin();

    while(it!=user.art.end())
    {
        cout<<*it->first<<endl; //imprimimos las tarjetas
    }

}





//IMPLEMENTACIÓN DE LA CLASE Clave
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

ostream& operator<<(ostream&os,const Clave&clav)
{
    os<<clav.clavecifrada;
    return os;
}
