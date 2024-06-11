#!/usr/bin/env python3
import argparse
import tabulate

from pythonosc.osc_message_builder import OscMessageBuilder

from typing import Union

from pythonosc.osc_bundle import OscBundle
from pythonosc.osc_message import OscMessage

import serial


class SLIPClient:
    END = b'\xc0'
    ESC = b'\xdb'
    ESC_END = b'\xdc'
    ESC_ESC = b'\xdd'

    def __init__(self, device, baudrate=9600, **kwargs):
        self.ser = serial.Serial(device, baudrate=baudrate, **kwargs)

    def send(self, content: Union[OscMessage, OscBundle]) -> None:
        encoded = self.END
        encoded += content.dgram.replace(self.ESC, self.ESC + self.ESC_ESC).replace(self.END, self.ESC + self.ESC_END)
        encoded += self.END
        self.ser.write(encoded)

    def receive(self):
        buffer = b''
        while True:
            c = self.ser.read(1)
            if c is None:
                return None

            if c == self.END:
                if len(buffer):
                    break
                continue

            if c == self.ESC:
                c = self.ser.read(1)
                if c is None:
                    return None
                if c == self.ESC_END:
                    buffer += self.END
                elif c == self.ESC_ESC:
                    buffer += self.ESC
            else:
                buffer += c

        return OscMessage(buffer)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('device')
    parser.add_argument('--set', action='append', help='Set crosspoint gain in SRC-DST:GAIN format')
    parser.add_argument('--show', action='store_true', help='Display mixing matrix after adjustments')
    args = parser.parse_args()

    inputs = ['IN1', 'IN2', 'IN3', 'PC', 'USB1', 'USB2']
    outputs = ['OUT1', 'OUT2', 'HP1', 'HP2', 'USB1', 'USB2']

    client = SLIPClient(args.device, 1152000)

    if args.set is not None:
        for change in args.set:
            crosspoint, gain = change.split(':', maxsplit=1)
            src, dst = crosspoint.split('-', maxsplit=1)
            channel = inputs.index(src)
            bus = outputs.index(dst)
            gain = float(gain)

            message = OscMessageBuilder(f"/ch/{channel}/mix/{bus}/level")
            message.add_arg(gain)
            client.send(message.build())
        if not args.show:
            return

    result = []
    head = ['#'] + outputs

    for ch in range(0, 6):
        row = [inputs[ch]]
        for bus in range(0, 6):
            message = OscMessageBuilder(f"/ch/{ch}/mix/{bus}/level").build()
            client.send(message)
            response = client.receive()
            level = response.params[0]
            row.append(level if level > 0 else '.')
        result.append(row)
    print(tabulate.tabulate(result, headers=head))


if __name__ == '__main__':
    main()

