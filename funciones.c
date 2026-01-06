#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

/*
 Muestra el menú principal del sistema y retorna
 la opción seleccionada por el usuario.
*/
int menu(){
    int opc;
    printf("===================================================\n");
    printf("  SISTEMA DE GESTION \"RUEDAS DE ORO\"\n");
    printf("===================================================\n");
    printf("1.Registrar Vehiculo\n");
    printf("2.Mostrar Inventario de Vehiculos\n");
    printf("3.Buscar Vehiculos segun preferencias del cliente\n");
    printf("4.Registrar Venta\n");
    printf("5.Mostrar Historial de Ventas\n");
    printf("6.Salir\n");
    printf("===================================================\n");
    printf("Seleccione una opcion: \n");

    // Se valida que la opción esté dentro del rango permitido
    opc = leerIntegerRango(1,6);
    return opc;
}

/*
 Lee una cadena de caracteres desde teclado,
 eliminando el salto de línea final.
*/
void leerCadena(char *cadena, int n){
    fflush(stdin); // Limpia el buffer de entrada
    fgets(cadena,n,stdin);
    int len = strlen(cadena) - 1;
    cadena[len]='\0'; // Elimina el salto de línea
}

/*
 Lee un número flotante validando que esté dentro
 de un rango específico.
*/
float leerFlotanteRango(float inicio, float fin){
    float num;
    int val;
    do{
        val = scanf("%f",&num);
        if (val != 1 || num<inicio || num>fin)
        {
            printf("El dato ingresado es invalido\n");
            printf("Ingrese un numero entre %.2f y %.2f: ", inicio, fin);
            while (getchar() != '\n'); // Limpia el buffer
        }
    }while(val != 1 || num<inicio || num>fin);
    return num;
}

/*
 Lee un número entero validando que esté dentro
 de un rango específico.
*/
int leerIntegerRango(int inicio, int fin){
    int num;
    int val;
    do{
        val = scanf("%d",&num);
        if (val != 1 || num<inicio || num>fin)
        {
            printf("El dato ingresado es invalido\n");
            printf("Ingrese un numero entre %d y %d: ", inicio, fin);
            while (getchar() != '\n'); // Limpia el buffer
        }
    }while(val != 1 || num<inicio || num>fin);
    return num;
}

