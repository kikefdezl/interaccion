#include "ros/ros.h"
#include "interaccion/usuario.h"
#include "interaccion/multiplicador.h"
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

class Listener {
public:
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

        ros::NodeHandle nodo;
        ros::ServiceClient client = nodo.serviceClient<interaccion::multiplicador>("servicio_multiplicador");
        interaccion::multiplicador srv;
        srv.request.entrada = msg->infPersonal.edad;
        client.call(srv);
        cout << "El doble de la edad es: " << srv.response.resultado << endl;
    }

    int edad;
};

int main(int argc, char **argv){
    ros::init(argc, argv, "dialogo_nodo");
    ros::NodeHandle nodo;
    ROS_INFO("dialogo_nodo creado y registrado");

    Listener listener;

    ros::Subscriber subscriptor = nodo.subscribe("user_topic", 0, &Listener::funcionCallback, &listener);

    ros::spin();


    return 0;
}
