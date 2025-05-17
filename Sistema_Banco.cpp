#include <iostream>
#include <string>
#include <vector>

using namespace std;
int opcion;

struct Usuario
{
    string NomUsuario;
    string ContraUsuario;
    string Dinero;
};

vector <Usuario> usuario;

// Usuario user1;
// user1.NomUsuario = "Daniel";


void CreacionCuenta(){
    Usuario NuevoUSUARIO;
    cout <<"\nINGRESE SU NOMBRE\n";
    cin >> NuevoUSUARIO.NomUsuario;
    cout <<"\nINGRESE SU CONTRASEÑA";
    cin >> NuevoUSUARIO.ContraUsuario;
    usuario.push_back(NuevoUSUARIO);
}

void VusualizarUser(){
    string Nombre;
    cout <<"\nINGRESE EL NOMBRE A BUSCAR";
    cin >> Nombre;


    for(Usuario&user : usuario)
        if (user.NomUsuario == Nombre)
        {
            cout <<"\nNOMBRE ENCONTRADO";
        }
        else
        {
            cout <<"\nNOMBRE NO EXISTENTE";
        }
        
        

}

void Menu(){
    while (true) {
        cout << "\nSELECCIONE LA ACCION DESEA REALIZAR\n";
        cin >> opcion;
        switch (opcion)
            {
            case 1:
                cout << "\nINGRESAR DINERO\n";
                break;
            
            case 2:
                cout << "\nRETIRAR DINERO\n";
                break;

            default: cout << "\nSELECCIONE UNA OPCION VALIDA!!\n";
                break;
            }
        }
}

int main() {
    int opcUsuario;

    // Example of initializing a user (if needed)
    Usuario user1;
    user1.NomUsuario = "Daniel";
    user1.ContraUsuario = "1234";
    user1.Dinero = "0";
    usuario.push_back(user1);

    cout << "BIENVENIDO\n";

    cout <<"SELECCIONE SU TIPO DE USUARIO:\n";
    cout <<"\nSI YA TIENE CUENTA INGRESE '1'\n";
    cout <<"SI QUIERE CREAR UNA CUENTA NUEVA INGRESE '2'\n";
    cin >> opcUsuario;

    
    if (opcUsuario == 1)
    {
        cout <<"VERIFICACION DE LA CUENTA";
        VusualizarUser();
    }
    else if (opcUsuario == 2)
    {
        cout <<"REGISTRO DE USUARIO NUEVO";
        CreacionCuenta();
        Menu();
    }
    

    return 0;
}
