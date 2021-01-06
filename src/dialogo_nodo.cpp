#include "ros/ros.h"
#include "interaccion/usuario.h"
#include "interaccion/multiplicador.h"
#include <string.h>
#include <iostream>
#include <vector>
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"

using namespace std;

class Listener {
public:
    void funcionCallback(const interaccion::usuario::ConstPtr& msg){
        static int counter = 0;
        cout << "Nombre del usuario: " << msg->infPersonal.nombre << endl;
        cout << "Edad del usuario: " << unsigned(msg->infPersonal.edad) << endl;
        cout << "El usuario habla los siguientes idiomas:" << endl;
        for(int i = 0; i< msg->infPersonal.idiomas.size(); i++)
        {
            cout << msg->infPersonal.idiomas.at(i) << endl;
        }
        cout << "La emocion del usuario es: " << msg->emocion << endl;
        cout << "El usuario se encuentra en la posicion x: " << unsigned(msg->posicion.x) << "  y: " << unsigned(msg->posicion.y) << "  z: " << unsigned(msg->posicion.z) << endl;

        ros::ServiceClient client = nodo.serviceClient<interaccion::multiplicador>("servicio_multiplicador");
        interaccion::multiplicador srv;
        srv.request.entrada = msg->infPersonal.edad;
        client.call(srv);
        cout << "El doble de la edad es: " << srv.response.resultado << endl;

        publicadorStart = nodoS.advertise<std_msgs::String>("start_topic", 0);

        std_msgs::String text;
        text.data = "ok";
        if (counter == 0) {
            publicadorStart.publish(text);
        }
        else{
            publicadorReset.publish(text);
        }
        //counter++;
    }
    void functionCallback2(const std_msgs::Bool::ConstPtr& msg){
        cout << "El temporizador sigue activo." << endl;
    }

private:
    int edad;
    ros::NodeHandle nodo, nodoS;
    ros::Publisher publicadorStart;
    ros::Publisher publicadorReset;
};

int main(int argc, char **argv){
    ros::init(argc, argv, "dialogo_nodo");
    ros::NodeHandle nodo1, nodo2;
    ROS_INFO("dialogo_nodo creado y registrado");

    Listener listener;

    ros::Subscriber subscriptor1 = nodo1.subscribe("user_topic", 0, &Listener::funcionCallback, &listener);
    ros::Subscriber subscriptor2 = nodo2.subscribe("still_alive", 0, &Listener::functionCallback2, &listener);
    ros::spin();

    return 0;
}
