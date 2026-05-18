import Foundation

// Clase base
class Pago {

    var monto: Double

    init(monto: Double) {
        self.monto = monto
    }

    func calcularPago() -> Double {
        return monto
    }

    func procesarPago() {
        print("Procesando pago...")
    }

    func mostrarInfo() {
        print("Monto: $\(calcularPago())")
    }
}

// Clase hija Tarjeta
class Tarjeta: Pago {

    override func procesarPago() {
        print("Pago realizado con tarjeta")
    }
}

// Clase hija Efectivo
class Efectivo: Pago {

    override func procesarPago() {
        print("Pago realizado en efectivo")
    }
}

// Clase hija Transferencia
class Transferencia: Pago {

    override func procesarPago() {
        print("Pago realizado por transferencia")
    }
}

// Programa principal

let p1: Pago = Tarjeta(monto: 1500)
let p2: Pago = Efectivo(monto: 700)
let p3: Pago = Transferencia(monto: 2500)

p1.mostrarInfo()
p1.procesarPago()

print()

p2.mostrarInfo()
p2.procesarPago()

print()

p3.mostrarInfo()
p3.procesarPago()