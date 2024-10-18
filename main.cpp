#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

class Transaccion {
private:
    char fecha[11];
    char hora[9];
    float cantidad;
    char categoriaCombustible[20];
    char metodoPago[20];
    char documentoCliente[20];
    float monto;

public:
    Transaccion(float cantidad, const char* categoriaCombustible, const char* metodoPago, const char* documentoCliente, float monto) {
        this->cantidad = cantidad;
        strcpy(this->categoriaCombustible, categoriaCombustible);
        strcpy(this->metodoPago, metodoPago);
        strcpy(this->documentoCliente, documentoCliente);
        this->monto = monto;

        time_t t = time(0);
        struct tm* now = localtime(&t);

        sprintf(fecha, "%04d-%02d-%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
        sprintf(hora, "%02d:%02d:%02d", now->tm_hour, now->tm_min, now->tm_sec);
    }

    const char* getFecha() const { return fecha; }
    const char* getHora() const { return hora; }
    float getCantidad() const { return cantidad; }
    const char* getCategoriaCombustible() const { return categoriaCombustible; }
    const char* getMetodoPago() const { return metodoPago; }
    const char* getDocumentoCliente() const { return documentoCliente; }
    float getMonto() const { return monto; }
};

class Surtidor {
private:
    char codigo[20];
    char modelo[20];
    bool activo;
    Transaccion** transacciones;
    int numTransacciones;

public:
    Surtidor(const char* codigo, const char* modelo) {
        strcpy(this->codigo, codigo);
        strcpy(this->modelo, modelo);
        this->activo = true;
        this->transacciones = nullptr;
        this->numTransacciones = 0;
    }

    ~Surtidor() {
        for (int i = 0; i < numTransacciones; ++i) {
            delete transacciones[i];
        }
        delete[] transacciones;
    }

    void registrarVenta(float cantidad, const char* categoriaCombustible, const char* metodoPago, const char* documentoCliente, float monto) {
        Transaccion* nuevaTransaccion = new Transaccion(cantidad, categoriaCombustible, metodoPago, documentoCliente, monto);

        Transaccion** nuevoArreglo = new Transaccion*[numTransacciones + 1];
        for (int i = 0; i < numTransacciones; ++i) {
            nuevoArreglo[i] = transacciones[i];
        }
        nuevoArreglo[numTransacciones] = nuevaTransaccion;
        delete[] transacciones;
        transacciones = nuevoArreglo;
        ++numTransacciones;
    }

    void mostrarTransacciones() const {
        std::cout << "\nHistorico de transacciones del surtidor " << codigo << ":\n";
        if (numTransacciones == 0) {
            std::cout << "  No hay transacciones registradas.\n";
            return;
        }
        for (int i = 0; i < numTransacciones; ++i) {
            std::cout << "Transaccion " << (i + 1) << ":\n";
            std::cout << "  Fecha: " << transacciones[i]->getFecha() << "\n";
            std::cout << "  Hora: " << transacciones[i]->getHora() << "\n";
            std::cout << "  Cantidad: " << transacciones[i]->getCantidad() << " litros\n";
            std::cout << "  Categoria: " << transacciones[i]->getCategoriaCombustible() << "\n";
            std::cout << "  Metodo de Pago: " << transacciones[i]->getMetodoPago() << "\n";
            std::cout << "  Documento Cliente: " << transacciones[i]->getDocumentoCliente() << "\n";
            std::cout << "  Monto: $" << transacciones[i]->getMonto() << "\n\n";
        }
    }

    bool estaActivo() const { return activo; }
    void activar() { activo = true; }
    void desactivar() { activo = false; }

