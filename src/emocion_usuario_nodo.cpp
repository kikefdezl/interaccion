#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>


int main(int argc, char **argv)
{
   ros::init(argc, argv, "emocion_usuario_nodo"); //se inicializa el nodo emocion_usuario_nodo
   ros::NodeHandle nodo; //se declara un NodeHandle

   ros::Publisher emocion_pub = nodo.advertise<std_msgs::String>("emocion_topic",0); //declaración del publicador con el topic emocion_topic, no se guarda en un objeto mensaje por ser un standard message por lo que se usa std_msgs


   while (ros::ok()){

       std_msgs::String msg; //creacion del standard message 

       std::string input; //creacion de un string para guardar lo introducido por terminal y posteriormente convertirlo al standard message

       std::cout << "Introduzca su emoción expresada: " << "\n"; //se pide introducir la emocion por terminal y se almacena dentro del string msg
       std::cin >> input;

       msg.data = input;

       emocion_pub.publish(msg); //publicacion de la emocion

       ros::spinOnce();
   }

   return 0;
}
