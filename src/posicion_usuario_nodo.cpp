#include "ros/ros.h"
#include "interaccion/pos_usuario.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    ros::init(argc, argv, "posicion_usuario_nodo");     //inicializamos el nodo posicion_usuario_nodo
    ros::NodeHandle nodo;       //instanciamos un NodeHandle
    ROS_INFO("posicion_usuario_nodo creado y registrado");

    ros::Publisher publicadorPosicion = nodo.advertise<interaccion::pos_usuario>("pos_usuario_topic",0);        //declaramos un objeto de tipo publisher, con topic pos_usuario_topic

    ros::Duration seconds_sleep(1);     //aqui se establece la frecuencia de refresco del bucle principal
    int x, y, z;

    //entrada al bucle principal. ros::ok() devuelve 1 siempre que haya instancias de NodeHandles o siempre que no se pulse Ctrl+C en el terminal.
    while (ros::ok()){

        interaccion::pos_usuario posicionAEnviar;       //creamos un nuevo objeto de tipo pos_usuario (corresponde al mensaje pos_usuario.msg creado)

        //solicitamos por terminal las coordenadas del usuario y se introducen dentro del objeto mensaje
        cout << "Introduce la posicion X" << endl;
        cin >> x;
        cout << "Introduce la posicion Y" << endl;
        cin >> y;
        cout << "Introduce la posicion Z" << endl;
        cin >> z;
        posicionAEnviar.x = x;
        posicionAEnviar.y = y;
        posicionAEnviar.z = z;

        publicadorPosicion.publish(posicionAEnviar);        //publicamos el mensaje

        ros::spinOnce();        //se procesa la publicacion del mensaje

        seconds_sleep.sleep();      //dormimos el bucle 1 segundo
    }
}
