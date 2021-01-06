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

# Making a rosbag

To make a rosbag for quicker debugging:

First run all nodes (f.e. with roslaunch). Then:
```
$ roscd
$ mkdir bagfiles
$ cd bagfiles
$ rosbag record -a
```
Then do fill in all the actions in emocion_nodo, pos_usuario_nodo, inf_personal_nodo. Once done, press Ctrl+C in the rosbag terminal. It should generate the bag file.
Tu rerun it:
```
$rosbag play "bagfile".bag
```
To rerun it at a quicker speed:
```
$rosbag play "bagfile".bag -r 20
```
