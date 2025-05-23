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
    double Dinero = 0.0;
    bool premium = false;
    vector <string> contactos;
};

vector <Usuario> usuarios;

//funciones prototipo xd
void procesarTransaccion(double cantidad, string tipoPlazo);
void ingresarDinero(Usuario& usuarioActual);
void agregarContactos(Usuario& usuarioActual);
Usuario* VisualizarUser();
Usuario* CreacionCuenta();
void ConsultarDinero(Usuario &usuario);
void Menu(Usuario& usuarioActual);
void accesoVentanilla();
void accesoAsesor();
Usuario* acceso();
Usuario* autenticacion();
void depositarDinero(Usuario &usuarioActual);


int main() {
    // Usuario de prueba (como en tu código original)
    Usuario user1;
    Usuario user2;
    Usuario user3;
    Usuario user4;
    Usuario user5;

    user1.NomUsuario = "Daniel";
    user1.ContraUsuario = "1234";
    user1.Dinero = 1500.00;
    user1.premium = true;

    user2.NomUsuario = "Juan";
    user2.ContraUsuario = "1234";
    user2.Dinero = 1500.00;
    
    user3.NomUsuario = "David";
    user3.ContraUsuario = "1234";
    user3.Dinero = 1500.00;
    user3.premium = true;

    user4.NomUsuario = "Alan";
    user4.ContraUsuario = "1234";
    user4.Dinero = 1500.00;
    user4.premium = false;

    user5.NomUsuario = "Francisco";
    user5.ContraUsuario = "1234";
    user5.Dinero = 1500.00;
    user5.premium = true;

    usuarios.push_back(user1);
    usuarios.push_back(user2);
    usuarios.push_back(user3);
    usuarios.push_back(user4);
    usuarios.push_back(user5);

    // Obtenemos el usuario autenticado
    Usuario* usuarioActual = acceso();
    
    if (usuarioActual != nullptr) {
        cout << "\nBienvenido al sistema, " << usuarioActual->NomUsuario << "!" << endl;

        // Pasamos el usuario al menú
        Menu(*usuarioActual);
    } else {
        cout << "Sesión terminada." << endl;
    }

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
    cout << "\nTransaccion completada: $" << cantidad << " (" << tipoPlazo << " plazo)" << endl;
    mtx.unlock();
}

void ingresarDinero(Usuario& usuarioActual) {
    double cantidad;
    int plazo;

    while (true) {
        cout << "MONTO A INGRESAR: $";
        if (cin >> cantidad) break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida. Por favor ingrese un número." << endl;
    }
    
    cout << "SELECCIONE PLAZO (1. Corto, 2. Mediano, 3. Largo): ";
    cin >> plazo;

    string tipoPlazo;
    switch (plazo) {
        case 1: tipoPlazo = "corto"; break;
        case 2: tipoPlazo = "mediano"; break;
        case 3: tipoPlazo = "largo"; break;
        default: tipoPlazo = "corto"; break;
    }

    // Procesar en hilo separado
    thread t(procesarTransaccion, cantidad, tipoPlazo);
    t.detach();
    
    // Actualizar saldo
    this_thread::sleep_for(chrono::milliseconds(500));
    usuarioActual.Dinero += cantidad;

    cout << "Saldo actualizado. Nuevo saldo: $" << usuarioActual.Dinero << endl;
}

Usuario* VisualizarUser() {
    string Nombre;
    string Contrasena;
    cout << "INGRESE SU NOMBRE DE USUARIO: " << endl;
    cin >> Nombre;
    cout << "INGRESE SU CONTRASEÑA: " << endl;
    cin >> Contrasena;

    for (auto& user : usuarios) {
        if (user.NomUsuario == Nombre && user.ContraUsuario == Contrasena) {
            return &user; // Devuelve un puntero al usuario encontrado
        }
    }
    cout << "CREDENCIALES INCORRECTAS O USUARIO NO EXISTENTE" << endl;
    return nullptr; // Devuelve nullptr si no se encuentra
}

Usuario* CreacionCuenta() {
    Usuario NuevoUSUARIO;
    cout << "INGRESE SU NOMBRE: " << endl;
    cin >> NuevoUSUARIO.NomUsuario;
    cout << "INGRESE SU CONTRASEÑA: " << endl;
    cin >> NuevoUSUARIO.ContraUsuario;
    NuevoUSUARIO.Dinero = 0.0;
    usuarios.push_back(NuevoUSUARIO);
    return &usuarios.back(); // Devuelve un puntero al último usuario agregado
}

