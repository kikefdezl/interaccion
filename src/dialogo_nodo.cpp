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

        //imprimimos por pantalla la informacion del mensaje usuario.msg
        cout << "Nombre del usuario: " << msg->infPersonal.nombre << endl;
        cout << "Edad del usuario: " << unsigned(msg->infPersonal.edad) << endl;
        cout << "El usuario habla los siguientes idiomas:" << endl;
        for(int i = 0; i< msg->infPersonal.idiomas.size(); i++)
        {
            cout << msg->infPersonal.idiomas.at(i) << endl;
        }
        cout << "La emoción del usuario es: " << msg->emocion << endl;
        cout << "El usuario se encuentra en la posicion x: " << unsigned(msg->posicion.x) << "  y: " << unsigned(msg->posicion.y) << "  z: " << unsigned(msg->posicion.z) << endl;

        interaccion::multiplicador srv;     //declaramos un mensaje/servicio de tipo multiplicador
        srv.request.entrada = msg->infPersonal.edad;        //establecemos la entrada del mensaje como la edad del usuario
        client.call(srv);       //llamada al servicio
        cout << "El doble de la edad es: " << srv.response.resultado << endl;       //se imprime por la pantalla el resultado (el doble de la edad)

        //publicamos mensaje para iniciar o resetear el temporizador de reloj_nodo. Si es la primera vez, se publica en start_topic, y se repite se publica en reset_topic
        std_msgs::String text;
        text.data = "ok";
        if (reset == 0) {
            publicadorStart.publish(text);
            reset = 1;
        }
        else{
            publicadorReset.publish(text);
        }

        //sintetizamos el texto con espeak
        system(command.c_str());
    }

    //la segunda funcion callback escucha al topic still_alive y el recibir el mensaje imprime que el temporizador sigue activo
    void functionCallback2(const std_msgs::Bool::ConstPtr& msg){
        cout << "El temporizador sigue activo." << endl;
    }

private:
    bool reset = 0;
    ros::NodeHandle nodo;       //declaramos un NodeHandle
    ros::ServiceClient client = nodo.serviceClient<interaccion::multiplicador>("servicio_multiplicador");       //declaramos un objeto cliente del servicio servicio_multiplicador
    ros::Publisher publicadorStart = nodo.advertise<std_msgs::String>("start_topic", 0);        //declaramos un publicador que manda el mensaje de inicio al reloj_nodo
    ros::Publisher publicadorReset = nodo.advertise<std_msgs::String>("reset_topic", 0);        //declaramos un publicador que manda el mensaje de reseteo al reloj_nodo

    string texto = "Este es el texto a sintetizar";     //declaracion del texto a ser sintetizado por espeak
    string command = "espeak -v es \"" + texto + "\"";      //declaracion del comando a sistema para sintetizar el texto con espeak
};

int main(int argc, char **argv){
    ros::init(argc, argv, "dialogo_nodo");      //inicializacion del nodo dialogo_nodo
    ros::NodeHandle nodo;       //instanciamos un NodeHandle
    ROS_INFO("dialogo_nodo creado y registrado");

    Listener listener;      //declaramos un objeto Listener, que maneja todas las funciones callback. Esto permite el intercambio de variables entre las funciones callback

    ros::Subscriber suscriptor1 = nodo.subscribe("user_topic", 0, &Listener::funcionCallback, &listener);      //declaracion del objeto suscriptor1, con funcion callback funcionCallback
    ros::Subscriber suscriptor2 = nodo.subscribe("still_alive", 0, &Listener::functionCallback2, &listener);        //declaracion del objeto suscriptor2, con funcion callback funcionCallback2
    ros::spin();

    return 0;
}
