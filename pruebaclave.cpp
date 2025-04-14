#include"usuario.hpp"


int main()
{
    Clave v("DANIELCASTILLO");

    cout<<"Clave cifrada: "<<v.clave()<<std::endl;

    Clave v2("DanielC");
    
    cout<<"Clave cifrada: "<<v2.clave()<<std::endl;

    if(v.verifica("DANIELCASTILLO"))
        cout<<"Contraseña correcta"<<endl; 

    if(!(v.verifica("danielcastillo")))
        cout<<"Contraseña en minúsculas incorrecta"<<endl;


    try
    {
        Clave v("123");
    }
    catch(const Clave::Incorrecta& e)
    {
        std::cerr << e.razon() << '\n';

        if(e.razon()==0)
            cout<<"Excepción: Contraseña demasiado Corta"<<endl;
    }
    


    return 0;

}

