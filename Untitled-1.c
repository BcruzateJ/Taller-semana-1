#include <stdio.h>
#include <string.h>

struct Producto {
    char id[100];
    char nombre[100];
    int cantidad_stock;
    float precio_normal;
    float precio_venta;
    float ganancias;
    float gastos;
};

int leerEnteroPositivo(const char *mensaje) {
    int valor;
    do {
        printf("%s", mensaje);
        if (scanf("%d", &valor) != 1) {
            printf("Entrada invalida. Debe ingresar solo numeros.\n");
            while (getchar() != '\n');
            valor = -1;
        } else if (valor < 0) {
            printf("Solo numeros de 0 para arriba.\n");
        }
    } while (valor < 0);
    return valor;
}

float leerFlotantePositivo(const char *mensaje) {
    float valor;
    do {
        printf("%s", mensaje);
        if (scanf("%f", &valor) != 1) {
            printf("Entrada invalida. Debe ingresar solo numeros.\n");
            while (getchar() != '\n');
            valor = -1;
        } else if (valor < 0) {
            printf("Solo numeros de 0 para arriba.\n");
        }
    } while (valor < 0);
    return valor;
}

struct Producto registrarProducto() {
    struct Producto p;
    printf("Ingrese ID del producto: ");
    fgets(p.id, sizeof(p.id), stdin);
    if (p.id[strlen(p.id) - 1] == '\n') {
        p.id[strlen(p.id) - 1] = '\0';
    }

    printf("Ingrese nombre del producto: ");
    fgets(p.nombre, sizeof(p.nombre), stdin);
    if (p.nombre[strlen(p.nombre) - 1] == '\n') {
        p.nombre[strlen(p.nombre) - 1] = '\0';
    }

    p.cantidad_stock = leerEnteroPositivo("Ingrese cantidad en stock: ");
    p.precio_normal = leerFlotantePositivo("Ingrese precio normal (para reabastecer): ");
    p.precio_venta = leerFlotantePositivo("Ingrese precio de venta: ");

    p.ganancias = 0;
    p.gastos = 0;
    return p;
}

struct Producto venderProducto(struct Producto p, int *contador_ventas) {
    int cantidad;
    cantidad = leerEnteroPositivo("Ingrese cantidad a vender: ");
    
    if (cantidad > p.cantidad_stock) {
        printf("No hay suficiente stock para la venta.\n");
    } else {
        p.cantidad_stock -= cantidad;
        if (*contador_ventas == 3) {
            p.ganancias += cantidad * p.precio_venta * 0.7;
            printf("Venta realizada con descuento del 30%%.\n");
            *contador_ventas = 0;
        } else {
            p.ganancias += cantidad * p.precio_venta;
        }
        (*contador_ventas)++;
        printf("Venta realizada con exito.\n");
    }
    return p;
}

struct Producto reabastecerProducto(struct Producto p) {
    int cantidad;
    cantidad = leerEnteroPositivo("Ingrese cantidad a agregar al stock: ");
    
    float costo = cantidad * p.precio_normal;
    p.gastos += costo;

    p.cantidad_stock += cantidad;
    printf("Stock actualizado correctamente.\n");
    return p;
}

int main() {
    struct Producto producto;
    float capital_inicial;
    int opcion;
    int contador_ventas = 1;

    printf("Ingrese el capital inicial con el que inicia su tienda: ");
    scanf("%f", &capital_inicial);
    getchar();

    producto = registrarProducto();
    
    do {
        printf("\n=== Menu ===\n");
        printf("1. Vender producto\n");
        printf("2. Reabastecer producto\n");
        printf("3. Mostrar ganancias netas\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        
        if (scanf("%d", &opcion) != 1) {
            printf("Opción invalida. Intente de nuevo.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (opcion) {
            case 1:
                producto = venderProducto(producto, &contador_ventas);
                break;
            case 2:
                producto = reabastecerProducto(producto);
                break;
            case 3:
                printf("\n=== Informacion del Producto ===\n");
                printf("ID: %s\n", producto.id);
                printf("Nombre: %s\n", producto.nombre);
                printf("Cantidad en stock: %d\n", producto.cantidad_stock);
                printf("Precio normal (para reabastecer): %.2f\n", producto.precio_normal);
                printf("Precio de venta: %.2f\n", producto.precio_venta);
                printf("Ganancias obtenidas: %.2f\n", producto.ganancias);
                printf("Gastos totales: %.2f\n", producto.gastos);
                printf("Ganancia neta: %.2f\n", producto.ganancias - producto.gastos);
                
                float capital_total = capital_inicial + producto.ganancias - producto.gastos;
                printf("Dinero total (Capital Inicial + Ganancias - Gastos): %.2f\n", capital_total);
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 4);

    return 0;
}