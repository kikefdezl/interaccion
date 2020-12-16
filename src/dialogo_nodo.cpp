#include "ros/ros.h"
#include "interaccion/usuario.h"
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

void funcionCallback(const interaccion::usuario::ConstPtr& msg){
    cout << "Nombre del usuario: " << msg->infPersonal.nombre << endl;
    cout << "Edad del usuario: " << unsigned(msg->infPersonal.edad) << endl;
    cout << "El usuario habla los siguientes idiomas:" << endl;
    for(int i = 0; i< msg->infPersonal.idiomas.size(); i++)
    {
        cout << msg->infPersonal.idiomas.at(i) << endl;
    }
    cout << "La emocion del usuario es: " << msg->emocion << endl;
    cout << "El usuario se encuentra en la posicion x: " << unsigned(msg->posicion.x) << "  y: " << unsigned(msg->posicion.y) << "  z: " << unsigned(msg->posicion.z) << endl;
}

int main(int argc, char **argv){
    //registra el nombre del nodo: dialogo_nodo
    ros::init(argc, argv, "dialogo_nodo");
    ros::NodeHandle nodoDialogo;
    ROS_INFO("dialogo_nodo creado y registrado"); //muestra en pantalla

    //si recibimos el mensaje cuyo topic ess: "user_topic" llamamos a la función manejadora: funcionCallback
    ros::Subscriber subscriptor = nodoDialogo.subscribe("user_topic", 0, funcionCallback);

    /** Loop infinito para que no finalice laejecución del nodo y siempre se pueda llamar al callback */
    ros::spin();

    return 0;
}
