#include "ros/ros.h"
#include "interaccion/pos_usuario.h"
#include <iostream>

using namespace std;

/*** Este nodo llamado nodo_emisor emite mensajes "mensajeTest_topic" del tipo beginner_tutorials::mensajeTest*/
int main(int argc, char **argv) {
    ros::init(argc, argv, "posicion_usuario_nodo"); //registra el nombre del nodo
    ros::NodeHandle nodo;   //Creamos un objeto nodo
    ROS_INFO("posicion_usuario_nodo creado y registrado"); //to screen and file
    //es necesario "advertir" el tipo de mensaje a enviar y como lo hemos llamado (el topic). En este caso es de tipo userInfo y el topic se llama user_info_topic
    ros::Publisher publicadorPosicion = nodo.advertise<interaccion::pos_usuario>("pos_usuario_topic",0);
    //tiempo a dormir en cada iteracción
    ros::Duration seconds_sleep(1);
    int x, y, z;

    //ejecuta constantemente hasta recibir un Ctr+C
    while (ros::ok()){

        //instancimaos un mensaje que queremos enviar
        interaccion::pos_usuario posicionAEnviar;
        //en el mensaje enviamos el número de veces que se ha iteradoen este bucle
        cout << "Introduce la posicion X" << endl;
        cin >> x;
        cout << "Introduce la posicion Y" << endl;
        cin >> y;
        cout << "Introduce la posicion Z" << endl;
        cin >> z;
        posicionAEnviar.x = x;
        posicionAEnviar.y = y;
        posicionAEnviar.z = z;

        //se publica el mensaje
        publicadorPosicion.publish(posicionAEnviar);

        //en este programa no es necesario spinOnce, pero si tuviera una funcion de callback es imprescindible para que se ejecute
        ros::spinOnce();

        ROS_DEBUG ("Se duerme el nodo emisor durante un segundo");

        //dormimos el nodo durante un tiemposeconds_sleep.sleep();
    }
}
