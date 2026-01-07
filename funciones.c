#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

/*
 Muestra el menú principal del sistema y retorna
 la opción seleccionada por el usuario.
*/
int menu()
{
    int opc;
    printf("===================================================\n");
    printf("  SISTEMA DE GESTION \"RUEDAS DE ORO\"\n");
    printf("===================================================\n");
    printf("1.Registrar Vehiculo\n");
    printf("2.Mostrar Inventario de Vehiculos\n");
    printf("3.Buscar Vehiculos segun preferencias del cliente\n");
    printf("4.Registrar Cliente\n");
    printf("5.Mostrar Clientes\n");
    printf("6.Registrar Venta\n");
    printf("7.Mostrar Historial de Ventas\n");
    printf("8.Salir\n");
    printf("===================================================\n");
    printf("Seleccione una opcion: \n");

    // Se valida que la opción esté dentro del rango permitido
    opc = leerIntegerRango(1, 8);
    return opc;
}

/*
 Lee una cadena de caracteres desde teclado,
 eliminando el salto de línea final.
*/
void leerCadena(char *cadena, int n)
{
    fflush(stdin); // Limpia el buffer de entrada
    fgets(cadena, n, stdin);
    int len = strlen(cadena) - 1;
    cadena[len] = '\0'; // Elimina el salto de línea
}

/*
 Lee un número flotante validando que esté dentro
 de un rango específico.
*/
float leerFlotanteRango(float inicio, float fin)
{
    float num;
    int val;
    do
    {
        val = scanf("%f", &num);
        if (val != 1 || num < inicio || num > fin)
        {
            printf("El dato ingresado es invalido\n");
            printf("Ingrese un numero entre %.2f y %.2f: ", inicio, fin);
            while (getchar() != '\n')
                ; // Limpia el buffer
        }
    } while (val != 1 || num < inicio || num > fin);
    return num;
}

/*
 Lee un número entero validando que esté dentro
 de un rango específico.
*/
int leerIntegerRango(int inicio, int fin)
{
    int num;
    int val;
    do
    {
        val = scanf("%d", &num);
        if (val != 1 || num < inicio || num > fin)
        {
            printf("El dato ingresado es invalido\n");
            printf("Ingrese un numero entre %d y %d: ", inicio, fin);
            while (getchar() != '\n')
                ; // Limpia el buffer
        }
    } while (val != 1 || num < inicio || num > fin);
    return num;
}

/*
 Registra un nuevo vehículo verificando que el ID sea único
 y guardándolo en el archivo de vehículos.
*/
void registrarVehiculo()
{
    Vehiculo vehiculo;
    Vehiculo vehiculos[MAX_VEHICULOS];
    int contv = leerVehiculos(vehiculos); // Carga vehículos existentes

    // Validación de ID único
    do
    {
        printf("Ingrese el ID del vehiculo: ");
        vehiculo.id = leerIntegerRango(1, MAX_VEHICULOS);

        int existe = 0;

        for (int i = 0; i < contv; i++)
        {
            if (vehiculos[i].id == vehiculo.id)
            {
                existe = 1;
                break;
            }
        }

        if (existe)
            printf("El ID ya existe. Ingrese otro.\n");
        else
            break;

    } while (1);

    // Ingreso de datos del vehículo
    printf("Ingrese la marca del vehiculo: ");
    leerCadena(vehiculo.marca, 20);

    printf("Ingrese el tipo del vehiculo: ");
    leerCadena(vehiculo.tipo, 20);

    printf("Ingrese el anio del vehiculo: ");
    vehiculo.anio = leerIntegerRango(1900, 2024);

    printf("Ingrese el precio del vehiculo: ");
    vehiculo.precio = leerFlotanteRango(0, 1000000);

    printf("Ingrese el estado del vehiculo (1-nuevo, 2-usado): ");
    vehiculo.estado = leerIntegerRango(1, 2);

    vehiculo.disponible = 1; // Por defecto el vehículo está disponible

    guardarVehiculo(&vehiculo); // Guarda el vehículo en archivo
}

/*
 Guarda un vehículo en el archivo binario vehiculos.dat
*/
void guardarVehiculo(Vehiculo *vehiculo)
{
    FILE *f = fopen("vehiculos.dat", "ab+");
    if (f == NULL)
    {
        printf("No se pudo abrir el archivo de vehiculos.\n");
        return;
    }
    fwrite(vehiculo, sizeof(Vehiculo), 1, f);
    fclose(f);
}

/*
 Lee todos los vehículos almacenados en el archivo
 y los carga en un arreglo.
*/
int leerVehiculos(Vehiculo *vehiculos)
{
    FILE *f = fopen("vehiculos.dat", "rb+");
    if (f == NULL)
    {
        printf("No se pudo abrir el archivo de vehiculos.\n");
        return 0;
    }
    int count = fread(vehiculos, sizeof(Vehiculo), MAX_VEHICULOS, f);
    fclose(f);
    return count;
}

