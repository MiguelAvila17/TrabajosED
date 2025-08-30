using System;
public class Persona
{
    public string Nombre { get; set; }
    public int Edad { get; set; }

    public Persona(string nombre, int edad)
    {
        Nombre = nombre;
        Edad = edad;
    }
}
class Program
{
    static void Main(string[] args)
    {
        Persona p1 = new Persona("Miguel Angel", 19);
        Console.WriteLine($"{p1.Nombre}, {p1.Edad}");
    }
}