/*
 Registra un nuevo vehículo verificando que el ID sea único
 y guardándolo en el archivo de vehículos.
*/
void registrarVehiculo(){
    Vehiculo vehiculo;
    Vehiculo vehiculos[MAX_VEHICULOS];
    int contv = leerVehiculos(vehiculos); // Carga vehículos existentes

    // Validación de ID único
    do
    {
        printf("Ingrese el ID del vehiculo (1-100): ");
        vehiculo.id = leerIntegerRango(1,MAX_VEHICULOS);

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
    leerCadena(vehiculo.marca,20);

    printf("Ingrese el tipo del vehiculo: ");
    leerCadena(vehiculo.tipo,20);

    printf("Ingrese el anio del vehiculo: ");
    vehiculo.anio = leerIntegerRango(1900,2024);

    printf("Ingrese el precio del vehiculo: ");
    vehiculo.precio = leerFlotanteRango(0,1000000);

    printf("Ingrese el estado del vehiculo (1-nuevo, 2-usado): ");
    vehiculo.estado = leerIntegerRango(1,2);

    vehiculo.disponible = 1; // Por defecto el vehículo está disponible

    guardarVehiculo(&vehiculo); // Guarda el vehículo en archivo
}

/*
 Guarda un vehículo en el archivo binario vehiculos.dat
*/
void guardarVehiculo(Vehiculo *vehiculo){
    FILE *f = fopen("vehiculos.dat","ab+");
    if (f==NULL)
    {
        printf("No se pudo abrir el archivo de vehiculos.\n");
        return;
    }
    fwrite(vehiculo,sizeof(Vehiculo),1,f);
    fclose(f);
}

/*
 Lee todos los vehículos almacenados en el archivo
 y los carga en un arreglo.
*/
int leerVehiculos(Vehiculo *vehiculos){
    FILE *f = fopen("vehiculos.dat","rb+");
    if (f==NULL)
    {
        printf("No se pudo abrir el archivo de vehiculos.\n");
        return 0;
    }
    int count = fread(vehiculos,sizeof(Vehiculo),MAX_VEHICULOS,f);
    fclose(f);
    return count;
}

/*
 Muestra el inventario completo de vehículos registrados.
*/
void mostrarInventario(){
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
void buscarVehiculos(){
    Cliente cliente;
    Vehiculo vehiculos[MAX_VEHICULOS];
    int contv = leerVehiculos(vehiculos);
    int similares = 0;

    // Ingreso de datos del cliente
    printf("\nIngrese el nombre del cliente: ");
    leerCadena(cliente.nombre,30);

    printf("Ingrese la edad del cliente: ");
    cliente.edad = leerIntegerRango(18,100);

    printf("Ingrese la marca preferida: ");
    leerCadena(cliente.marcapreferida,20);

    printf("Ingrese el tipo de vehiculo preferido: ");
    leerCadena(cliente.tipopreferido,20);

    printf("Ingrese el estado preferido del vehiculo (1-nuevo, 2-usado): ");
    cliente.estadopreferido = leerIntegerRango(1,2);

    printf("Ingrese el presupuesto maximo: ");
    cliente.presupuestomax = leerFlotanteRango(0,1000000);

    // Búsqueda de vehículos compatibles
    for (int i = 0; i < contv; i++)
    {
        if (vehiculos[i].disponible == 1 &&
            vehiculos[i].estado == cliente.estadopreferido &&
            vehiculos[i].precio <= cliente.presupuestomax &&
            strcasecmp(vehiculos[i].marca,cliente.marcapreferida)==0 &&
            strcasecmp(vehiculos[i].tipo,cliente.tipopreferido)==0)
        {
            printf("%d %s %s %.2f\n",
                   vehiculos[i].id,
                   vehiculos[i].marca,
                   vehiculos[i].tipo,
                   vehiculos[i].precio);
            similares++;
        }
    }

    if (similares == 0)
        printf("No se encontraron vehiculos que cumplan las preferencias.\n");

    printf("Desea registrar una venta 1.Si / 2.No: ");
    if (leerIntegerRango(1,2) == 1)
        registrarVenta();
}


/*
 Registra una venta de un vehículo.
 Verifica que el vehículo exista y esté disponible,
 guarda la venta y actualiza el estado del vehículo.
*/
void registrarVenta(){
    Vehiculo vehiculos[MAX_VEHICULOS];
    int contv = leerVehiculos(vehiculos); // Carga los vehículos registrados
    Venta venta;
    int idVehiculoVenta;
    int encontrado = -1; // Indica si el vehículo fue encontrado

    // Ingreso del nombre del vendedor
     printf("Ingrese el nombre del vendedor: ");
     leerCadena(venta.vendedor,15);

    // Ingreso del ID del vehículo a vender
    printf("Ingrese el ID del vehiculo a vender: ");
    idVehiculoVenta = leerIntegerRango(1,MAX_VEHICULOS);
    
    // Búsqueda del vehículo en el inventario
    for (int i = 0; i < contv; i++)
    {
        if (vehiculos[i].id == idVehiculoVenta && vehiculos[i].disponible == 1)
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
    printf("Nombre del cliente: ");
    leerCadena(venta.clientes.nombre,20);

    printf("Edad del cliente: ");
    venta.clientes.edad = leerIntegerRango(18,100);

    // Asignación de datos de la venta
    venta.idVehiculo = idVehiculoVenta;
    venta.precioVenta = vehiculos[encontrado].precio;

    printf("Fecha (dd/mm/aaaa): ");
    leerCadena(venta.fecha,15);

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
void guardarVenta(Venta *venta){
    FILE *f = fopen("ventas.dat","ab+");
    
    if (f == NULL){
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
void actualizarVehiculo(Vehiculo *vehiculos, int cont){
    FILE *f = fopen("vehiculos.dat","wb");
    fwrite(vehiculos, sizeof(Vehiculo), cont, f);
    fclose(f);
}

/*
 Muestra el historial completo de ventas registradas
 en el sistema.
*/
void mostrarHistorialVentas(){
    FILE *f = fopen("ventas.dat","rb");
    Venta venta;

    // Verifica si el archivo existe
    if(f == NULL){
        printf("No hay ventas registradas.\n");
        return;
    }

    printf("\n========= HISTORIAL DE VENTAS =========\n");
    printf("\n%-10s %-12s %-20s %-5s %-15s %-12s\n",
       "Vendedor", "ID Vehiculo", "Cliente", "Edad", "Precio Venta", "Fecha");
    printf("-----------------------------------------------------------------------\n");

    // Lectura secuencial de todas las ventas
    while(fread(&venta, sizeof(Venta), 1, f)){
        printf("\n%-10s %-12d %-20s %-5d %-15.2f %-12s\n",
                                                         venta.vendedor,
                                                         venta.idVehiculo,
                                                         venta.clientes.nombre,
                                                         venta.clientes.edad,
                                                         venta.precioVenta,
                                                         venta.fecha);
    }

    printf("-----------------------------------------------------------------------\n");
    fclose(f);
}
