Arduino Nano IMU & Buzzer Project


Description:

This project utilizes an Arduino Nano, a GY-85 IMU sensor, and a buzzer to analyze motion data and generate sound based on acceleration. The IMU captures acceleration values, which are processed to control the buzzer's frequency. Additionally, real-time motion data is plotted using Python.


Features:

    Reads acceleration data from a GY-85 IMU sensor.

    Filters out small variations to reduce noise.

    Maps acceleration values to buzzer frequencies.

    Visualizes 2D movement using Matplotlib in Python.

Components Used:

    Arduino Nano
    
    GY-85 IMU sensor
    
    Buzzer

Installation & Usage:

    Upload Arduino Code:
    
        Install the required GY-85 library.
        
        Flash the code onto the Arduino Nano.
        
    Run Python Script:
    
        Install dependencies: pip install pyserial matplotlib
        
        Run python imu_plot.py
        
    Observe Data on the Screen:
    
        The IMU values will be plotted in real-time.
        
        The buzzer will change frequency based on motion.
        

License:
This project is open-source under the MIT License. Feel free to modify and distribute it.

Author: Robert-Stefan PETCU
University POLITEHNICA of Bucharest
Faculty of Electronics, Telecommunications and Information Technology
