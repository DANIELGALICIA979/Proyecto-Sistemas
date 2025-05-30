#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <condition_variable>
#include <future>

using namespace std;

struct Usuario
{
    string NomUsuario;
    string ContraUsuario;
    double Dinero = 0.0;
    bool premium = false;
    vector <string> contactos;
};

//es para simular los demas clientes en la fila
struct ClienteEnEspera 
{
    string nombre;
    int tiempoEstimado; 
};

mutex mtx; //Sincronizacion de hilos
int opcion;
vector <Usuario> usuarios;
queue<pair<double, bool>> colaTransacciones;
mutex mtxCola;
condition_variable cv;
bool detenerSimulacion = false;

//funciones prototipo xd
void procesadorTransacciones();
void detenerProcesador();
void iniciarTransaccion(double cantidad, bool esPremium);
void procesarTransaccion(double cantidad, bool esPremium);
void ingresarDinero(Usuario& usuarioActual);
void RetirarDinero(Usuario& usuarioActual);
void agregarContactos(Usuario& usuarioActual);
Usuario* verificarUsuario();
Usuario* CreacionCuenta();
void ConsultarDinero(Usuario &usuario);
void Menu(Usuario& usuarioActual);
void asignarVentanilla();
void accesoAsesor();
Usuario* acceso();
Usuario* autenticacion();
void depositarDinero(Usuario &usuarioActual);
void TarjetaT();
void EliminarCuenta(Usuario& usuarioActual);


int main() 
{
    Usuario user1;
    Usuario user2;
    Usuario user3;
    Usuario user4;
    Usuario user5;

    user1.NomUsuario = "Daniel";
    user1.ContraUsuario = "1234";
    user1.Dinero = 1500.00;

    user2.NomUsuario = "Juan";
    user2.ContraUsuario = "1111";
    user2.Dinero = 1500.00;
    
    user3.NomUsuario = "David";
    user3.ContraUsuario = "1234";
    user3.Dinero = 1500.00;
    user3.premium = true;

    user4.NomUsuario = "Alan";
    user4.ContraUsuario = "1234";
    user4.Dinero = 1500.00;

    user5.NomUsuario = "Francisco";
    user5.ContraUsuario = "1234";
    user5.Dinero = 1500.00;

    usuarios.push_back(user1);
    usuarios.push_back(user2);
    usuarios.push_back(user3);
    usuarios.push_back(user4);
    usuarios.push_back(user5);

    // Obtenemos el usuario autenticado
    Usuario* usuarioActual = acceso();
    
    if (usuarioActual != nullptr) 
    {
        cout << "\nBienvenido al sistema, " << usuarioActual->NomUsuario << "!" << endl;

        // Pasamos el usuario al menú
        Menu(*usuarioActual);
    } 
    else 
    {
        cout << "Sesión terminada." << endl;
    }

    return 0;
}

void procesadorTransacciones() 
{
    while (true) 
    {
        unique_lock<mutex> lock(mtxCola);
        cv.wait(lock, []{ return !colaTransacciones.empty() || detenerSimulacion; });
        
        if (detenerSimulacion) break;

        // Extraer transacción (prioridad a premium)
        auto transaccion = colaTransacciones.front();
        colaTransacciones.pop();
        lock.unlock();

        // Calcular tiempo según prioridad
        int tiempo = transaccion.second ? 1 : 3; // Premium: 1s, Normal: 3s

        // Procesar (sin mostrar detalles internos)
        this_thread::sleep_for(chrono::seconds(tiempo));
        
        mtx.lock();
        cout << "\nTransacción completada: $" << transaccion.first 
             << (transaccion.second ? " (Cliente Premium)" : "") << endl;
        mtx.unlock();
    }
}

// Función para detener
void detenerProcesador() {
    {
        lock_guard<mutex> lock(mtxCola);
        detenerSimulacion = true;
    }
    cv.notify_all();
}

// Función para iniciar transacciones
void iniciarTransaccion(double cantidad, bool esPremium) 
{
    lock_guard<mutex> lock(mtxCola);
    colaTransacciones.push({cantidad, esPremium});
    cv.notify_one();
}

//Simular proceso de transacciones
// Modificar la función original para usar el sistema
void procesarTransaccion(double cantidad, bool esPremium) 
{
    // Tiempos basados solo en prioridad
    int tiempo = esPremium ? 1 : 3; // Premium: 1s, Normal: 3s
    
    // Simulación del procesamiento
    this_thread::sleep_for(chrono::seconds(tiempo));
    
    // Bloqueo para salida segura
    lock_guard<mutex> lock(mtx);
    cout << "\nTransacción de $" << cantidad << " completada"  << (esPremium ? " [PRIORIDAD PREMIUM]" : "") << endl;
}

