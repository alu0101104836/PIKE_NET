#include "../include/socket.hpp"
#include "../include/file.hpp"
#include <cstdlib>

std::atomic_int quit_app(0);
std::atomic_int abr(0);
std::atomic_int abort_receive(0);
std::atomic_int send_receive(0);
/*
signal(
  SIGUSR1,
  &mod_siguser
);
struct sigaction act = {
    .sa_handler = &mi_manejador_de_sigterm, 
    .sa_sigaction = NULL,   
    .sa_mask = 0,           
}

sigaction(
    SIGUSR1, 
    &act,    
    NULL     
);*/


void net_send(std::string &fichero)
{
  if (quit_app != 1 || abr != 2 || abr != 3 || abr != 4)
  {
    sockaddr_in local_address = make_ip_address(8000, "127.0.0.1");
    sockaddr_in remote_address = make_ip_address(8001, "127.0.0.1");

    Socket socket_local(local_address);

    //Pasamos nombre del fichero a el receive
    Message nombre_fichero;
    fichero.copy(nombre_fichero.text.data(), nombre_fichero.text.size() - 1, 0);
    socket_local.send_to(nombre_fichero, remote_address);
    std::cout << "Nombre del fichero: " << fichero << std::endl;

    // Abrimos fichero para lectura
    file_ fichero_send("send/" + fichero, false);

    // Size del fichero para enviar al receive
    Message size;
    int size_f = fichero_send.getSize();
    std::string buffer = std::to_string(size_f);
    std::cout << "Size: " << buffer << std::endl;

    buffer.copy(size.text.data(), size.text.size() - 1, 0);
    socket_local.send_to(size, remote_address);

    // Envio del mensaje por TCP básico
    Message envio;
    char *p = (char *)fichero_send.data_();
    std::string buffer_(p);
    buffer_.copy(envio.text.data(), envio.text.size() - 1, 0);
    socket_local.send_to(envio, remote_address);
    std::cout << "Mensaje: " << buffer_ << std::endl;

    send_receive = 0;
  }
  else
    std::cout << "Caso atomico activado" << std::endl;
}

void net_receive(std::string &nombre_directorio)
{
  if (quit_app != 1 || abort_receive != 5)
  {
    sockaddr_in local_address = make_ip_address(8001, "127.0.0.1");
    sockaddr_in remote_address = make_ip_address(8000, "127.0.0.1");

    Socket socket_local(local_address);

    if (mkdir(nombre_directorio.c_str(), 0777) == -1)
      std::cerr << std::endl << "Error : " << std::strerror(errno) << std::endl ;
    else
      std::cout << "Se ha creado el directorio " << nombre_directorio << std::endl;

    // Recibimos el nombre del fichero
    Message nombre;
    socket_local.receive_from(nombre, remote_address);
    std::string nombre_;
    nombre_ = nombre.text.data();
    nombre_.resize(nombre_.size() - 4);
    std::cout << "Nombre del fichero: " << nombre_ << std::endl;

    Message size;
    socket_local.receive_from(size, remote_address);
    int size_f;
    size_f = std::atoi((char *)size.text.data());
    std::cout << "Size_receive: " << size_f << std::endl;

    Message mensaje;
    socket_local.receive_from(mensaje, remote_address);
    std::string aux = mensaje.text.data();
    std::cout << "Mensaje: " << aux << std::endl;

    file_ fichero_send("send/" + nombre_, true, size_f);

    //fichero_send.escribir(aux);
    fichero_send.write_file(aux);

    send_receive = 0;
  }
  else
    std::cout << "Caso atomico activado" << std::endl;
}

void get_entrada(std::string &entrada, std::string &extra)
{
  std::string var;
  extra = "NULL";
  entrada = "A";
  std::thread hilo3;
  std::thread hilo2;

  while (quit_app != 1)
  {
    std::cout << std::endl;
    std::cout << "Entrada: ";
    std::cin >> var;
    std::cout << std::endl;

    if (var == "receive")
    {
      std::cout << "Receive" << std::endl
                << std::endl;
      std::cout << "Directorio a guardar: ";
      std::cin >> extra;

      hilo3 = std::thread (net_receive, std::ref(extra));
      send_receive = 1;
    }
    else if (var == "send")
    {
      std::cout << "Send" << std::endl
                << std::endl;
      std::cout << "Nombre del archivo a enviar: ";
      std::cin >> extra;

      hilo2 = std::thread (net_send, std::ref(extra));
      //hilo2.join();
      send_receive = 2;
    }
    else if (var == "abort")
    {
      std::cout << "Abort" << std::endl
                << std::endl;
      std::cout << "Opción extra: ";
      std::cin >> extra;

      if (extra == "receive")
        abort_receive = 5;
      else
        abr = 2;
    }
    else if (var == "resume")
    {
      std::cout << "Resume" << std::endl
                << std::endl;
      abr = 3;
    }
    else if (var == "pause")
    {
      std::cout << "Pause" << std::endl
                << std::endl;
      abr = 4;
    }
    else if (var == "quit")
    {
      std::cout << "Quit" << std::endl
                << std::endl;
      quit_app = 1;
    }

    if (var != "quit")
      entrada = var;
    else
      entrada = "B";
  }

  
  std::cout << "Salida: " << entrada << std::endl;
}

int protected_main(void)
{
  std::string salida_funcion = "NULL";
  std::string opcion;

  sigset_t set;

  sigemptyset(&set);
  sigaddset(&set, SIGINT);
  sigaddset(&set, SIGUSR1);
  std::thread hilo1;
  while (quit_app != 1)
  {
    hilo1 = std::thread (get_entrada, std::ref(salida_funcion), std::ref(opcion));
    hilo1.join();
    std::cout << "Fin de hilo 1 & join" << std::endl;

    if (salida_funcion != "NULL")
      std::cout << "Ejecución de la linea de comandos: " << salida_funcion << std::endl;
    else
      std::cout << "Salida: quit" << std::endl;

    if (opcion != "NULL")
      std::cout << "Con la opción: " << opcion << std::endl;

    if (opcion == "receive")
      return 3;

    if (send_receive == 2)
    {
      //std::thread hilo2(net_send, std::ref(opcion));
      std::cout << "Función send" << std::endl;
      //hilo2.join();
    }

    if (send_receive == 1)
    {
      //std::thread hilo3(net_receive, std::ref(opcion));
      std::cout << "Función receive" << std::endl;
      //hilo3.join();
    }
  }

  return 0;
}

int main(void)
{
  try
  {
    return protected_main();
  }
  catch (std::bad_alloc &e)
  {
    std::cerr << "mytalk"
              << ": memoria insuficiente\n";
    return 1;
  }
  catch (std::system_error &e)
  {
    std::cerr << "mytalk"
              << ": " << e.what() << '\n';
    return 2;
  }
  catch (...)
  {
    std::cout << "Error desconocido\n";
    return 99;
  }
  return 0;
}
