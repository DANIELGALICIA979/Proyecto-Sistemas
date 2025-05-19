#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <cstdlib>
#include <ctime>

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

//funciones prototipo xd
void procesarTransaccion(double cantidad, string tipoPlazo);
void ingresarDinero();
void CreacionCuenta();
void VisualizarUser();
void Menu();
void accesoVentanilla();
void accesoAsesor();
void acceso();
void autenticacion();


int main() {
    
    Usuario user1;
    user1.NomUsuario = "Daniel";
    user1.ContraUsuario = "1234";
    user1.Dinero = 0.00;
    usuarios.push_back(user1);

    acceso();

    
    

    return 0;
}


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

    cout << "INGRESE SU NOMBRE DE USUARIO: ";
    
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
    cout <<"INGRESE SU NOMBRE: "<<endl;
    cin >> NuevoUSUARIO.NomUsuario;
    cout <<"INGRESE SU CONTRASEÑA: "<<endl;
    cin >> NuevoUSUARIO.ContraUsuario;
    usuarios.push_back(NuevoUSUARIO);
}

void VisualizarUser(){
    string Nombre;
    cout <<"INGRESE SU NOMBRE DE USUARIO: ";
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

void accesoVentanilla()
{
    system("clear");
    srand(time(0));
    int ventanilla = rand() % 5 + 1; //Numero aleatorio entre 1 y 5
    system("clear");
    cout << "Favor de pasar a ventanilla numero: " << ventanilla << endl;
}

void accesoAsesor()
{
    system("clear");
    srand(time(0));
    vector<string> asesores = {"Juan Perez", "Maria Garcia", "Carlos Lopez"};
    int numAsesor = rand() % 3 + 1; //Numero aleatorio entre 1 y 3
    switch (numAsesor)
    {
    case 1:
        system("clear");
        cout << "Pase con el asesor" << asesores[numAsesor-1] << endl;
        break;
    case 2:
        system("clear");
        cout << "Pase con la asesora: " << asesores[numAsesor-1] << endl;
        break;
    
    case 3:
        system("clear");
        cout << "Pase con el asesor: " << asesores[numAsesor-1] << endl;
        break;
        
    default:    
        cout << "Pase con el asesor: " << asesores[0] << endl;
        break;
    }
}

void acceso(){
    int opcInicial;
    cout << "====================================" << endl;
    cout << "   SISTEMA BANCARIO - BIENVENIDO    " << endl;
    cout << "====================================" << endl;
    cout << "1. Asignacion de ventanilla" << endl;
    cout << "2. Asignacion de asesor" << endl;
    cout << "3. Acceder al sistema" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcInicial;

    switch (opcInicial)
    {
    case 1:
        accesoVentanilla();
        break;

    case 2:
        accesoAsesor();
        break;
    
    case 3:
        autenticacion();
        Menu();
        break;
    
    default:
        cout << "Opcion no valida. Intente nuevamente." << endl;
        acceso();
        break;
    }
}

void autenticacion()
{
    int opcUsuario;
    system("clear");
    cout << "SELECCIONE SU TIPO DE USUARIO: " << endl;
    cout << "1. Acceso con cuenta existente." << endl;
    cout << "2. Registro de nuevo cliente." << endl;
    cout << "Opcion: ";
    cin >> opcUsuario;

    switch (opcUsuario)
    {
    case 1:
        VisualizarUser();
        break;
    
    case 2:
        CreacionCuenta();
        break;
    default:
        cout << "Porfavor digite una opcion valida!"<< endl;
        cout << endl;
        autenticacion();
        break;
    }
}


