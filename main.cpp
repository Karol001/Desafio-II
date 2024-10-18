#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Transaccion {
private:
    string fecha;  // Formato: YYYY-MM-DD
    string hora;   // Formato: HH:MM:SS
    float cantidad;
    string categoriaCombustible;
    string metodoPago;
    string documentoCliente;
    float monto;

public:
    Transaccion(float cantidad, string categoriaCombustible, string metodoPago, string documentoCliente, float monto) {
        this->cantidad = cantidad;
        this->categoriaCombustible = categoriaCombustible;
        this->metodoPago = metodoPago;
        this->documentoCliente = documentoCliente;
        this->monto = monto;

        // Obtener la fecha y hora actual
        time_t t = time(0); // Obtener el tiempo actual
        struct tm* now = localtime(&t);

        // Formatear la fecha como YYYY-MM-DD
        fecha = to_string(now->tm_year + 1900) + "-" +
                to_string(now->tm_mon + 1) + "-" +
                to_string(now->tm_mday);

        // Formatear la hora como HH:MM:SS
        hora = to_string(now->tm_hour) + ":" +
               to_string(now->tm_min) + ":" +
               to_string(now->tm_sec);
    }

    // Métodos getter para los atributos
    string getFecha() const { return fecha; }
    string getHora() const { return hora; }
    float getCantidad() const { return cantidad; }
    string getCategoriaCombustible() const { return categoriaCombustible; }
    string getMetodoPago() const { return metodoPago; }
    string getDocumentoCliente() const { return documentoCliente; }
    float getMonto() const { return monto; }
};

class Surtidor {
private:
    string codigo;
    string modelo;
    bool activo;
    Transaccion** transacciones; // Puntero a un arreglo dinámico de transacciones
    int numTransacciones; // Contador de transacciones

public:
    Surtidor(string codigo, string modelo) {
        this->codigo = codigo;
        this->modelo = modelo;
        this->activo = true;
        this->transacciones = nullptr; // Inicialmente sin transacciones
        this->numTransacciones = 0;
    }

    ~Surtidor() {
        // Liberar memoria asignada a las transacciones
        for (int i = 0; i < numTransacciones; ++i) {
            delete transacciones[i];
        }
        delete[] transacciones;
    }

    void registrarVenta(float cantidad, string categoriaCombustible, string metodoPago, string documentoCliente, float monto) {
        Transaccion* nuevaTransaccion = new Transaccion(cantidad, categoriaCombustible, metodoPago, documentoCliente, monto);

        // Redimensionar el arreglo de transacciones para agregar la nueva
        Transaccion** nuevoArreglo = new Transaccion*[numTransacciones + 1];
        for (int i = 0; i < numTransacciones; ++i) {
            nuevoArreglo[i] = transacciones[i];
        }
        nuevoArreglo[numTransacciones] = nuevaTransaccion;
        delete[] transacciones;
        transacciones = nuevoArreglo;
        ++numTransacciones;
    }

    bool estaActivo() const { return activo; }
    void activar() { activo = true; }
    void desactivar() { activo = false; }

    string getCodigo() const { return codigo; }
    int getNumTransacciones() const { return numTransacciones; }
    float calcularVentasPorCategoria(string categoria) const {
        float total = 0.0;
        for (int i = 0; i < numTransacciones; ++i) {
            if (transacciones[i]->getCategoriaCombustible() == categoria) {
                total += transacciones[i]->getMonto();
            }
        }
        return total;
    }
};

class EstacionDeServicio {
private:
    string nombre;
    string codigo;
    string gerente;
    string region;
    float* capacidadTanque; // Puntero a un arreglo dinámico de capacidades
    int numCategorias; // Cantidad de categorías
    Surtidor** surtidores; // Puntero a un arreglo dinámico de surtidores
    int numSurtidores; // Contador de surtidores

public:
    EstacionDeServicio(string nombre, string codigo, string gerente, string region, int numCategorias) {
        this->nombre = nombre;
        this->codigo = codigo;
        this->gerente = gerente;
        this->region = region;
        this->numCategorias = numCategorias;
        this->capacidadTanque = new float[numCategorias]; // Asignar espacio para capacidades
        this->surtidores = nullptr; // Inicialmente sin surtidores
        this->numSurtidores = 0;
    }

    ~EstacionDeServicio() {
        delete[] capacidadTanque;
        for (int i = 0; i < numSurtidores; ++i) {
            delete surtidores[i];
        }
        delete[] surtidores;
    }

    void agregarSurtidor(Surtidor* nuevoSurtidor) {
        Surtidor** nuevoArreglo = new Surtidor*[numSurtidores + 1];
        for (int i = 0; i < numSurtidores; ++i) {
            nuevoArreglo[i] = surtidores[i];
        }
        nuevoArreglo[numSurtidores] = nuevoSurtidor;
        delete[] surtidores;
        surtidores = nuevoArreglo;
        ++numSurtidores;
    }

    bool eliminarSurtidor() {
        if (numSurtidores == 0) {
            return false; // No hay surtidores para eliminar
        }
        // Desactivar el último surtidor como ejemplo, puedes modificar esto
        delete surtidores[numSurtidores - 1];
        numSurtidores--;
        return true;
    }

