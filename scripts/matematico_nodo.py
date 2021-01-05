#!/usr/bin/env python

from interaccion.srv import multiplicador
import rospy

def multiply(req):
    multiplication=int(req.entrada*2)
    rospy.loginfo("Multiplicando: %s x 2 = %s"%(req.entrada, multiplication))
    return multiplication

def multiply_server():
    rospy.init_node('matematico_nodo')
    s = rospy.Service('servicio_multiplicador', multiplicador, multiply)
    rospy.loginfo("Listo para multiplicar...")
    rospy.spin()

if __name__ == "__main__":
    multiply_server()