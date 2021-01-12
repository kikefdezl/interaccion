#include <iostream>
#include <string>
#include "ros/ros.h"
#include "interaccion/inf_personal_usuario.h"
#include <vector>



int main(int argc, char **argv)
{
    ros::init(argc, argv, "informacion_personal_nodo"); //incicializacion del nodo informacion_personal_nodo
    ros::NodeHandle nodo; //declaracion del NodeHandle

    ros::Publisher informacion_pub = nodo.advertise<interaccion::inf_personal_usuario>("inf_pers_topic", 0); //creacion del publicador con el topic inf_pers_topic

    //variables para almacenar la informacion
    int x; 
    std::string a;
    int i;
    std::string id;

    while (ros::ok()){
       interaccion::inf_personal_usuario infoAEnviar;   //se crea el objeto inf_personal_usuario 
       infoAEnviar.idiomas.clear(); //se vacia el vector idiomas en cada iteracion

       //se pide introducir la informacion por terminal 
       std::cout <<"Intruduzca su nombre: " << "\n";
       std::cin >> a;

       infoAEnviar.nombre = a;

       std::cout <<"Introduzca su edad: " << "\n";
       std::cin >> x;

       infoAEnviar.edad = x;

       std::cout <<"¿Cuantos idiomas habla?: " << "\n";
       std::cin >> i;


       //bucle para introducir tantos idiomas como se han indicado 
       for (int j = 0; j < i; j++){
           std::cout <<"Introduzca los idiomas que habla: " << "\n";
           std::cin >> id;
           infoAEnviar.idiomas.push_back(id);
       }


       informacion_pub.publish(infoAEnviar);    //publicacion del mensaje

       ros::spinOnce();
    }
    return 0;
}
