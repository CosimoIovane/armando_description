# Armando Description Package

Questo pacchetto contiene il modello del braccio robotico Armando per Gazebo Harmonic, la configurazione della telecamera sul polso (Task 2) e il nodo C++ di teleoperazione (Task 3).

## Istruzioni per la Validazione

### 1. Avvio della Simulazione (Task 1)
Per compilare il pacchetto e lanciare il robot in Gazebo, apri un terminale ed esegui:

    cd ~/ros2_ws
    colcon build --packages-select armando_description
    source install/setup.bash
    ros2 launch armando_description armando_gazebo.launch.py


### 2. Visualizzazione Telecamera sul Polso (Task 2)
Per verificare il corretto funzionamento della telecamera montata sul polso del robot, apri un **nuovo terminale** ed esegui:

    rqt

1. Nel menu in alto di rqt, naviga su **Plugins > Visualization > Image View**.
2. Seleziona il topic `/wrist_camera/image_raw` dal menu a tendina.

### 3. Avvio del Controller e Movimento (Task 3)
Per muovere il braccio robotico da tastiera e osservare il movimento tramite la telecamera, apri un **terzo terminale** ed esegui:

    cd ~/ros2_ws
    source install/setup.bash
    ros2 run armando_description teleop_arm

**Comandi da tastiera:**
* **Q / A** : Ruota il giunto j0 (base)
* **W / S** : Ruota il giunto j1
* **E / D** : Ruota il giunto j2
* **R / F** : Ruota il giunto j3
* **CTRL+C** : Interrompi il nodo