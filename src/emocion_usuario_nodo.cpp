#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>


int main(int argc, char **argv)
{
   ros::init(argc, argv, "emocion_usuario_nodo");
   ros::NodeHandle nodo;

   ros::Publisher emocion_pub = nodo.advertise<std_msgs::String>("emocion_topic",0);


   while (ros::ok()){

       std_msgs::String msg;

       std::string input;

       std::cout << "Introduzca su emoción expresada: " << "\n";
       std::cin >> input;

       msg.data = input;

       emocion_pub.publish(msg);

       ros::spinOnce();
   }

   return 0;
}