    const char* getCodigo() const { return codigo; }
    const char* getModelo() const { return modelo; }
    int getNumTransacciones() const { return numTransacciones; }
    Transaccion* getTransaccion(int index) const { return transacciones[index]; }
};

class EstacionDeServicio {
private:
    char nombre[50];
    char codigo[20];
    char gerente[50];
    char region[50];
    float* capacidadTanque;
    int numCategorias;
    std::string categorias[3]; // Cambiado a std::string
    float precios[3];
    Surtidor** surtidores;
    int numSurtidores;

public:
    EstacionDeServicio(const char* nombre, const char* codigo, const char* gerente, const char* region, int numCategorias) {
        strcpy(this->nombre, nombre);
        strcpy(this->codigo, codigo);
        strcpy(this->gerente, gerente);
        strcpy(this->region, region);
        this->numCategorias = 3;
        this->capacidadTanque = new float[numCategorias];
        categorias[0] = "Regular";
        categorias[1] = "Premium";
        categorias[2] = "Ecoextra";
        this->surtidores = nullptr;
        this->numSurtidores = 0;

        // Inicializar precios por defecto
        precios[0] = 1.0;
        precios[1] = 1.5;
        precios[2] = 1.2;

        capacidadTanque[0] = 105;   // Regular
        capacidadTanque[1] = 165;   // Premium
        capacidadTanque[2] = 130;   // Ecoextra
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

    void eliminarSurtidor(const char* codigo) {
        for (int i = 0; i < numSurtidores; ++i) {
            if (strcmp(surtidores[i]->getCodigo(), codigo) == 0) {
                delete surtidores[i];
                for (int j = i; j < numSurtidores - 1; ++j) {
                    surtidores[j] = surtidores[j + 1];
                }
                --numSurtidores;
                cout << "Surtidor eliminado." << endl;
                return;
            }
        }
        cout << "Surtidor no encontrado." << endl;
    }

    void registrarVentaEnSurtidor(const char* codigoSurtidor, float cantidad, const char* categoriaCombustible, const char* metodoPago, const char* documentoCliente, float monto) {
        for (int i = 0; i < numSurtidores; ++i) {
            if (strcmp(surtidores[i]->getCodigo(), codigoSurtidor) == 0) {
                surtidores[i]->registrarVenta(cantidad, categoriaCombustible, metodoPago, documentoCliente, monto);
                cout << "Venta registrada en surtidor " << codigoSurtidor << "." << endl;
                return;
            }
        }
        cout << "Surtidor no encontrado." << endl;
    }

    float calcularVentasPorCategoria(const char* categoria) {
        float total = 0.0;
        for (int i = 0; i < numSurtidores; ++i) {
            Surtidor* surtidor = surtidores[i];
            for (int j = 0; j < surtidor->getNumTransacciones(); ++j) {
                Transaccion* transaccion = surtidor->getTransaccion(j);
                if (strcmp(transaccion->getCategoriaCombustible(), categoria) == 0) {
                    total += transaccion->getMonto();
                }
            }
        }
        return total;
    }

    void fijarPrecio(const char* categoria, float precio) {
        for (int i = 0; i < numCategorias; ++i) {
            if (categorias[i] == categoria) {  // Cambiado a comparación de std::string
                precios[i] = precio;
                cout << "Precio de " << categoria << " fijado a " << precio << endl;
                return;
            }
        }
        cout << "Categoria no encontrada." << endl;
    }
    void mostrarPrecios() const {
        cout << "Precios por categoria en " << nombre << ":\n";
        for (int i = 0; i < numCategorias; ++i) {
            cout << " - " << categorias[i] << ": " << precios[i] << endl;
        }
    }

    bool tieneSurtidoresActivos() const {
        for (int i = 0; i < numSurtidores; ++i) {
            if (surtidores[i]->estaActivo()) {
                return true;
            }
        }
        return false;
    }
    void consultarHistoricoDeSurtidor(const char* codigoSurtidor) const {
        for (int i = 0; i < numSurtidores; ++i) {
            if (strcmp(surtidores[i]->getCodigo(), codigoSurtidor) == 0) {
                surtidores[i]->mostrarTransacciones();
                return;
            }
        }
        std::cout << "Surtidor con codigo " << codigoSurtidor << " no encontrado.\n";
    }

    void consultarHistoricoTodosSurtidores() const {
        std::cout << "\nHistorico de transacciones de todos los surtidores en la estacion " << nombre << ":\n";
        for (int i = 0; i < numSurtidores; ++i) {
            surtidores[i]->mostrarTransacciones();
        }
    }

    void verificarFugas() {
        bool fugaDetectada = false;
        for (int i = 0; i < numCategorias; ++i) {
            float totalVendido = 0.0;
            float capacidadOriginal = capacidadTanque[i];

            for (int j = 0; j < numSurtidores; ++j) {
                Surtidor* surtidor = surtidores[j];
                for (int k = 0; k < surtidor->getNumTransacciones(); ++k) {
                    Transaccion* transaccion = surtidor->getTransaccion(k);
                    if (transaccion->getCategoriaCombustible() == categorias[i]) {
                        totalVendido += transaccion->getCantidad();
                    }
                }
            }

            float combustibleRestante = capacidadOriginal - totalVendido;

            if (combustibleRestante < 0) {
                fugaDetectada = true;
                cout << "ALERTA: Fuga detectada en la categoria " << categorias[i] << "\n";
                cout << "Total vendido: " << totalVendido << " litros\n";
                cout << "Capacidad original: " << capacidadOriginal << " litros\n";
                cout << "Diferencia: " << combustibleRestante << " litros\n\n";
            }
        }

        if (!fugaDetectada) {
            cout << "No se detectaron fugas en ninguna categoria.\n";
        }
    }

    std::string getCategoria(int index) const {
        if (index >= 0 && index < numCategorias) {
            return categorias[index];  // Devuelve std::string
        }
        return "";  // o un valor de error apropiado
    }

    // Método para obtener el precio por índice
    float getPrecio(int index) const {
        if (index >= 0 && index < numCategorias) {
            return precios[index];
        }
        return 0.0;  // o un valor de error apropiado
    }
    int getNumCategorias() const {
        return numCategorias; // Asegúrate de que numCategorias es una variable de instancia que contiene el número de categorías
    }
    const char* getNombre() const { return nombre; }
    const char* getCodigo() const { return codigo; }
    const char* getGerente() const { return gerente; }
    const char* getRegion() const { return region; }
    int getNumSurtidores() const { return numSurtidores; }
    const std::string* getCategorias() const { return categorias; }
    const float* getPrecios() const { return precios; }
    Surtidor* getSurtidor(int index) const { return surtidores[index]; }

    void mostrarSurtidores() const {
        cout << "\nSurtidores de la Estacion " << nombre << " (Codigo: " << codigo << "):\n";
        for (int i = 0; i < numSurtidores; ++i) {
            Surtidor* surtidor = surtidores[i];
            cout << "  Surtidor " << i+1 << ":\n";
            cout << "    Codigo: " << surtidor->getCodigo() << "\n";
            cout << "    Modelo: " << surtidor->getModelo() << "\n";
            cout << "    Estado: " << (surtidor->estaActivo() ? "Activo" : "Inactivo") << "\n\n";
        }
    }

};

class RedNacional {
private:
    EstacionDeServicio** estaciones;
    int numEstaciones;

public:
    RedNacional() {
        this->numEstaciones = 0;
        this->estaciones = nullptr;
    }

