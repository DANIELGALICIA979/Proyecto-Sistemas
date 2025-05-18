#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;
mutex mtx; //Sincronizacion de hilos dice el dipsik
int opcion;


struct Usuario
{
    string NomUsuario;
    string ContraUsuario;
    double Dinero;
};

vector <Usuario> usuarios;

//Simular proceso de transacciones
void procesarTransaccion(double cantidad, string tipoPlazo)
{
    int tiempo;
    if (tipoPlazo == "corto")
    {
        tiempo = 1; //Corto plazo    
    }
    else if (tipoPlazo == "mediano")
    {
        tiempo == 3; //mediano plazo 
    }
    else tiempo == 5; //largo plazo

    cout << "Procesando transaccion (" << tipoPlazo << " plazo) ..." << endl;
    this_thread::sleep_for(chrono::seconds(tiempo));
    mtx.lock();
    cout << "endl";
    cout << "Transaccion completada: $" << cantidad << " (" << tipoPlazo << " plazo)" << endl;
    mtx.unlock();
}

void ingresarDinero()
{
    string nombre;
    double cantidad;
    int plazo;

    cout << "INGRESE SU NOMBRE: ";
    
    cin>> nombre;
    
    while (true)
    {
        cout << "MONTO A INGRESAR: $";
        if (cin >> cantidad) break;
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Porfavor ingrese un numero." << endl; 
    
        }
    }
    
    cout << "SELECCIONE PLAZO (1. Corto, 2. Mediano, 3.Largo): ";
    cin >> plazo;

    string tipoPlazo;
    switch (plazo)
    {
    case 1: tipoPlazo = "corto";
        break;

    case 2: tipoPlazo = "mediano";
        break;

    case 3: tipoPlazo = "largo";
        break;

    default: tipoPlazo = "corto";
        break;
    }

    //Buscar al usuario
    for (auto& user : usuarios)
    {
        if (user.NomUsuario == nombre)
        {
            //Procesar hilo separado
            thread t(procesarTransaccion, cantidad, tipoPlazo);
            t.detach();
            //Actualizar saldo
            this_thread::sleep_for(chrono::milliseconds(500));
            user.Dinero += cantidad;

            cout << "Saldo actualizado. Nuevo saldo: $" << user.Dinero << endl;
            return;

        }
    }

    cout << "Usuario no encontrado!" << endl;
}

void CreacionCuenta(){
    Usuario NuevoUSUARIO;
    cout <<"INGRESE SU NOMBRE"<<endl;
    cin >> NuevoUSUARIO.NomUsuario;
    cout <<"INGRESE SU CONTRASEÑA"<<endl;
    cin >> NuevoUSUARIO.ContraUsuario;
    usuarios.push_back(NuevoUSUARIO);
}

void VusualizarUser(){
    string Nombre;
    cout <<"INGRESE EL NOMBRE A BUSCAR: ";
    cin >> Nombre;

    for(Usuario&user : usuarios)
    if (user.NomUsuario == Nombre)
    {
        cout <<"Bienvenido: "<<Nombre<<endl;
    }
    else
    {
        cout <<"NOMBRE NO EXISTENTE"<<endl;
    }

}

void Menu(){
    while (true) {
        cout << "MENU DE ACCIONES: " << endl;;
        cout << "1. INGRESAR DINERO." << endl;
        cout << "2. RETIRAR DINERO."<< endl;
        cout << "3. DEPSOTIAR A UNA CUENTA."<< endl;
        cout << "4. AGREGAR CONTACTOS."<< endl;
        cout << "5. DAR DE BAJA LA CUENTA."<< endl;
        cout << "6. SALIR."<< endl;
        cout << "DIGITE LA OPCION QUE DESEE REALIZAR: ";

        cin >> opcion;
        switch (opcion)
        {
        case 1:
            ingresarDinero();
            break;
            
        case 2:
            cout << "RETIRAR DINERO"<<endl;
            break;

        case 3:
            cout << "DEPOSITAR A UNA CUENTA" <<endl;
            break;
        
        case 4:
            cout << "AGREGAR CONTACTOS" <<endl;
            break;

        case 5:
            cout << "DAR DE BAJA LA CUENTA" <<endl;
            break;

        case 6:
            cout << "SALIR" <<endl;
            return;
            
        default: cout << "SELECCIONE UNA OPCION VALIDA!!" <<endl;
            break;
        }
    }
}

int main() {
    int opcUsuario;

    Usuario user1;
    user1.NomUsuario = "Daniel";
    user1.ContraUsuario = "1234";
    user1.Dinero = 0.00;
    usuarios.push_back(user1);

    cout << "BIENVENIDO"<<endl;

    cout <<"SELECCIONE SU TIPO DE USUARIO:"<<endl;
    cout <<"SI YA TIENE CUENTA INGRESE '1'"<<endl;
    cout <<"SI QUIERE CREAR UNA CUENTA NUEVA INGRESE '2'"<<endl;
    cin >> opcUsuario;

    if (opcUsuario == 1)
    {
        cout <<"VERIFICACION DE LA CUENTA"<<endl;
        VusualizarUser();
        Menu();
    }
    else if (opcUsuario == 2)
    {
        cout <<"REGISTRO DE USUARIO NUEVO"<<endl;
        CreacionCuenta();
        Menu();
    }
    

    return 0;
}
