import can
import struct
from pydbus import SessionBus
import asyncio
import time
from scipy.signal import bessel, lfilter
from piracer.vehicles import PiRacerStandard
from piracer.gamepads import ShanWanGamepad

bus = SessionBus()
piracer = PiRacerStandard()
shanwan_gamepad = ShanWanGamepad()

DBUS_INTERFACE = """
<node>
    <interface name="com.example.Chkout">
        <method name="handleError">
        </method>
    </interface>
</node>
"""

order = 3
b, a = bessel(order, 0.1)

def bessel_filter(data, zi=None):
    if zi is not None:
        y, zf = lfilter(b, a, data, zi=zi)
        return y[0], zf
    else:
        return lfilter(b, a, data)

class DbusData:
    """A class to interact with D-Bus and represent data."""
    bus = DBUS_INTERFACE

    def __init__(self):
        # Get D-Bus object
        start_time = time.time()
        while(time.time() - start_time < 10):
            try:
                self._dbus = bus.get("com.example.CanData", "/com/example/CanData/Data")
                break
            except Exception as e:
                print("Trying to Connect!!")
                time.sleep(0.5)
        
        self._current_speed = 0.0
        self._current_rpm = 0.0
        self._current_battery = 0
        self._current_throttle = -0.038


    def update(self, speed, rpm, battery):
        self._current_speed = speed
        self._current_rpm = rpm
        self._current_battery = battery
        print(f"Received RPM: {self._current_rpm}, Speed: {self._current_speed} Battery: {self._current_battery}")
        self._dbus.setData(speed, rpm, battery)
        print("1")

def receive_can_data(dbus_data):
    can_bus = can.interface.Bus(channel='can0', bustype='socketcan')
    print("2")
    
    zi_speed = [0.0] * order

    loop = asyncio.new_event_loop()  # Create a new event loop

    while True:

        message = loop.run_until_complete(asyncio.to_thread(can_bus.recv))
        if message is not None:
            data = message.data
            print("4")
            rpm, speed = struct.unpack('<ff', data)
            
            # Apply Bessel filter only to speed
            speed, zi_speed = bessel_filter([speed], zi_speed)
            
            if(speed < 0):
                speed = 0

            throttle = 1 
            print("5")
            # Continue with the rest of the logic
            
            battery_percentage = ((((piracer.get_battery_voltage() / 3) - 2.5) / 1.7) * 100)
            dbus_data.update(300 * speed, rpm, battery_percentage)
             

dbus_data = DbusData()
<<<<<<< HEAD
receive_can_data(dbus_data)

=======

# Start receiving CAN data and run the asyncio main loop
asyncio.run(receive_can_data(dbus_data))
>>>>>>> origin