    ~RedNacional() {
        for (int i = 0; i < numEstaciones; ++i) {
            delete estaciones[i];
        }
        delete[] estaciones;
    }

    void agregarEstacion(EstacionDeServicio* estacion) {
        EstacionDeServicio** nuevoArreglo = new EstacionDeServicio*[numEstaciones + 1];
        for (int i = 0; i < numEstaciones; ++i) {
            nuevoArreglo[i] = estaciones[i];
        }
        nuevoArreglo[numEstaciones] = estacion;
        delete[] estaciones;
        estaciones = nuevoArreglo;
        ++numEstaciones;
    }

    void eliminarEstacion(const char* codigo) {
        for (int i = 0; i < numEstaciones; ++i) {
            if (strcmp(estaciones[i]->getCodigo(), codigo) == 0) {
                if (!estaciones[i]->tieneSurtidoresActivos()) {
                    delete estaciones[i];
                    for (int j = i; j < numEstaciones - 1; ++j) {
                        estaciones[j] = estaciones[j + 1];
                    }
                    --numEstaciones;
                    cout << "Estacion eliminada." << endl;
                } else {
                    cout << "No se puede eliminar la estacion con surtidores activos." << endl;
                }
                return;
            }
        }
        cout << "Estacion no encontrada." << endl;
    }

    void calcularVentas() {
        for (int i = 0; i < numEstaciones; ++i) {
            EstacionDeServicio* estacion = estaciones[i];
            float totalGasolina = estacion->calcularVentasPorCategoria("Regular");
            float totalPremium = estacion->calcularVentasPorCategoria("Premium");
            float totalEcoextra = estacion->calcularVentasPorCategoria("Ecoextra");
            cout << "Total Ventas Estacion: " << estacion->getCodigo() << endl;
            cout << " - Regular: " << totalGasolina << endl;
            cout << " - Premium: " << totalPremium << endl;
            cout << " - Ecoextra: " << totalEcoextra << endl;
            estacion->mostrarPrecios();
        }
    }

    int getNumEstaciones() const { return numEstaciones; }
    EstacionDeServicio* getEstacion(int index) const { return estaciones[index]; }

