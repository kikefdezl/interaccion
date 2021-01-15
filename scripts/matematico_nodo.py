#!/usr/bin/env python

from interaccion.srv import multiplicador
import rospy


def multiply(req):
    #Servicio que multiplica por 2 el valor recibido
    multiplication=int(req.entrada*2) #La entrada se multiplica por 2 y se convierte en entero
    rospy.loginfo("Multiplicando: %s x 2 = %s"%(req.entrada, multiplication)) #Se muestra un mensaje por terminal del calculo realizado
    return multiplication #Se envia el resultado

def multiply_server():
    rospy.init_node('matematico_nodo') #Se inicializa el nodo
    s = rospy.Service('servicio_multiplicador', multiplicador, multiply) #Se declara el servicio "multiplicador_nodo"
    rospy.loginfo("Listo para multiplicar...")#Se avisa por terminal que el servicio esta disponible
    rospy.spin() #Se mantiene el nodo activo

if __name__ == "__main__":
    multiply_server()