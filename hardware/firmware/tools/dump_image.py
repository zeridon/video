import sys
from PIL import Image

img = Image.open(sys.argv[1]).convert('RGBA')

sx = int(sys.argv[2])
sy = int(sys.argv[3])
w = int(sys.argv[4])
if len(sys.argv) >= 6:
    h = int(sys.argv[5])
else:
    h = (w * img.height) // img.width

img = img.resize((w, h))

def write_img_rgba():
    sys.stdout.buffer.write(f'\ndisplay.img rgba {sx} {sy} {w} {h}\n'.encode('utf-8'))

    for y in range(h):
        for x in range(w):
            r, g, b, a = img.getpixel((x, y))
            sys.stdout.buffer.write(bytes([r, g, b, a]))

    sys.stdout.buffer.write(f'display.refresh\n'.encode('utf-8'))

def write_img_565():
    sys.stdout.buffer.write(f'\ndisplay.img 565 {sx} {sy} {w} {h}\n'.encode('utf-8'))
    for y in range(h):
        for x in range(w):
            r, g, b, _ = img.getpixel((x, y))
            col = b | (g << 8) | (r << 16)
            c565 = (((col >> 8) & 0xf800) | ((col >> 5) & 0x07e0) | ((col >> 3) & 0x001f))
            sys.stdout.buffer.write(bytes([(c565 >> 8) & 0xff, (c565 >> 0) & 0xff]))
    sys.stdout.buffer.write(f'display.refresh\n'.encode('utf-8'))

write_img_rgba()