    void mostrarEstaciones() const {
        cout << "\nEstaciones de Servicio:\n";
        for (int i = 0; i < numEstaciones; ++i) {
            EstacionDeServicio* estacion = estaciones[i];
            cout << "Estacion: " << estacion->getNombre()
                 << " (Codigo: " << estacion->getCodigo() << ")\n";
            cout << "  Gerente: " << estacion->getGerente() << "\n";
            cout << "  Region: " << estacion->getRegion() << "\n";
            cout << "  Numero de surtidores: " << estacion->getNumSurtidores() << "\n\n";
        }
    }
};

void menuGestionRed(RedNacional& red) {
    int opcion;
    do {
        cout << "\nMenu Gestion de la Red:\n";
        cout << "1. Agregar Estacion\n";
        cout << "2. Eliminar Estacion\n";
        cout << "3. Calcular Ventas\n";
        cout << "4. Fijar Precio de Combustible\n";
        cout << "5. Mostrar Precios de Combustible\n";
        cout << "6. Mostrar Estaciones\n";  // Nueva opción
        cout << "0. Volver al Menu Principal\n";
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            char nombre[50], codigo[20], gerente[50], region[50];
            cout << "Ingrese nombre de la estacion: ";
            cin >> nombre;
            cout << "Ingrese codigo de la estacion: ";
            cin >> codigo;
            cout << "Ingrese nombre del gerente: ";
            cin >> gerente;

            // Validación de la región
            bool regionValida = false;
            do {
                cout << "Ingrese region (Norte, Centro, Sur): ";
                cin >> region;
                if (strcmp(region, "Norte") == 0 || strcmp(region, "Centro") == 0 || strcmp(region, "Sur") == 0) {
                    regionValida = true;
                } else {
                    cout << "Region no válida. Por favor, elija entre Norte, Centro o Sur." << endl;
                }
            } while (!regionValida);

            // Crear nueva estación
            EstacionDeServicio* nuevaEstacion = new EstacionDeServicio(nombre, codigo, gerente, region, 3);

            // Agregar la nueva estación a la red
            red.agregarEstacion(nuevaEstacion);

            cout << "Estacion creada exitosamente: " << nombre << endl;

            break;
        }

        case 2: {
            char codigo[20];
            cout << "Ingrese codigo de la estacion a eliminar: ";
            cin >> codigo;
            red.eliminarEstacion(codigo);
            break;
        }
        case 3: {
            red.calcularVentas();
            break;
        }
        case 4: {
            char categoria[20];
            float precio;
            cout << "Ingrese categoria de combustible: ";
            cin >> categoria;
            cout << "Ingrese nuevo precio: ";
            cin >> precio;
            for (int i = 0; i < red.getNumEstaciones(); ++i) {
                red.getEstacion(i)->fijarPrecio(categoria, precio);
            }
            break;
        }
        case 5: {
            for (int i = 0; i < red.getNumEstaciones(); ++i) {
                red.getEstacion(i)->mostrarPrecios();
            }
            break;
        }
        case 6: {
            red.mostrarEstaciones();  // Nueva opción para mostrar estaciones
            break;
        }
        case 0:
            cout << "Volviendo al Menu Principal." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
}

void menuGestionEstaciones(RedNacional& red) {
    int opcion;
    do {
        cout << "\nMenu Gestion de Estaciones de Servicio:\n";
        cout << "1. Agregar Surtidor\n";
        cout << "2. Eliminar Surtidor\n";
        cout << "3. Simular Venta de Combustible\n";
        cout << "4. Activar/Desactivar Surtidor\n";
        cout << "5. Mostrar surtidores\n";
        cout << "6. Consultar historico de transacciones\n";  // Nueva opción
        cout << "0. Volver al Menu Principal\n";
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            char codigoEstacion[20], codigoSurtidor[20], modelo[20];
            cout << "Ingrese codigo de la estacion: ";
            cin >> codigoEstacion;
            for (int i = 0; i < red.getNumEstaciones(); ++i) {
                if (strcmp(red.getEstacion(i)->getCodigo(), codigoEstacion) == 0) {
                    cout << "Ingrese codigo del surtidor: ";
                    cin >> codigoSurtidor;
                    cout << "Ingrese modelo del surtidor: ";
                    cin >> modelo;
                    Surtidor* nuevoSurtidor = new Surtidor(codigoSurtidor, modelo);
                    red.getEstacion(i)->agregarSurtidor(nuevoSurtidor);
                    cout << "Surtidor agregado a la estacion." << endl;
                    break;
                }
            }
            break;
        }
        case 2: {
            char codigoEstacion[20], codigoSurtidor[20];
            cout << "Ingrese codigo de la estacion: ";
            cin >> codigoEstacion;
            for (int i = 0; i < red.getNumEstaciones(); ++i) {
                if (strcmp(red.getEstacion(i)->getCodigo(), codigoEstacion) == 0) {
                    cout << "Ingrese codigo del surtidor a eliminar: ";
                    cin >> codigoSurtidor;
                    red.getEstacion(i)->eliminarSurtidor(codigoSurtidor);
                    break;
                }
            }
            break;
        }
        case 3: {
            char codigoEstacion[20], codigoSurtidor[20], categoria[20], metodoPago[20], documentoCliente[20];
            float cantidad, monto;
            cout << "Ingrese codigo de la estacion: ";
            cin >> codigoEstacion;
            for (int i = 0; i < red.getNumEstaciones(); ++i) {
                if (strcmp(red.getEstacion(i)->getCodigo(), codigoEstacion) == 0) {
                    cout << "Ingrese codigo del surtidor: ";
                    cin >> codigoSurtidor;
                    cout << "Ingrese cantidad: ";
                    cin >> cantidad;
                    cout << "Ingrese categoria de combustible: ";
                    cin >> categoria;
                    cout << "Ingrese metodo de pago: ";
                    cin >> metodoPago;
                    cout << "Ingrese documento del cliente: ";
                    cin >> documentoCliente;
                    cout << "Ingrese monto: ";
                    cin >> monto;
                    red.getEstacion(i)->registrarVentaEnSurtidor(codigoSurtidor, cantidad, categoria, metodoPago, documentoCliente, monto);
                    break;
                }
            }
            break;
        }
        case 4: { // Opción para activar/desactivar un surtidor
            char codigoEstacion[20], codigoSurtidor[20];
            cout << "Ingrese codigo de la estacion: ";
            cin >> codigoEstacion;
            for (int i = 0; i < red.getNumEstaciones(); ++i) {
                if (strcmp(red.getEstacion(i)->getCodigo(), codigoEstacion) == 0) {
                    cout << "Ingrese codigo del surtidor: ";
                    cin >> codigoSurtidor;

                    // Buscar el surtidor por código
                    Surtidor* surtidorEncontrado = nullptr;
                    for (int j = 0; j < red.getEstacion(i)->getNumSurtidores(); ++j) {
                        if (strcmp(red.getEstacion(i)->getSurtidor(j)->getCodigo(), codigoSurtidor) == 0) {
                            surtidorEncontrado = red.getEstacion(i)->getSurtidor(j);
                            break;
                        }
                    }

                    if (surtidorEncontrado) {
                        char accion;
                        cout << "Activar o desactivar? (a/d): ";
                        cin >> accion;
                        if (accion == 'a') {
                            surtidorEncontrado->activar(); // Activar el surtidor
                            cout << "Surtidor activado." << endl;
                        } else if (accion == 'd') {
                            surtidorEncontrado->desactivar(); // Desactivar el surtidor
                            cout << "Surtidor desactivado." << endl;
                        } else {
                            cout << "Accion no válida." << endl;
                        }
                    } else {
                        cout << "Surtidor no encontrado." << endl;
                    }
                    break;
                }
            }
            break;
        }
        case 5: {
            char codigoEstacion[20];
            cout << "Ingrese codigo de la estacion: ";
            cin >> codigoEstacion;
            bool encontrado = false;
            for (int i = 0; i < red.getNumEstaciones(); ++i) {
                if (strcmp(red.getEstacion(i)->getCodigo(), codigoEstacion) == 0) {
                    red.getEstacion(i)->mostrarSurtidores();
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                cout << "Estacion no encontrada." << endl;
            }
            break;
        }
        case 6: { // Opción para consultar el histórico de transacciones de cada surtidor
            char codigoEstacion[20];
            cout << "Ingrese codigo de la estacion: ";
            cin >> codigoEstacion;
            bool encontrado = false;
            for (int i = 0; i < red.getNumEstaciones(); ++i) {
                if (strcmp(red.getEstacion(i)->getCodigo(), codigoEstacion) == 0) {
                    red.getEstacion(i)->consultarHistoricoTodosSurtidores();
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                cout << "Estacion no encontrada." << endl;
            }
            break;
        }
        case 0:
            cout << "Volviendo al Menu Principal." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
}

void simularVenta(EstacionDeServicio& estacion) {
    if (!estacion.tieneSurtidoresActivos()) {
        cout << "No hay surtidores activos en la estacion " << estacion.getNombre() << endl;
        return;
    }

    // Seleccionar un surtidor activo aleatoriamente
    int surtidorIndex;
    do {
        surtidorIndex = rand() % estacion.getNumSurtidores();
    } while (!estacion.getSurtidor(surtidorIndex)->estaActivo());

    Surtidor* surtidorSeleccionado = estacion.getSurtidor(surtidorIndex);

    // Generar cantidad aleatoria entre 3 y 20 litros
    int cantidadLitros = rand() % 18 + 3; // 3 a 20 litros

    // Seleccionar categoría de combustible aleatoriamente
    int categoriaIndex = rand() % estacion.getNumCategorias();
    string categoriaCombustible = estacion.getCategoria(categoriaIndex);
    float precioPorLitro = estacion.getPrecio(categoriaIndex);

    // Calcular el monto total
    float montoTotal = cantidadLitros * precioPorLitro;

    // Simular datos del cliente y método de pago
    const char* metodoPago = "Tarjeta"; // Ejemplo fijo
    const char* documentoCliente = "12345678"; // Ejemplo fijo

    // Registrar la venta en el surtidor seleccionado
    surtidorSeleccionado->registrarVenta(cantidadLitros, categoriaCombustible.c_str(), metodoPago, documentoCliente, montoTotal);

    // Mostrar los datos de la transacción
    cout << "\nTransaccion registrada:\n";
    cout << "Surtidor: " << surtidorSeleccionado->getCodigo() << endl;
    cout << "Cantidad: " << cantidadLitros << " litros\n";
    cout << "Categoria: " << categoriaCombustible << endl;
    cout << "Monto Total: $" << montoTotal << endl;
}

void menuPrincipal(RedNacional& red) {
    int opcion;
    do {
        cout << "\nMenu Principal:\n";
        cout << "1. Gestion de la Red\n";
        cout << "2. Gestion de Estaciones de Servicio\n";
        cout << "3. Sistema nacional de verificacion de fugas\n";
        cout << "4. Simulacion de ventas\n";
        cout << "0. Salir\n";
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            menuGestionRed(red);
            break;
        case 2:
            menuGestionEstaciones(red);
            break;
        case 3: { // Nueva opción para verificar fugas
            char codigo[20];
            cout << "Ingrese codigo de la estacion para verificar fugas: ";
            cin >> codigo;
            for (int i = 0; i < red.getNumEstaciones(); ++i) {
                if (strcmp(red.getEstacion(i)->getCodigo(), codigo) == 0) {
                    red.getEstacion(i)->verificarFugas();
                    break;
                }
            }
            break;
        }
        case 4: { // Nueva opción para simular ventas
            char codigo[20];
            cout << "Ingrese codigo de la estacion para simular venta: ";
            cin >> codigo;

            for (int i = 0; i < red.getNumEstaciones(); ++i) {
                if (strcmp(red.getEstacion(i)->getCodigo(), codigo) == 0) {
                    simularVenta(*red.getEstacion(i));
                    break;
                }
            }

            break;
        }
        case 0:
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    RedNacional red;

    // Crear estaciones y surtidores
    EstacionDeServicio* estacion1 = new EstacionDeServicio("Estacion 1", "E001", "Gerente 1", "Sur", 3);
    Surtidor* surtidor1 = new Surtidor("S001", "Modelo A");

    // Ventas ajustadas para que solo se detecte fuga en Ecoextra
    // Ventas de ejemplo
    // Ajusta las ventas de esta forma
    surtidor1->registrarVenta(90, "Regular", "Efectivo", "12345678", 90 * 1.0);  // Total vendido: 90 litros (sin fuga)
    surtidor1->registrarVenta(150, "Premium", "Tarjeta", "87654321", 150 * 1.5); // Total vendido: 150 litros (sin fuga)
    surtidor1->registrarVenta(360, "Ecoextra", "Efectivo", "12312312", 360 * 1.2); // Total vendido: 360 litros (con fuga)


    estacion1->agregarSurtidor(surtidor1);
    red.agregarEstacion(estacion1);

    // Crear otra estación para mostrar que no hay fugas en otras categorías
    EstacionDeServicio* estacion2 = new EstacionDeServicio("Estacion 2", "E002", "Gerente 2", "Norte", 3);
    Surtidor* surtidor2 = new Surtidor("S002", "Modelo B");


    estacion2->agregarSurtidor(surtidor2);
    red.agregarEstacion(estacion2);


    // Mostrar menú y verificar fugas
    menuPrincipal(red);

    return 0;
}