void ingresarDinero(Usuario& usuarioActual) 
{
    
    double cantidad;
    while (true) {
        cout << "MONTO A INGRESAR: $";
        if (cin >> cantidad) break;
        // ... (manejo errores)
    }
    
    system("clear");
    auto resultado = async(launch::async, [cantidad, esPremium = usuarioActual.premium]{
        int tiempo = esPremium ? 1 : 3;
        this_thread::sleep_for(chrono::seconds(tiempo));
        lock_guard<mutex> lock(mtx);
        //cout << "\n[✓] Transacción de $" << cantidad << " completada\n";
    });
    
    cout << "Procesando... (espere)";
    procesarTransaccion(cantidad, usuarioActual.premium);
    resultado.get(); // Bloquea hasta terminar
    
    usuarioActual.Dinero += cantidad; // Actualizar saldo
    cout << "\nNuevo saldo: $" << usuarioActual.Dinero << endl;
    //system("clear");
}

Usuario* verificarUsuario() 
{
    string Nombre;
    string Contrasena;
    cout << "INGRESE SU NOMBRE DE USUARIO: " << endl;
    cin >> Nombre;
    cout << "INGRESE SU CONTRASEÑA: " << endl;
    cin >> Contrasena;

    for (auto& user : usuarios) 
    {
        if (user.NomUsuario == Nombre && user.ContraUsuario == Contrasena) 
        {
            return &user; // Devuelve un puntero al usuario encontrado
        }
    }
    cout << "CREDENCIALES INCORRECTAS O USUARIO NO EXISTENTE" << endl;
    return nullptr; // Devuelve nullptr si no se encuentra
}

Usuario* CreacionCuenta() 
{
    Usuario NuevoUSUARIO;
    cout << "INGRESE SU NOMBRE: " << endl;
    cin >> NuevoUSUARIO.NomUsuario;
    cout << "INGRESE SU CONTRASEÑA: " << endl;
    cin >> NuevoUSUARIO.ContraUsuario;
    NuevoUSUARIO.Dinero = 0.0;
    usuarios.push_back(NuevoUSUARIO);
    return &usuarios.back(); // Devuelve un puntero al último usuario agregado
}

void Menu(Usuario& usuarioActual) 
{
    while (true) 
    {
        //system("clear");
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
        switch (opcion) 
        {
        case 1:
            ingresarDinero(usuarioActual);
            break;
        case 2:
            ConsultarDinero(usuarioActual);
            break;
        case 3:
            RetirarDinero(usuarioActual);
            break;
        case 4:
            depositarDinero(usuarioActual);
            break;
        case 5:
            agregarContactos(usuarioActual);
            break;
        case 6:
            EliminarCuenta(usuarioActual);
            if (usuarioActual.NomUsuario.empty()) 
            { 
                acceso();
                return;
            }
            break; // Si se canceló, continúa en el menú
        case 7:
            cout << "Sesion cerrada. Hasta la proxima." << endl;
            return;
        default:
            cout << "Selecciona una opcion valida." << endl;
            break;
        }
    }
}

//con algoritmo Shortest Job First 
void asignarVentanilla() 
{
    system("clear");
    
    int N = rand()% 6 + 1;
    
    vector<ClienteEnEspera> cola = {{"Daniel", N},{"David", N},{"Alan", N},{"Francisco", N}};
    
    ClienteEnEspera NuevoCLIENTE = {"NuevoCLIENTE", N}; // Cambia el número según necesites
    cola.push_back(NuevoCLIENTE);


    // Ordenar por tiempo 
    sort(cola.begin(), cola.end(), [](const ClienteEnEspera& a, const ClienteEnEspera& b) 
    {
        return a.tiempoEstimado < b.tiempoEstimado;
    });

    // Simular atención por ventanilla 
    int ventanilla = 1;
    for (auto& cliente : cola) 
    {
        cout << "\n" << cliente.nombre << " AVANZE A VENTANILLA " << ventanilla << endl;
        cout << "EN VENTANILLA......."<<endl;
        this_thread::sleep_for(chrono::seconds(5));//simulacion del tiempo en ventanilla
        cout << "CLIENTE " << cliente.nombre << " ATENDIDO." << endl;
        ventanilla = (ventanilla % 5) + 1; // cambia entre ventanillas 1 a 5
    }
}

void accesoAsesor()
{
    system("clear");
    srand(time(0));
    int opc;
    cout << "BIENVENIDO SELECCIONE SU TIPO DE CUENTA" <<endl;
    cout << "1 CUENTA PREFERENCIAL"<<endl;
    cout << "2 CUENTA ESTANDAR"<<endl;
    cout << "---------------------" << endl;
    cin >> opc;
    
    
    if(opc == 1)
    {
        cout << "\nSE LE HA ASIGNADO CON NUESTRO ASESOR ALEJANDRO RUIZ"<<endl;
    }
    if(opc == 2)
    {
        vector<string> asesores = {"JUAN PEREZ", "MARIA GARCIA", "CARLOS LOPEZ"};
        int numAsesor = rand() % 3 + 1; //Numero aleatorio entre 1 y 3
        switch (numAsesor)
        {
        case 1:
            system("clear");
            cout << "SE LE HA ASIGNADO AL ASESOR" << asesores[numAsesor-1] << endl;
            break;
        case 2:
            system("clear");
            cout << "SE LE HA ASIGNADO A LA ASESORA: " << asesores[numAsesor-1] << endl;
            break;
        
        case 3:
            system("clear");
            cout << "SE LE HA ASIGNADO AL ASESOR: " << asesores[numAsesor-1] << endl;
            break;
            
        default:    
            cout << "SE LE HA ASIGNADO AL ASESOR: " << asesores[0] << endl;
            break;
        }
    }
}