void Menu(Usuario& usuarioActual) {
    while (true) {
        cout << "\nMENU DE ACCIONES: " << endl;
        cout << "1. INGRESAR DINERO." << endl;
        cout << "2. CONSULTAR SALDO." << endl;
        cout << "3. RETIRAR DINERO." << endl;
        cout << "4. DEPOSITAR A UNA CUENTA." << endl;
        cout << "5. AGREGAR CONTACTOS." << endl;
        cout << "6. DAR DE BAJA LA CUENTA." << endl;
        cout << "7. SALIR." << endl;
        cout << "DIGITE LA OPCION QUE DESEE REALIZAR: ";

        cin >> opcion;
        switch (opcion) {
        case 1:
            ingresarDinero(usuarioActual);
            break;

        case 2:
            ConsultarDinero(usuarioActual);
            break;
        case 3:
            
            break;
        case 4:
            depositarDinero(usuarioActual);
            break;
        case 5:
            agregarContactos(usuarioActual);
            break;
        case 6:
            
            break;
        case 7:
            return;
        default:
            cout << "Selecciona una opcion valida." << endl;
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

Usuario* acceso() {
    int opcInicial;
    cout << "====================================" << endl;
    cout << "   SISTEMA BANCARIO - BIENVENIDO    " << endl;
    cout << "====================================" << endl;
    cout << "1. Asignacion de ventanilla" << endl;
    cout << "2. Asignacion de asesor" << endl;
    cout << "3. Acceder al sistema" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcInicial;

    switch (opcInicial) {
    case 1:
        accesoVentanilla();
        return nullptr;  // No hay usuario en este caso
    case 2:
        accesoAsesor();
        return nullptr;  // No hay usuario en este caso
    case 3:
        return autenticacion();  // Devuelve el usuario autenticado
    default:
        cout << "Opcion no valida. Intente nuevamente." << endl;
        return acceso();  // Llamada recursiva
    }
}

Usuario* autenticacion() {
    int opcUsuario;
    system("clear");
    cout << "SELECCIONE SU TIPO DE USUARIO: " << endl;
    cout << "1. Acceso con cuenta existente." << endl;
    cout << "2. Registro de nuevo cliente." << endl;
    cout << "Opcion: ";
    cin >> opcUsuario;

    switch (opcUsuario) {
    case 1:
        return VisualizarUser();  // Devuelve el usuario encontrado
    case 2:
        return CreacionCuenta(); // Devuelve el nuevo usuario
    default:
        cout << "Por favor digite una opcion valida!" << endl;
        return autenticacion();  // Llamada recursiva
    }
}

void ConsultarDinero(Usuario& usuarioActual){
    double Money;
    cout << "REVISANDO SALDO DISPONIBLE" <<endl;
    cout << "SU SALDO ACTUAL ES: " << usuarioActual.Dinero <<endl;
}

void agregarContactos(Usuario& usuarioActual)
{
    string nombreContacto;
    cout << "Ingresa el nombre del contacto a agregar: ";
    cin >> nombreContacto;

    if (nombreContacto == usuarioActual.NomUsuario)
    {
        cout << "No puedes agregarte a ti mismo como contacto." << endl;
        return;
    }

    for (const auto& contacto : usuarioActual.contactos)
    {
        if (contacto == nombreContacto)
        {
            cout << "Este contacto ya existe en tu lista" << endl;
            return;
        }
    }

    bool usuarioExiste = false;
    for (const auto user : usuarios)
    {
        if (user.NomUsuario == nombreContacto)
        {
            usuarioExiste = true;
            break;
        }
    }
    
    if (usuarioExiste)
    {
        usuarioActual.contactos.push_back(nombreContacto);
        cout << "Haz  agregado exitosamente a : " << nombreContacto << endl;
        cout << "\nTus contactos:" << endl;
        for (const auto& contacto : usuarioActual.contactos)
        {
            cout << "- " << contacto << endl;
        }
    }
    else
    {
        cout << "El usuario '" << nombreContacto << "' no existe en el sistema." << endl; 
    }
}

void depositarDinero(Usuario &usuarioActual)
{
    double cantidad;
    int plazo;
    bool esContacto = false;
    string nombreContacto;
    cout << "Ingresa el nombre del contacto al que vas a depositar: ";
    cin >> nombreContacto;
    for (const auto contacto : usuarioActual.contactos)
    {
        if (contacto == nombreContacto)
        {
            esContacto = true;
            break;
        }
    }

    if (esContacto)
    {
        cout << "\nDigita la cantidad que vas a depositar: $";
        cin >> cantidad;
        if (cantidad > usuarioActual.Dinero)
        {
            cout << "Fondos insuficientes para realizar el deposito." << endl;
            return;
        }
        else
        {
            usuarioActual.Dinero -= cantidad;
            procesarTransaccion(cantidad, "mediano");
        }    
    }
    else
    {
        cout << "El usuario " << nombreContacto << " no es tu contacto o no existe en el sistema." << endl;
    }
}

