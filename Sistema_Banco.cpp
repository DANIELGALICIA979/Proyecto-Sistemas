#include <iostream>
#include <string>
#include <vector>

using namespace std;
int opcion;

struct Usuario
{
    string NomUsuario;
    string ContraseñaUsuario;
};

vector <Usuario> usuario;

void CreacionCuenta(){
    cout <<"INGRESE SU NOMBRE";
}

void Menu(){
    while (true) {
        cout << "\nSELECCIONE LA ACCION DESEA REALIZAR\n";
        cin >> opcion;
        switch (opcion)
            {
            case 1:
                cout << "INGRESAR DINERO";
                break;
            
            case 2:
                cout << "RETIRAR DINERO";
                break;

            default: cout << "SELECCIONE UNA OPCION VALIDA!!";
                break;
            }
        }
}

int main() {
    int opcUsuario;

    cout << "BIENVENIDO\n";

    cout <<"SELECCIONE SU TIPO DE USUARIO:\n";
    cout <<"SI YA TIENE CUENTA INGRESE '1'\n";
    cout <<"SI QUIERE CREAR UNA CUENTA NUEVA INGRESE '2'\n";
    cin >> opcUsuario;

    
    if (opcUsuario == 1)
    {
        cout <<"VERIFICACION DE LA CUENTA";
    }
    else{
        cout <<"REGISTRO DE USUARIO NUEVO";
        Menu();
    }

    return 0;
}