Usuario* acceso() 
{
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
        asignarVentanilla();
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

Usuario* autenticacion() 
{
    int opcUsuario;
    system("clear");
    cout << "SELECCIONE SU TIPO DE USUARIO: " << endl;
    cout << "1. Acceso con cuenta existente." << endl;
    cout << "2. Registro de nuevo cliente." << endl;
    cout << "3. Operar con tarjeta temporal" << endl;
    cout << "Opcion: ";
    cin >> opcUsuario;

    switch (opcUsuario) 
    {
    case 1:
        return verificarUsuario();  // Devuelve el usuario encontrado
    case 2:
        return CreacionCuenta(); // Devuelve el nuevo usuario
    case 3:
        TarjetaT();
        return nullptr;
    default:
        cout << "Por favor digite una opcion valida!" << endl;
        return autenticacion();  // Llamada recursiva
    }
}

void TarjetaT()
{
    string nameT;
    double CantidadT;
    double CantidadINI;
    cout << "INGRESE LA CANTIDAD QUE VA A TENER LA TARJETA TEMPORAL" << endl;
    cin >> CantidadINI;
    cout << "INGRESE EL NOMBRE DE USUARIO A DEPOSITAR"<< endl;
    cin >> nameT;

    for (auto& user : usuarios) 
    {
        if (user.NomUsuario == nameT) 
        {
            cout << "INGRESE LA CANTIDAD A DEPOSITAR" << endl;
            cin >> CantidadT;
            user.NomUsuario += CantidadT;
            CantidadINI -= CantidadT;
            cout << "SU SALDO DISPONIBLE ES: " << CantidadINI << endl;
        }
    }
}

void ConsultarDinero(Usuario& usuarioActual)
{
    system("clear");
    double Money;
    cout << "REVISANDO SALDO DISPONIBLE" <<endl;
    cout << usuarioActual.NomUsuario << " tu saldo actual es: $" << usuarioActual.Dinero <<endl;
}

void agregarContactos(Usuario& usuarioActual)
{
    system("clear");
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
    system("clear");
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
            procesarTransaccion(cantidad, usuarioActual.premium);
        }    
    }
    else
    {
        cout << "El usuario " << nombreContacto << " no es tu contacto o no existe en el sistema." << endl;
    }
}

void RetirarDinero(Usuario& usuarioActual) 
{
    double DineroRET;
    cout << "INGRESE LA CANTIDAD QUE DESEA RETIRAR: ";
    cin >> DineroRET;

    if (DineroRET <= 0) 
    {
        cout << "CANTIDAD NO VALIDA. INGRESE UN MONTO POSITIVO." << endl;
    } 
    else if (DineroRET <= usuarioActual.Dinero) 
    {
        usuarioActual.Dinero -= DineroRET;
        cout << "RETIRO EXITOSO" << endl;
    } 
    else 
    {
        cout << "FONDOS INSUFICIENTES" << endl;
    }
}

void EliminarCuenta(Usuario& usuarioActual) 
{
    int opcion;
    cout << "\n=== CONFIRMACIÓN DE ELIMINACIÓN ===" << endl;
    cout << "1. CONFIRMAR ELIMINACIÓN" << endl;
    cout << "2. CANCELAR" << endl;
    cout << "Su elección: ";
    cin >> opcion;

    switch(opcion) 
    {
    case 1:
        {
            auto it = find_if(usuarios.begin(), usuarios.end(),[&usuarioActual](const Usuario& u) {return u.NomUsuario == usuarioActual.NomUsuario;});

            if (it != usuarios.end()) 
            {
                usuarios.erase(it);
                cout << "\nCuenta eliminada correctamente." << endl;
                usuarioActual = Usuario(); // Resetear usuario
            } 
            else 
            {
                cout << "\nError: cuenta no encontrada." << endl;
            }
            break;
        }

    case 2:
        cout << "\nOperación cancelada. Volviendo al menú..." << endl;
        return;
    default:
        cout << "\nOpción inválida." << endl;
    }

    // Si llegamos aquí y el usuario fue eliminado, forzar cierre
    if (usuarioActual.NomUsuario.empty()) 
    {
        cout << "\nSesión finalizada por eliminación de cuenta." << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
}