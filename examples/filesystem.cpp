#include "../code/Elip.hpp"

int main()
{
    if (!Elip::ExistsFS("test.txt"))
    {
        Elip::Printf("{}\n", "No existe el archivo text.txt,creando el archivo");
        Elip::CreateFileFS("test.txt");
    }
    Elip::File data("./test.txt");
    data.Write("Hola mundo en c++");
    Elip::Printf("Datos del archivo: {}\n", data.ReadAsString());
}