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
        cout << "Nombre del usuario: " << msg->infPersonal.nombre << endl;
        cout << "Edad del usuario: " << unsigned(msg->infPersonal.edad) << endl;
        cout << "El usuario habla los siguientes idiomas:" << endl;
        for(int i = 0; i< msg->infPersonal.idiomas.size(); i++)
        {
            cout << msg->infPersonal.idiomas.at(i) << endl;
        }
        cout << "La emocion del usuario es: " << msg->emocion << endl;
        cout << "El usuario se encuentra en la posicion x: " << unsigned(msg->posicion.x) << "  y: " << unsigned(msg->posicion.y) << "  z: " << unsigned(msg->posicion.z) << endl;

        //ros::ServiceClient client = nodo.serviceClient<interaccion::multiplicador>("servicio_multiplicador");
        interaccion::multiplicador srv;
        srv.request.entrada = msg->infPersonal.edad;
        client.call(srv);
        cout << "El doble de la edad es: " << srv.response.resultado << endl;

        std_msgs::String text;
        text.data = "ok";
        if (reset == 0) {
            publicadorStart.publish(text);
            reset = 1;
        }
        else{
            publicadorReset.publish(text);
        }
        system(command.c_str());
    }

    void functionCallback2(const std_msgs::Bool::ConstPtr& msg){
        cout << "El temporizador sigue activo." << endl;
    }

private:
    int edad;
    bool reset = 0;
    ros::NodeHandle nodo;
    ros::ServiceClient client = nodo.serviceClient<interaccion::multiplicador>("servicio_multiplicador");
    ros::Publisher publicadorStart = nodo.advertise<std_msgs::String>("start_topic", 0);
    ros::Publisher publicadorReset = nodo.advertise<std_msgs::String>("reset_topic", 0);
    string texto = "Este es el texto a sintetizar";
    string command = "espeak -v es \"" + texto + "\"";
};

int main(int argc, char **argv){
    ros::init(argc, argv, "dialogo_nodo");
    ros::NodeHandle nodo;
    ROS_INFO("dialogo_nodo creado y registrado");

    Listener listener;

    ros::Subscriber subscriptor1 = nodo.subscribe("user_topic", 0, &Listener::funcionCallback, &listener);
    ros::Subscriber subscriptor2 = nodo.subscribe("still_alive", 0, &Listener::functionCallback2, &listener);
    ros::spin();

    return 0;
}
