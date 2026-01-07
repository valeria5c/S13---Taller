#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_VEHICULOS 100 // Número máximo de vehículos permitidos
#define MAX_CLIENTES 100 // Número máximo de clientes permitidos

/*
 Estructura que representa un vehículo
*/
typedef struct{
    int id;
    char marca[20];
    char tipo[20];
    int anio;
    float precio;
    int estado;      // 1-nuevo 2-usado
    int disponible;  // 1-disponible 0-vendido
}Vehiculo;

/*
 Estructura que representa un cliente
*/
typedef struct{
    char ci[12];
    char nombre[20];
    int edad;
    char telefono[15];
    char email[20];
}Cliente;

/*
 Estructura que representa una venta
*/
typedef struct{
    char vendedor[10];
    int idVehiculo;
    char ciCliente[12]; // CI del cliente que realiza la compra
    float precioVenta;
    char fecha[15];
}Venta;

typedef struct{
    char marcapreferida[20];
    char tipopreferido[20];
    int estadopreferido; // 0 = cualquiera, 1 = nuevo, 2 = usado
    float presupuestomax; // 0 = sin límite
}Preferencias;

/* Prototipos de funciones */
int menu();
void leerCadena(char *cadena, int n);
float leerFlotanteRango(float inicio, float fin);
int leerIntegerRango(int inicio, int fin);
void registrarVehiculo();
void guardarVehiculo(Vehiculo *vehiculo);
int leerVehiculos(Vehiculo *vehiculos);
void mostrarInventario();
void buscarVehiculos();
void registrarVenta();
void guardarVenta(Venta *venta);
void actualizarVehiculo(Vehiculo *vehiculos, int cont);
void mostrarHistorialVentas();
void registrarCliente();
void guardarCliente(Cliente *c);
int leerClientes(Cliente *clientes);
void seleccionarCliente(char *ci);
void mostrarClientes();

#endif
