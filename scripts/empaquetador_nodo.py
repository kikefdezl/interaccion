#!/usr/bin/env python

#Run "chmod +x *.py" in scripts folder

import rospy
import time
from std_msgs.msg import String
from interaccion.msg import pos_usuario, inf_personal_usuario, usuario

class packager:
  def __init__(self):
    self.pub = rospy.Publisher("user_topic",usuario,queue_size=10)

    self.informacion_personal_sub = rospy.Subscriber("inf_pers_topic",inf_personal_usuario,self.callback_informacion_personal)
    self.emocion_usuario_sub = rospy.Subscriber("emocion_topic",String,self.callback_emocion_usuario)
    self.posicion_usuario_sub = rospy.Subscriber("pos_usuario_topic",pos_usuario,self.callback_posicion_usuario)

    self.informacion_personal=inf_personal_usuario()
    self.emocion_usuario=String()
    self.posicion_usuario=pos_usuario()
    self.usuario=usuario()


  def callback_informacion_personal(self, data):
    rospy.loginfo(data)
    self.informacion_personal=data
    
  def callback_emocion_usuario(self, data):
    rospy.loginfo(data)
    self.emocion_usuario=data
    
  def callback_posicion_usuario(self, data):
    self.posicion_usuario=data
    rospy.loginfo(data)

  def package(self):

    if self.informacion_personal.nombre and self.emocion_usuario.data and self.posicion_usuario.x: #If all three messages are full
      
      #Build usuario msg
      self.usuario.infPersonal=self.informacion_personal
      self.usuario.emocion=self.emocion_usuario.data
      self.usuario.posicion=self.posicion_usuario

      #Publish
      try:
        self.pub.publish(self.usuario)
        rospy.loginfo("MENSAJE PUBLICADO")
      except:
        rospy.logerr("Mensaje NO publicado")

      #Reset msg variables
      self.informacion_personal=inf_personal_usuario()
      self.emocion_usuario=String()
      self.posicion_usuario=pos_usuario()

    else: #Wait
      time.sleep(1)

      
def main():
  p = packager()
  rospy.init_node('empaquetador_nodo', anonymous=True)
  rospy.loginfo("Empaquetador listo...")

  while not rospy.is_shutdown():
    p.package()

if __name__ == '__main__':
  main()