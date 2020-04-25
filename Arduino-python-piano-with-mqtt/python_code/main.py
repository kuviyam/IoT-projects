# Arduino piano
# this code reads 7 digit hex values from serial port and plays corresponding notes

import os
import serial
import pysynth as ps
import paho.mqtt.client as mqtt

SERIAL_PORT = '/dev/ttyACM0'
SERIAL_RATE = 115200


keystate0 = [False] * 12
keystate1 = [False] * 12
keystate2 = [False] * 12

oct_cur = 0
oct_state = False
octave_select = "4"

def play_sound(duration, note):
    freq = float(ps.getfreq()[0][note])
    print(note)
    os.system('play -nq -t alsa synth {} sine {} &'.format(duration, freq))
    # sudo apt install sox


def play(octave_select, zero, one, two, three, four, five, six):
    global keystate0, keystate1, keystate2
    note = ['c', 'c#', 'd', 'd#', 'e', 'f', 'f#', 'g', 'g#', 'a', 'a#', 'b', 'b#']

    oct0 = "000000000"+zero
    for i in range(0,12):
        if oct0[i] == '0' and keystate0[i] == False:
            keystate0[i] = True
            play_sound(0.1, note[i]+str(int(octave_select)-1))
        elif oct0[i] == '1':
            keystate0[i] = False

    oct1 = one + two + three
    for i in range(0,12):
        if oct1[i] == '0' and keystate1[i] == False:
            keystate1[i] = True
            play_sound(0.1, note[i]+octave_select)
        elif oct1[i] == '1':
            keystate1[i] = False

    oct2 = four + five + six
    for i in range(0,12):
        if oct2[i] == '0' and keystate2[i] == False:
            keystate2[i] = True
            play_sound(0.1, note[i]+str(int(octave_select)+1))
        elif oct2[i] == '1':
            keystate2[i] = False


def main():
    global oct_cur, octave_select
    ser = serial.Serial(SERIAL_PORT, SERIAL_RATE)
    while True:
        try:
            reading = ser.readline().decode('utf-8').rstrip().upper()
            if len(reading) == 7:
                zero = str("{0:04b}".format(int(reading[0], 16))) #     SWITCH a3 a#3 b3
                one = str("{0:04b}".format(int(reading[1], 16)))  #     c4 c#4 d4 d#4
                two = str("{0:04b}".format(int(reading[2], 16)))  #     e4 f4 f#4 g4
                three = str("{0:04b}".format(int(reading[3], 16)))#     g#4 a4 a#4 b4
                four = str("{0:04b}".format(int(reading[4], 16))) #     c5 c#5 d5 d#5
                five = str("{0:04b}".format(int(reading[5], 16))) #     e5 f5 f#5 g5
                six = str("{0:04b}".format(int(reading[6], 16)))  #     g#5 a5 a#5 b5

                # Toggle octave select switch state
                if zero[3] == '0' and oct_state == False:
                    oct_state = True
                    if (oct_cur < 1):
                        oct_cur = oct_cur + 1
                    else:
                        oct_cur = 0
                elif zero[3] == '1':
                    oct_state = False
                octave_select = str(oct_cur + 4)

                play(octave_select, zero[0:3][::-1], one[::-1], two[::-1], three[::-1],
                     four[::-1], five[::-1], six[::-1])
        except Exception as e:
            print("Exception occured",e)


if __name__ == "__main__":
    main()
