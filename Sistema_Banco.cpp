#include <iostream>
#include <string>

using namespace std;
int opcion;

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
    cout <<"SI QUIERE CREAR UNA CUENTA INGRESE '2'\n";
    cin >> opcUsuario;

    
    if (opcUsuario == 2)
    {
        cout <<"INGRESE LOS DATOS PAA CREAR LA CUENTA";
    }
    else{
        cout <<"INGRESE SU NOMBRE DE USUARIO";
        Menu();
    }

    return 0;
}
