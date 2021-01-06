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
        startTime = ros::Time::now().toSec();
        subscriptorReset = nodoS.subscribe("reset_topic", 0, &Clock::resetFunctionCallback, this);
        publicador = nodoP.advertise<std_msgs::Bool>("still_alive", 0);
        flag.data = 0;
        while(ros::ok()){
            time_t seconds = ros::Time::now().toSec();
            cout << "Local: " << asctime(localtime(&seconds));
            cout << "  GMT: " << asctime(gmtime(&seconds));
            cout << "Han transcurrido " << (seconds-startTime) << " segundos desde el comienzo o reset." << endl;
            if (((seconds-startTime+1)%61 == 0) && (temp != seconds))
            {
                temp = seconds;
                flag.data = 1;
                publicador.publish(flag);
            }
            ros::Duration(1./rate).sleep();
            ros::spinOnce();
        }
    }

    void resetFunctionCallback(const std_msgs::String::ConstPtr& msg){
        startTime = ros::Time::now().toSec();
        ROS_INFO("Timer has been reset");
    }

private:
    ros::NodeHandle nodoS, nodoP;
    ros::Subscriber subscriptorReset;
    ros::Publisher publicador;
    time_t startTime, temp;
    std_msgs::Bool flag;
    float rate = 3.;
};

int main(int argc, char **argv){
    ros::init(argc, argv, "reloj_nodo");
    ros::NodeHandle nodo;
    ROS_INFO("reloj_nodo creado y registrado");

    Clock clock;

    ros::Subscriber subscriptor = nodo.subscribe("start_topic", 0, &Clock::startFunctionCallback, &clock);

    ros::spin();

    return 0;
}