    int getNumSurtidores() const { return numSurtidores; }
    string getCodigo() const { return codigo; }

    float calcularVentasPorCategoria(string categoria) const {
        float total = 0.0;
        for (int i = 0; i < numSurtidores; ++i) {
            total += surtidores[i]->calcularVentasPorCategoria(categoria);
        }
        return total;
    }
};

class RedNacional {
private:
    EstacionDeServicio** estaciones; // Puntero a un arreglo dinámico de estaciones de servicio
    int numEstaciones; // Contador de estaciones
    float* preciosPorRegion; // Puntero a un arreglo dinámico para precios por región
    int numRegiones; // Cantidad de regiones

public:
    RedNacional(int numRegiones) {
        this->numEstaciones = 0;
        this->estaciones = nullptr; // Inicialmente sin estaciones
        this->numRegiones = numRegiones;
        this->preciosPorRegion = new float[numRegiones]; // Asignar espacio para precios
    }

    ~RedNacional() {
        delete[] preciosPorRegion;
        for (int i = 0; i < numEstaciones; ++i) {
            delete estaciones[i];
        }
        delete[] estaciones;
    }

    void agregarEstacion(EstacionDeServicio* nuevaEstacion) {
        EstacionDeServicio** nuevoArreglo = new EstacionDeServicio*[numEstaciones + 1];
        for (int i = 0; i < numEstaciones; ++i) {
            nuevoArreglo[i] = estaciones[i];
        }
        nuevoArreglo[numEstaciones] = nuevaEstacion;
        delete[] estaciones;
        estaciones = nuevoArreglo;
        ++numEstaciones;
    }

    bool eliminarEstacion(string codigo) {
        for (int i = 0; i < numEstaciones; ++i) {
            if (estaciones[i]->getCodigo() == codigo && estaciones[i]->getNumSurtidores() == 0) {
                delete estaciones[i];
                for (int j = i; j < numEstaciones - 1; ++j) {
                    estaciones[j] = estaciones[j + 1];
                }
                numEstaciones--;
                return true; // Estación eliminada
            }
        }
        return false; // No se pudo eliminar la estación
    }

    void mostrarVentasPorCategoria(string categoria) {
        for (int i = 0; i < numEstaciones; ++i) {
            float total = estaciones[i]->calcularVentasPorCategoria(categoria);
            cout << "Estacion: " << estaciones[i]->getCodigo() << " - Ventas en " << categoria << ": " << total << endl;
        }
    }

    void fijarPrecios(float* precios) {
        for (int i = 0; i < numRegiones; ++i) {
            preciosPorRegion[i] = precios[i];
        }
    }

    int getNumEstaciones() const { return numEstaciones; }
};

void menu(RedNacional& red) {
    int opcion;
    do {
        cout << "Menu de Gestion de la Red de Estaciones de Servicio:\n";
        cout << "1. Agregar estacion de servicio\n";
        cout << "2. Eliminar estacion de servicio\n";
        cout << "3. Calcular ventas por categoria de combustible\n";
        cout << "4. Fijar precios del combustible para toda la red\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string nombre, codigo, gerente, region;
            int numCategorias;
            cout << "Ingrese nombre: ";
            cin >> nombre;
            cout << "Ingrese codigo: ";
            cin >> codigo;
            cout << "Ingrese gerente: ";
            cin >> gerente;
            cout << "Ingrese region: ";
            cin >> region;
            cout << "Ingrese numero de categorias: ";
            cin >> numCategorias;

            EstacionDeServicio* nuevaEstacion = new EstacionDeServicio(nombre, codigo, gerente, region, numCategorias);
            red.agregarEstacion(nuevaEstacion);
            cout << "Estacion de servicio agregada con exito.\n";
            break;
        }
        case 2: {
            string codigo;
            cout << "Ingrese codigo de la estacion a eliminar: ";
            cin >> codigo;
            if (red.eliminarEstacion(codigo)) {
                cout << "Estacion eliminada con exito.\n";
            } else {
                cout << "No se pudo eliminar la estacion (puede tener surtidores activos).\n";
            }
            break;
        }
        case 3: {
            string categoria;
            cout << "Ingrese categoria de combustible: ";
            cin >> categoria;
            red.mostrarVentasPorCategoria(categoria);
            break;
        }
        case 4: {
            float* precios = new float[red.getNumEstaciones()]; // Ejemplo simple, deberías ajustar según regiones
            cout << "Ingrese precios por region:\n";
            for (int i = 0; i < red.getNumEstaciones(); ++i) {
                cout << "Precio para la region " << i + 1 << ": ";
                cin >> precios[i];
            }
            red.fijarPrecios(precios);
            delete[] precios;
            cout << "Precios fijados con exito.\n";
            break;
        }
        case 0:
            cout << "Saliendo del menu.\n";
            break;
        default:
            cout << "Opción no valida, intente de nuevo.\n";
        }
    } while (opcion != 0);
}

int main() {
    RedNacional red(3); // Inicializamos con 3 regiones
    menu(red);
    return 0;
}
