#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Producto {
    unsigned int codigo;
    char nombre[50];
    double precio;
    int cantidad;
    struct Producto *siguiente;
};

struct Producto *lista = NULL;

void LimpiarEntrada()
{

    int caracter;
    while ((caracter = getchar()) != '\n' && caracter != EOF) {};
}

void registrarProducto()
{
    struct Producto *nuevo = malloc(sizeof(struct Producto));

    if (nuevo == NULL) {
        printf("Memoria insuficiente para crear el producto\n");
        return;
    }

    printf("Codigo del producto: ");
    if ((scanf("%u", &nuevo->codigo)) != 1 ) {
        printf("codigo invalido");
        LimpiarEntrada();
        free(nuevo);
        return;
    }
    LimpiarEntrada();

    printf("Nombre del producto: ");
    if ((scanf(" %49[^\n]", nuevo->nombre)) != 1 ) {
        printf("nombre invalido");
        LimpiarEntrada();
        free(nuevo);
        return;
    }
    LimpiarEntrada();

    printf("Precio del producto: ");
    if ((scanf("%lf", &nuevo->precio)) != 1 ) {
        printf("precio invalido");
        LimpiarEntrada();
        free(nuevo);
        return;
    }
    LimpiarEntrada();

    printf("Cantidad de producto: ");
    if ((scanf("%d", &nuevo->cantidad)) != 1 ) {
        printf("cantidad invalida");
        LimpiarEntrada();
        free(nuevo);
        return;
    }
    LimpiarEntrada();

    nuevo->siguiente = NULL;

    if (lista == NULL) {
        lista = nuevo;
    }
    else {

        struct Producto *actual = lista;

        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevo;
    }

    printf("Produto registrado con exito!\n");

}

void mostrarProducto() {

    printf("==========PRODUCTOS REGISTRADOS==========\n");
    struct Producto *actual = lista;

    if (lista == NULL) {
        printf("****No hay productos registrados****\n");
        return;
    }

    unsigned contador = 1;
    while (actual != NULL) {

        printf("\n-- Producto #%u --\n", contador);
        printf("Codigo: %u\n", actual->codigo);
        printf("Nombre: %s\n", actual->nombre);
        printf("Precio: %.2f\n", actual->precio);
        printf("Cantidad: %d\n\n", actual->cantidad);

        actual = actual->siguiente;
        contador++;
    }
}

void buscarProducto() {

    printf("==========BUSQUEDA DE PRODUCTOS==========\n\n");
    struct Producto *actual = lista;
    unsigned int codigoElegido;

    if (lista == NULL) {
        printf("****No hay productos registrados****\n");
        return;
    }

    printf("Codigo del producto a buscar: ");
    if ((scanf("%u", &codigoElegido)) != 1) {
        printf("codigo invalido");
        LimpiarEntrada();
        return;
    }

    LimpiarEntrada();

    while (actual != NULL) {
        if (actual->codigo == codigoElegido) {
            printf("Codigo: %u\n", codigoElegido);
            printf("Nombre: %s\n", actual->nombre);
            printf("Precio: %.2f\n", actual->precio);
            printf("Cantidad: %d\n\n", actual->cantidad);
            return;
        }
        actual = actual->siguiente;
    }

    printf("****Producto no encontrado****\n\n");
}

void eliminarProducto() {

    printf("========ELIMINAR PRODUCTOS=======\n\n");
    struct Producto *actual = lista;
    struct Producto *anterior = NULL;
    unsigned int codigoElegido;

    printf("Codigo del producto a eliminar: ");
    if ((scanf("%u", &codigoElegido)) != 1) {
        printf("codigo invalido");
        LimpiarEntrada();
        return;
    }
    LimpiarEntrada();

    if (lista == NULL) {
        printf("****No hay productos registrados****\n");
        return;
    }

    while (actual != NULL && actual->codigo != codigoElegido)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("**Producto no encontrado**\n");
        return;
    }

    if (anterior == NULL) {
        lista = actual->siguiente;
    }
    else {
        anterior->siguiente = actual->siguiente;
    }

    free(actual);

    printf("Producto eliminado con exito!\n\n");
}

void contarProducto() {

    unsigned int cantidadProductos = 0;
    printf("==========CONTEO DE INVENTARIO==========\n\n");
    struct Producto *actual = lista;

    if (lista == NULL) {
        printf("****No hay productos registrados****\n");
        return;
    }

    while ( actual != NULL) {
        cantidadProductos++;
        actual = actual->siguiente;
    }

    printf("--> Cantidad de productos registrados: %u\n", cantidadProductos);

}

void liberarLista(void)
{
    struct Producto *actual = lista;
    struct Producto *siguiente;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    lista = NULL;
}


int main(void) {

    int eleccion;

    do {
        printf("\n===== GESTOR DE INVENTARIO =====\n");
        printf("1. Registrar producto\n");
        printf("2. Mostrar productos\n");
        printf("3. Buscar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Contar productos\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &eleccion) != 1) {
            printf("Debe introducir un numero valido.\n");
            LimpiarEntrada();
            continue;
        }

        LimpiarEntrada();

        switch (eleccion) {
            case 1:
                registrarProducto();
                break;

            case 2:
                mostrarProducto();
                break;

            case 3:
                buscarProducto();
                break;

            case 4:
                eliminarProducto();
                break;
            case 5:
                contarProducto();
                break;
            case 6:
                liberarLista();
                printf("Gracias por usar nuestro programa.\n");
                break;

            default:
                printf("Opcion no valida.\n");
        }
    } while (eleccion != 6);
    return 0;
}
