# Chronosmart

This is the arduino code for make work the project "Chronosmart".
There are two file that you have to load on the boards after pairing them each other through the AT mode.

# Chronosmart - Master.ino 
The master waits for the start signal from the slave wich in turn waits for the start of the app hence when the user click on the button "start" the slave send "1" to master and the system is turn On. When the runner is positioned in front of the first sensor the master turn on the green Led to signal that it will start to record time when the run starts.
Once the runner starts the Master send a signal to make the slave start to record time.


# Chronosmart - Slave.ino
The slave send the "1" to the master (when the user click on the "start button") and wait the signal (always from the master) to start the stopwatch. When the runner passes in front of the sensor, the slave stop the stopwatch and send the time to the Android app.
