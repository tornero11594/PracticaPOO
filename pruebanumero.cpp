#include"tarjeta.hpp"
#include<iostream>
using namespace std;


int main()
{
    //ahora funciona bien
    try
    {
 
    Cadena C("4970100000000055");
    Numero n(C);

               
    }catch(const Numero::Incorrecto &e)
    {
        cout<<"Error: "<<e.razon(); 
    }

    cout<<"Numero de tarjeta correcto"<<endl;


    cout<<"Prueba con una segunda tarjeta válida:" <<endl;

    try
    {
 
    Cadena C2("4970 1000 0000 0063");
    Numero n(C2);

               
    }catch(const Numero::Incorrecto &e)
    {
        cout<<"Error: "<<e.razon()<<endl; 
        exit(1);
    }





    //4970100000000063

    return 0;
}


