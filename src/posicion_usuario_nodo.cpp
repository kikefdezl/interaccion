#include "ros/ros.h"
#include "interaccion/pos_usuario.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    ros::init(argc, argv, "posicion_usuario_nodo");
    ros::NodeHandle nodo;
    ROS_INFO("posicion_usuario_nodo creado y registrado");

    ros::Publisher publicadorPosicion = nodo.advertise<interaccion::pos_usuario>("pos_usuario_topic",0);

    ros::Duration seconds_sleep(1);
    int x, y, z;

    while (ros::ok()){

        interaccion::pos_usuario posicionAEnviar;

        cout << "Introduce la posicion X" << endl;
        cin >> x;
        cout << "Introduce la posicion Y" << endl;
        cin >> y;
        cout << "Introduce la posicion Z" << endl;
        cin >> z;
        posicionAEnviar.x = x;
        posicionAEnviar.y = y;
        posicionAEnviar.z = z;

        publicadorPosicion.publish(posicionAEnviar);

        ros::spinOnce();

        ROS_DEBUG ("Se duerme el nodo emisor durante un segundo");
    }
}
