#include "ros/ros.h"
#include "interaccion/usuario.h"
#include "interaccion/multiplicador.h"
#include <iostream>
#include <vector>
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include <ctime>

using namespace std;

class Clock {
public:
    void startFunctionCallback(const std_msgs::String::ConstPtr& msg){

        startTime = ros::Time::now().toSec();       //guardamos el tiempo a la entrada del bucle en la variable startTime (en segundos).
        suscriptorReset = nodo1.subscribe("reset_topic", 0, &Clock::resetFunctionCallback, this);       //suscribimos el objeto suscriptor al topic reset_topic, con funcion callback resetFunctionCallback
        publicador = nodo1.advertise<std_msgs::Bool>("still_alive", 0);     //indicamos que el objeto publicador publica en el topic still_alive
        flag.data = 0;      //inicializamos el mensaje still_alive a 0

        while(ros::ok()){
            time_t seconds = ros::Time::now().toSec();      //obtenemos el tiempo actual (en segundos)
            cout << "Local: " << asctime(localtime(&seconds));      //imprimimos el tiempo local
            cout << "  GMT: " << asctime(gmtime(&seconds));     //imprimimos el tiempo GMT

            //imprimimos por pantalla el tiempo transcurrido desde la entrada del bucle
            cout << "Han transcurrido " << (seconds-startTime) << " segundos desde el " ;
            if (reset){
                cout << "reset" << endl;
            }
            else{
                cout << "comienzo" << endl;
            }

            //si han transcurrido 60 segundos, se publica 1 en el topico still_alive
            //la variable temp sirve para que aunque la frecuencia de refresco sea superior a 1 Hz, tan solo se publique el mensaje 1 vez
            if (((seconds-startTime+1)%61 == 0) && (temp != seconds))
            {
                temp = seconds;
                flag.data = 1;
                publicador.publish(flag);
            }

            //dormimos el periodo 1/rate y se procesa el flujo de mensajes
            ros::Duration(1./rate).sleep();
            ros::spinOnce();
        }
    }

    //la funcion resetCallback simplemente vuelve a establecer un nuevo tiempo de entrada al bucle y fija la variable reset a True. Hecho esto, el programa continua iterando el bucle de startFunctionCallback
    void resetFunctionCallback(const std_msgs::String::ConstPtr& msg){
        startTime = ros::Time::now().toSec();
        reset = 1;
        ROS_INFO("Timer has been reset");
    }

private:
    ros::NodeHandle nodo1;      //declaracion de objeto NodeHandle
    ros::Subscriber suscriptorReset;       //declaracion del suscriptor que recibira el mensaje para resetear el temporizador
    ros::Publisher publicador;      //declaracion del publicador que manda el menseje still_alive cada 60 segundos
    time_t startTime, temp;     //variables de tipo time_t (libreria <ctime>) empleadas para manejar los periodos del temporizador
    std_msgs::Bool flag;        //mensaje que envia el publicador
    float rate = 3.;        //frecuencia de refresco del temporizador por pantalla en Hz
    bool reset = 0;     //flag que indica si es la primera vez que se entra en la funcion callback o si es un reseteo
};

int main(int argc, char **argv){
    ros::init(argc, argv, "reloj_nodo");        //inicializacion del nodo reloj_nodo
    ros::NodeHandle nodo;       //instanciamos un NodeHandle
    ROS_INFO("reloj_nodo creado y registrado");

    Clock clock;        //declaramos un objeto Clock que servira para manejar las callback Functions.

    ros::Subscriber subscriptor = nodo.subscribe("start_topic", 0, &Clock::startFunctionCallback, &clock);      //declaramos un objeto subscriptor, con la funcion callback startFunctionCallback

    ros::spin();    //se refresca el flujo de mensajes

    return 0;
}


