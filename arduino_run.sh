WORKDIR=/tmp/arduino
mkdir -p $WORKDIR
cp $1 $WORKDIR/arduino.ino
arduino-cli compile --fqbn arduino:avr:uno $WORKDIR > /dev/null
arduino-cli upload -p /dev/cu.usbmodem14201 --fqbn arduino:avr:uno $WORKDIR
rm -rf $WORKDIR
