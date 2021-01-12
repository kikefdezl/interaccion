#!/usr/bin/env python

#Run "chmod +x *.py" in scripts folder

import rospy
import time
from std_msgs.msg import String
from interaccion.msg import pos_usuario, inf_personal_usuario, usuario

class packager:
  def __init__(self): 
    #Declaración del publisher
    self.pub = rospy.Publisher("user_topic",usuario,queue_size=10)

    #Declaración de los subscribers
    self.informacion_personal_sub = rospy.Subscriber("inf_pers_topic",inf_personal_usuario,self.callback_informacion_personal)
    self.emocion_usuario_sub = rospy.Subscriber("emocion_topic",String,self.callback_emocion_usuario)
    self.posicion_usuario_sub = rospy.Subscriber("pos_usuario_topic",pos_usuario,self.callback_posicion_usuario)

    #Se crean atributos de la clase de los tipos de mensaje que el nodo envía y recibe
    self.informacion_personal=inf_personal_usuario()
    self.emocion_usuario=String()
    self.posicion_usuario=pos_usuario()
    self.usuario=usuario()

  def callback_informacion_personal(self, data):
  #Se ejecuta cuando se publica en el topic "inf_pers_topic" y almacena la información en el atributo de la clase
    rospy.loginfo(data)
    self.informacion_personal=data
    
  def callback_emocion_usuario(self, data):
  #Se ejecuta cuando se publica en el topic "emocion_topic" y almacena la información en el atributo de la clase
    rospy.loginfo(data)
    self.emocion_usuario=data
    
  def callback_posicion_usuario(self, data):
  #Se ejecuta cuando se publica en el topic "pos_usuario_topic" y almacena la información en el atributo de la clase
    self.posicion_usuario=data
    rospy.loginfo(data)

  def package(self):
  #Método principal de la clase. Se espera hasta que se ha publicado en todos los topics y se envía el mensaje en "user_topic"

    if self.informacion_personal.nombre and self.emocion_usuario.data and self.posicion_usuario.x:
    #Comprobamos si ya se ha publicado en los topics verificando si el atributo de la clase está vacío. En el caso de "emocion_usuario" y
    #"posicion_usuario" que su mensaje esta formado por varios atributos, se comprueba solo el primero.
      
      #Se crea el mensaje usuario
      self.usuario.infPersonal=self.informacion_personal
      self.usuario.emocion=self.emocion_usuario.data
      self.usuario.posicion=self.posicion_usuario

      try:
        #Se publica el mensaje en "user_topic"
        self.pub.publish(self.usuario)
        rospy.loginfo("MENSAJE PUBLICADO")
      except:
        #Si hay algún error al publicar el mensaje, se muestra un error en la terminal
        rospy.logerr("Mensaje NO publicado")

      #Los atributos de la clase se resetean para realizar la comprobación en la próxima iteración
      self.informacion_personal=inf_personal_usuario()
      self.emocion_usuario=String()
      self.posicion_usuario=pos_usuario()

    else: 
      #Se espera 0.1 segundos para evitar que el nodo consuma muchos recursos
      time.sleep(0.1)
      
def main():
  p = packager() #Declaramos un objeto de tipo "packager"
  rospy.init_node('empaquetador_nodo', anonymous=True) #Inicializamos el nodo
  rospy.loginfo("Empaquetador listo...") #Feedback de que el nodo se ha iniciado en la terminal

  while not rospy.is_shutdown(): #Ejecutar el método package del objeto mientras que no se mate el nodo
    p.package()

if __name__ == '__main__':
  main()