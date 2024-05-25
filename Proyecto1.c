#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTOS 100
#define MAX_NOMBRE 25
#define MAX_MOVIMIENTOS 100

typedef struct {
	char nombre[MAX_NOMBRE];
	int cantidad;
} Producto;

typedef struct {
	char descripcion[100];
} Movimiento;

Producto inventario[MAX_PRODUCTOS];
Movimiento movimientos[MAX_MOVIMIENTOS];
int num_productos = 0;
int num_movimientos = 0;

void registrarMovimiento(const char *descripcion) {
	if (num_movimientos < MAX_MOVIMIENTOS) {
		strncpy(movimientos[num_movimientos].descripcion, descripcion, 100);
		num_movimientos++;
	}
}

void verificarUsuario() {
	char nombre[25];
	char password[25];
	printf("\nIngrese su usuario: ");
	scanf("%s", nombre);
	printf("Ingrese su password: ");
	scanf("%s", password);
	
	if (strcmp(nombre, "Sergioj") == 0 && strcmp(password, "Sergio1") == 0) {
		printf("\nBienvenido al menú principal\n");
	} else {
		printf("\nTu usuario y/o password son incorrectos...\n");
		exit(0); // Salir del programa si la autenticación falla
	}
}

void agregarproductos() {
	if (num_productos >= MAX_PRODUCTOS) {
		printf("El inventario está lleno. No se pueden agregar más productos.\n");
		return;
	}
	
	char nombre[MAX_NOMBRE];
	int cantidad;
	
	printf("\nIngrese el nombre del producto que desea agregar: ");
	scanf("%s", nombre);
	printf("Ingrese la cantidad: ");
	scanf("%d", &cantidad);
	
	// Verificar si el producto ya existe
	for (int i = 0; i < num_productos; i++) {
		if (strcmp(inventario[i].nombre, nombre) == 0) {
			inventario[i].cantidad += cantidad;
			printf("Producto actualizado. Nueva cantidad: %d\n", inventario[i].cantidad);
			char movimiento[150];
			snprintf(movimiento, sizeof(movimiento), "Actualizado producto: %s, Nueva cantidad: %d", nombre, inventario[i].cantidad);
			registrarMovimiento(movimiento);
			return;
		}
	}
	
	// Si el producto no existe, agregarlo al inventario
	strcpy(inventario[num_productos].nombre, nombre);
	inventario[num_productos].cantidad = cantidad;
	num_productos++;
	printf("Producto agregado con éxito.\n");
	
	char movimiento[150];
	snprintf(movimiento, sizeof(movimiento), "Agregado producto: %s, Cantidad: %d", nombre, cantidad);
	registrarMovimiento(movimiento);
}

void editarproductos() {
	char nombre[MAX_NOMBRE];
	int cantidad;
	
	printf("\nIngrese el nombre del producto que desea editar: ");
	scanf("%s", nombre);
	
	for (int i = 0; i < num_productos; i++) {
		if (strcmp(inventario[i].nombre, nombre) == 0) {
			printf("Ingrese la nueva cantidad: ");
			scanf("%d", &cantidad);
			inventario[i].cantidad = cantidad;
			printf("Producto editado con éxito.\n");
			
			char movimiento[150];
			snprintf(movimiento, sizeof(movimiento), "Editado producto: %s, Nueva cantidad: %d", nombre, cantidad);
			registrarMovimiento(movimiento);
			return;
		}
	}
	
	printf("Producto no encontrado.\n");
}

void eliminarproductos() {
	char nombre[MAX_NOMBRE];
	
	printf("\nIngrese el nombre del producto que desea eliminar: ");
	scanf("%s", nombre);
	
	for (int i = 0; i < num_productos; i++) {
		if (strcmp(inventario[i].nombre, nombre) == 0) {
			for (int j = i; j < num_productos - 1; j++) {
				inventario[j] = inventario[j + 1];
			}
			num_productos--;
			printf("Producto eliminado con éxito.\n");
			
			char movimiento[150];
			snprintf(movimiento, sizeof(movimiento), "Eliminado producto: %s", nombre);
			registrarMovimiento(movimiento);
			return;
		}
	}
	
	printf("Producto no encontrado.\n");
}

void mostrarInventario() {
	if (num_productos == 0) {
		printf("El inventario está vacío.\n");
		return;
	}
	
	printf("\nInventario:\n");
	for (int i = 0; i < num_productos; i++) {
		printf("Producto: %s, Cantidad: %d\n", inventario[i].nombre, inventario[i].cantidad);
	}
}

void mostrarMovimientos() {
	if (num_movimientos == 0) {
		printf("No se realizaron movimientos.\n");
		return;
	}
	
	printf("\nMovimientos realizados:\n");
	for (int i = 0; i < num_movimientos; i++) {
		printf("%s\n", movimientos[i].descripcion);
	}
}

int main(int argc, char *argv[]) {
	int opcion;
	
	printf("\n-----Farmacia San Pablo-----\n");
	printf("\nPara poder ingresar al sistema ingrese su usuario y su password");
	
	verificarUsuario();
	
	do {
		printf("\n----------------------------------------------\n");
		printf("\n¿Qué acción desea hacer?\n");
		printf("1.- Agregar productos.\n");
		printf("2.- Editar productos.\n");
		printf("3.- Eliminar productos.\n");
		printf("4.- Mostrar inventario.\n");
		printf("5.- Salir.\n");
		printf("Ingrese una opción: ");
		scanf("%d", &opcion);
		
		switch (opcion) {
		case 1:
			agregarproductos();
			break;
		case 2:
			editarproductos();
			break;
		case 3:
			eliminarproductos();
			break;
		case 4:
			mostrarInventario();
			break;
		case 5:
			printf("Saliendo del programa...\n");
			mostrarMovimientos();
			break;
		default:
			printf("Opción inválida.\n");
		}
	} while (opcion != 5);
	
	return 0;
}

/*holamundo*/
