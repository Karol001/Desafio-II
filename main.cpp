#include <iostream>
#include <string>
#include <vector>

// Clase Transaccion
class Transaccion {
private:
    std::string fecha;
    std::string hora;
    float cantidad;
    std::string categoriaCombustible;
    std::string metodoPago;
    std::string documentoCliente;
    float monto;

public:
    Transaccion() = default;

    Transaccion(const std::string& fecha, const std::string& hora, float cantidad,
                const std::string& categoriaCombustible, const std::string& metodoPago,
                const std::string& documentoCliente, float monto)
        : fecha(fecha), hora(hora), cantidad(cantidad), categoriaCombustible(categoriaCombustible),
        metodoPago(metodoPago), documentoCliente(documentoCliente), monto(monto) {}

    void mostrarTransaccion() const {
        std::cout << "Fecha: " << fecha << ", Hora: " << hora
                  << ", Cantidad: " << cantidad << " litros, Categoría: " << categoriaCombustible
                  << ", Pago: " << metodoPago << ", Cliente: " << documentoCliente
                  << ", Monto: $" << monto << std::endl;
    }
};

// Clase Surtidor
class Surtidor {
private:
    std::string codigo;
    std::string modelo;
    bool activo;
    std::vector<Transaccion> transacciones;

public:
    Surtidor(const std::string& codigo, const std::string& modelo)
        : codigo(codigo), modelo(modelo), activo(true) {}

    void registrarVenta(const Transaccion& nuevaTransaccion) {
        transacciones.push_back(nuevaTransaccion);
        std::cout << "Venta registrada en surtidor " << codigo << std::endl;
    }

    std::vector<Transaccion> consultarTransacciones() const {
        return transacciones;
    }

    std::string getCodigo() const {
        return codigo;
    }
};

// Clase EstacionDeServicio
class EstacionDeServicio {
private:
    std::string nombre;
    std::string codigo;
    std::string gerente;
    std::string region;
    std::pair<float, float> ubicacionGPS;
    std::vector<std::pair<std::string, float>> capacidadTanque;
    std::vector<Surtidor> surtidores;

public:
    EstacionDeServicio(const std::string& nombre, const std::string& codigo, const std::string& gerente,
                       const std::string& region, std::pair<float, float> ubicacionGPS)
        : nombre(nombre), codigo(codigo), gerente(gerente), region(region), ubicacionGPS(ubicacionGPS) {}

    std::string getCodigo() const {
        return codigo;
    }

    void agregarSurtidor(const Surtidor& nuevoSurtidor) {
        surtidores.push_back(nuevoSurtidor);
        std::cout << "Surtidor agregado a la estación " << nombre << std::endl;
    }

    void eliminarSurtidor(const std::string& codigoSurtidor) {
        for (auto it = surtidores.begin(); it != surtidores.end(); ++it) {
            if (it->getCodigo() == codigoSurtidor && it->consultarTransacciones().empty()) {
                surtidores.erase(it);
                std::cout << "Surtidor " << codigoSurtidor << " eliminado de la estación " << nombre << std::endl;
                return;
            }
        }
        std::cout << "No se encontró el surtidor " << codigoSurtidor << " o tiene transacciones registradas." << std::endl;
    }

    std::vector<Transaccion> consultarTransacciones() const {
        std::vector<Transaccion> todasTransacciones;
        for (const auto& surtidor : surtidores) {
            auto transacciones = surtidor.consultarTransacciones();
            todasTransacciones.insert(todasTransacciones.end(), transacciones.begin(), transacciones.end());
        }
        return todasTransacciones;
    }

    float calcularVenta(const std::string& categoriaCombustible) const {
        float totalVentas = 0.0f;
        return totalVentas;
    }
};

// Clase RedNacional
class RedNacional {
private:
    std::vector<EstacionDeServicio> estaciones;
    std::vector<std::pair<std::string, float>> preciosPorRegion;

public:
    void agregarEstacion(const EstacionDeServicio& nuevaEstacion) {
        estaciones.push_back(nuevaEstacion);
        std::cout << "Estación de servicio agregada a la red nacional." << std::endl;
    }

    void eliminarEstacion(const std::string& codigoEstacion) {
        for (auto it = estaciones.begin(); it != estaciones.end(); ++it) {
            if (it->getCodigo() == codigoEstacion && it->consultarTransacciones().empty()) {
                estaciones.erase(it);
                std::cout << "Estación de servicio eliminada de la red nacional." << std::endl;
                return;
            }
        }
        std::cout << "No se encontró la estación de servicio o tiene transacciones." << std::endl;
    }

    float calcularVentas(const std::string& codigoEstacion, const std::string& categoriaCombustible) const {
        float totalVentas = 0.0f;
        for (const auto& estacion : estaciones) {
            if (estacion.getCodigo() == codigoEstacion) {
                totalVentas += estacion.calcularVenta(categoriaCombustible);
            }
        }
        return totalVentas;
    }
};

int main() {
    // Prueba del sistema
    RedNacional miRed;
    std::cout << "Sistema inicializado correctamente." << std::endl;

    return 0;
}