/*
 Muestra el inventario completo de vehículos registrados.
*/
void mostrarInventario()
{
    Vehiculo vehiculos[MAX_VEHICULOS];
    int cont = leerVehiculos(vehiculos);

    printf("\n========= INVENTARIO DE VEHICULOS =========\n");
    printf("\n%-5s %-15s %-12s %-6s %-10s %-10s %-12s\n",
           "ID", "Marca", "Tipo", "Anio", "Precio", "Estado", "Disponible");

    for (int i = 0; i < cont; i++)
    {
        printf("\n%-5d %-15s %-12s %-6d %-10.2f %-10s %-12s\n",
               vehiculos[i].id,
               vehiculos[i].marca,
               vehiculos[i].tipo,
               vehiculos[i].anio,
               vehiculos[i].precio,
               vehiculos[i].estado == 1 ? "Nuevo" : "Usado",
               vehiculos[i].disponible == 1 ? "Si" : "No");
    }
}

/*
 Busca vehículos que coincidan con las preferencias
 ingresadas por el cliente.
*/
void buscarVehiculos()
{
    Preferencias preferencias;
    Vehiculo vehiculos[MAX_VEHICULOS];
    int cont = leerVehiculos(vehiculos);
    int similares = 0;

    printf("Marca (0 para cualquiera): ");
    leerCadena(preferencias.marcapreferida, 20);

    printf("Tipo (0 para cualquiera): ");
    leerCadena(preferencias.tipopreferido, 20);

    printf("Estado (0 cualquiera, 1 nuevo, 2 usado): ");
    preferencias.estadopreferido = leerIntegerRango(0, 2);

    printf("Presupuesto maximo (0 sin limite): ");
    preferencias.presupuestomax = leerFlotanteRango(0, 1000000);

    printf("\n========= VEHICULOS SIMILARES =========\n");
    printf("\n%-5s %-15s %-15s %-6s %-10s %-8s\n",
       "ID", "Marca", "Tipo", "Anio", "Estado", "Precio");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < cont; i++)
    {
        if (!vehiculos[i].disponible)
            continue;

        if (preferencias.estadopreferido != 0 && vehiculos[i].estado != preferencias.estadopreferido)
            continue;
        if (preferencias.presupuestomax != 0 && vehiculos[i].precio > preferencias.presupuestomax)
            continue;
        if (strcmp(preferencias.marcapreferida, "0") != 0 &&
            strcasecmp(vehiculos[i].marca, preferencias.marcapreferida) != 0)
            continue;
        if (strcmp(preferencias.tipopreferido, "0") != 0 &&
            strcasecmp(vehiculos[i].tipo, preferencias.tipopreferido) != 0)
            continue;

        printf("\n%-5d %-15s %-15s %-6d %-10s %-8.2f\n",
                                                        vehiculos[i].id,
                                                        vehiculos[i].marca,
                                                        vehiculos[i].tipo,
                                                        vehiculos[i].anio,
                                                        vehiculos[i].estado == 1 ? "Nuevo" : "Usado",
                                                        vehiculos[i].precio);
        similares++;
    }

    if (similares == 0)
        printf("No se encontraron vehiculos que cumplan las preferencias.\n");

    printf("Desea registrar una venta 1.Si / 2.No: ");
    if (leerIntegerRango(1, 2) == 1)
        registrarVenta();
}

/*
 Registra una venta de un vehículo.
 Verifica que el vehículo exista y esté disponible,
 guarda la venta y actualiza el estado del vehículo.
*/
void registrarVenta()
{
    Vehiculo vehiculos[MAX_VEHICULOS];
    int contv = leerVehiculos(vehiculos); // Carga los vehículos registrados
    Venta venta;
    int encontrado = -1; // Indica si el vehículo fue encontrado

    // Ingreso del nombre del vendedor
    printf("Ingrese el nombre del vendedor: ");
    leerCadena(venta.vendedor, 15);

    // Ingreso del ID del vehículo a vender
    printf("Ingrese el ID del vehiculo a vender: ");
    venta.idVehiculo = leerIntegerRango(1, MAX_VEHICULOS);

    // Búsqueda del vehículo en el inventario
    for (int i = 0; i < contv; i++)
    {
        if (vehiculos[i].id == venta.idVehiculo && vehiculos[i].disponible == 1)
        {
            encontrado = i;
            break;
        }
    }

    // Si el vehículo no existe o no está disponible
    if (encontrado == -1)
    {
        printf("Vehiculo no encontrado o no disponible para la venta.\n");
        return;
    }

    // Ingreso de datos del cliente que realiza la compra
    seleccionarCliente(venta.ciCliente);

    // Asignación de datos de la venta
    venta.precioVenta = vehiculos[encontrado].precio;

    printf("Fecha (dd/mm/aaaa): ");
    leerCadena(venta.fecha, 15);

    // Guarda la venta en el archivo de ventas
    guardarVenta(&venta);

    // Marca el vehículo como no disponible (vendido)
    vehiculos[encontrado].disponible = 0;

    // Actualiza el archivo de vehículos
    actualizarVehiculo(vehiculos, contv);

    printf("Venta registrada correctamente.\n");
}

