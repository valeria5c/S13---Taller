#include <stdio.h>
#include "funciones.h"

/*
 Función principal del programa.
 Controla el flujo general del sistema de gestión de vehículos,
 mostrando el menú principal y llamando a las funciones según
 la opción seleccionada por el usuario.
*/
int main(int argc, char *argv[])
{
    int opc1, opc2, opc3; 
    // opc1: opción del menú principal
    // opc2: controla si el usuario desea volver al menú
    // opc3: controla si se desea registrar otro vehículo

    do
    {
        // Se muestra el menú principal y se obtiene la opción elegida
        opc1 = menu();

        // Estructura switch para ejecutar la funcionalidad seleccionada
        switch (opc1)
        {
        case 1:
            // Opción para registrar vehículos
            do
            {
                registrarVehiculo(); // Registra un nuevo vehículo
                printf("Desea registrar otro vehiculo 1.Si / 2.No: ");
                opc3 = leerIntegerRango(1, 2); // Validación de entrada
            } while (opc3 == 1);
            break;

        case 2:
            // Muestra todos los vehículos registrados
            mostrarInventario();
            break;

        case 3:
            // Busca vehículos según las preferencias del cliente
            buscarVehiculos();
            break;

        case 4:
            // Registra un cliente
            registrarCliente();
            break;
        
        case 5:
            // Muestra los clientes registrados
            mostrarClientes();
            break;

        case 6:
            // Registra una venta de un vehículo
            registrarVenta();
            break;

        case 7:
            // Muestra el historial completo de ventas realizadas
            mostrarHistorialVentas();
            break;

        case 8:
            // Finaliza la ejecución del sistema
            printf("Saliendo del sistema...\n");
            return 0;

        default:
            // Caso de seguridad
            break;
        }

        // Pregunta al usuario si desea volver al menú principal
        printf("Desea regresar al menu 1.Si/2.No: ");
        opc2 = leerIntegerRango(1, 2);

    } while (opc2 == 1); // Se repite mientras el usuario lo desee

    return 0; // Fin del programa
}
