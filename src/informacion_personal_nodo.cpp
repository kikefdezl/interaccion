#include <iostream>
#include <string>
#include "ros/ros.h"
#include "interaccion/inf_personal_usuario.h"
#include <vector>



int main(int argc, char **argv)
{
    ros::init(argc, argv, "informacion_personal_nodo");
    ros::NodeHandle nodo;

    ros::Publisher informacion_pub = nodo.advertise<interaccion::inf_personal_usuario>("inf_pers_topic", 0);

    ros::Duration seconds_sleep(1);

    int x;
    std::string a;
    int i;
    std::string id;

    while (ros::ok()){
       interaccion::inf_personal_usuario infoAEnviar;
       infoAEnviar.idiomas.clear();

       std::cout <<"Intruduzca su nombre: " << "\n";
       std::cin >> a;

       infoAEnviar.nombre = a;

       std::cout <<"Introduzca su edad: " << "\n";
       std::cin >> x;

       infoAEnviar.edad = x;

       std::cout <<"¿Cuantos idiomas habla?: " << "\n";
       std::cin >> i;



       for (int j = 0; j < i; j++){
           std::cout <<"Introduzca los idiomas que habla: " << "\n";
           std::cin >> id;
           infoAEnviar.idiomas.push_back(id);
       }


       informacion_pub.publish(infoAEnviar);

       ros::spinOnce();

       seconds_sleep.sleep();
    }
    return 0;
}