/*
 Guarda una venta en el archivo binario ventas.dat
*/
void guardarVenta(Venta *venta)
{
    FILE *f = fopen("ventas.dat", "ab+");

    if (f == NULL)
    {
        printf("No se pudo abrir el archivo de ventas.\n");
        return;
    }

    fwrite(venta, sizeof(Venta), 1, f);
    fclose(f);
}

/*
 Actualiza el archivo de vehículos sobrescribiendo
 toda la información con los datos actuales.
*/
void actualizarVehiculo(Vehiculo *vehiculos, int cont)
{
    FILE *f = fopen("vehiculos.dat", "wb");
    fwrite(vehiculos, sizeof(Vehiculo), cont, f);
    fclose(f);
}

/*
 Muestra el historial completo de ventas registradas
 en el sistema.
*/
void mostrarHistorialVentas()
{
    FILE *f = fopen("ventas.dat", "rb");
    Venta venta;

    // Verifica si el archivo existe
    if (f == NULL)
    {
        printf("No hay ventas registradas.\n");
        return;
    }

    printf("\n========= HISTORIAL DE VENTAS =========\n");
    printf("\n%-10s %-12s %-12s %-15s %-12s\n",
           "Vendedor", "ID Vehiculo", "Cliente", "Precio Venta", "Fecha");
    printf("-----------------------------------------------------------------------\n");

    // Lectura secuencial de todas las ventas
    while (fread(&venta, sizeof(Venta), 1, f))
    {
        printf("\n%-10s %-12d %-12s %-15.2f %-12s\n",
               venta.vendedor,
               venta.idVehiculo,
               venta.ciCliente,
               venta.precioVenta,
               venta.fecha);
    }

    printf("-----------------------------------------------------------------------\n");
    fclose(f);
}

void registrarCliente()
{
    Cliente cliente;
    Cliente clientes[MAX_CLIENTES];

    printf("Cedula de Identidad: ");
    leerCadena(cliente.ci, 12);

    printf("Nombre del cliente: ");
    leerCadena(cliente.nombre, 20);

    printf("Edad: ");
    cliente.edad = leerIntegerRango(18, 100);

    printf("Telefono: ");
    leerCadena(cliente.telefono, 15);

    printf("Email: ");
    leerCadena(cliente.email, 20);

    guardarCliente(&cliente);
    printf("Cliente registrado con ID %s\n", cliente.ci);
}

void guardarCliente(Cliente *cliente)
{
    FILE *f = fopen("clientes.dat", "ab+");
    fwrite(cliente, sizeof(Cliente), 1, f);
    fclose(f);
}

int leerClientes(Cliente *clientes)
{
    FILE *f = fopen("clientes.dat", "rb+");
    // Verifica si el archivo existe
    if (f == NULL)
    {
        printf("No se pudo abrir el archivo de clientes.\n");
        return 0;
    }
    int contc = fread(clientes, sizeof(Cliente), MAX_CLIENTES, f);
    fclose(f);
    return contc;
}

void seleccionarCliente(char *ci)
{
    Cliente clientes[MAX_CLIENTES];
    int count = leerClientes(clientes);
    int existe = 0;

    if (count == 0)
    {
        printf("No hay clientes registrados.\n");
        printf("Debe registrar un cliente primero.\n");
        registrarCliente();
        leerClientes(clientes);
        count = leerClientes(clientes);
    }

    do
    {
        existe = 0;

        printf("Ingrese CI del cliente: ");
        leerCadena(ci, 12);

        for (int i = 0; i < count; i++)
        {
            if (strcmp(clientes[i].ci, ci) == 0)
            {
                existe = 1;
                break;
            }
        }

        if (!existe)
        {
            int opc;
            printf("\nCliente no encontrado.\n");
            printf("1. Ingresar otra CI\n");
            printf("2. Registrar nuevo cliente\n");
            printf("Seleccione una opcion: ");
            opc = leerIntegerRango(1, 2);

            if (opc == 2)
            {
                registrarCliente();
                count = leerClientes(clientes); // recargar lista
            }
        }

    } while (!existe);
}

/*
 Muestra el registro completo de clientes.
*/
void mostrarClientes()
{
    Cliente clientes[MAX_CLIENTES];
    int cont = leerClientes(clientes);

    printf("\n========= CLIENTES REGISTRADOS =========\n");
    printf("\n%-12s %-10s %-5s %-12s %-12s\n",
           "CI", "Nombre", "Edad", "Telefono", "Email");
    printf("-----------------------------------------------------------------------\n");

    for (int i = 0; i < cont; i++)
    {
        printf("\n%-12s %-10s %-5d %-12s %-12s\n",
                                                clientes[i].ci,
                                                clientes[i].nombre,
                                                clientes[i].edad,
                                                clientes[i].telefono,
                                                clientes[i].email);
    }
    printf("-----------------------------------------------------------------------\n");
}
