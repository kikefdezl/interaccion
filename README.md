# interaccion

Make python scripts executable:
```
roscd interaccion
cd scripts
chmod +x *.py
```
To run all nodes simultaneously(must have xterm installed):
```
$ roslaunch interaccion interaccion.launch
```
To install xterm:
```
$ sudo apt-get install xterm
```

# Recording and playing with Rosbag (for quicker debugging)

First run all nodes (f.e. with roslaunch). Then:
```
$ cd
$ mkdir bagfiles
$ cd bagfiles
$ rosbag record -a
```
Then fill in all the actions in emocion_nodo, pos_usuario_nodo, inf_personal_nodo. Once done, press Ctrl+C in the rosbag terminal. It should stop recording and generate the bag file.
Tu run it:
```
$rosbag play "bagfile".bag
```
To run it at a quicker speed:
```
$rosbag play "bagfile".bag -r 20
```

# Install Google Text-to-Speech
## [Make ROS Melodic compatible with Python 3](https://dhanoopbhaskar.com/blog/2020-05-07-working-with-python-3-in-ros-kinetic-or-melodic/)
> If ROS needs to support python3 we may have to recompile ROS source code using python3 which is not practical. So what we can do is to run python3 programs, separately and connect using ROS bridge (if we use custom messages (ROS msg)). However, if we are not using any custom rosmsg and using only built-in rosmsg, we can do the following steps to run python3 codes in ROS (without using a ROS bridge).

After installing ROS, install rospkg for python3
```
sudo apt install python3-pip python3-all-dev python3-rospkg
```
This will prompt to install python3-rospkg and to remove ROS packages (already installed). Select Yes for that prompt. This will remove ROS packages and we will have to re-install them.
```
sudo apt install ros-melodic-desktop-full --fix-missing
```
This will complete the installation part. Now comes the coding part.

Just include the following directive as the first line of your program code (file) which should be executed using python3.
```
#!/usr/bin/env python3
```

## Python libraries

Install Python 3 pip:
```
sudo apt install python3-pip
```
### [gTTS](https://gtts.readthedocs.io/en/latest/)
```
pip3 install gTTS
```
### [Playsound](https://pypi.org/project/playsound/)
```
pip3 install playsound
```

## Test Text-to-Speech
Run in one terminal:
```
roscore
```
In the second terminal:
```
rosrun interaccion tts.py
```
And in the third terminal:
```
rostopic pub /speech std_msgs/String "Hola. Esto es una prueba de síntesis de voz"
```

## [Run nodes from different computers](https://www.youtube.com/watch?v=Y4yRNOQXD5I)
