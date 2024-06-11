#include <Audio.h>
#include <Wire.h>

#define DISPLAY 1

#ifdef DISPLAY

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OSCMessage.h>
#include <SLIPEncodedSerial.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C
#define OLED_RESET (-1)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif

SLIPEncodedUSBSerial slip(Serial);

// GUItool: begin automatically generated code
AudioInputI2SQuad i2s_quad1;      //xy=336,677
AudioSynthNoisePink pink1;          //xy=338,824
AudioSynthWaveformSine sine1;          //xy=340,784
AudioInputUSB usb1;           //xy=341,743
AudioAnalyzePeak peak5;          //xy=603,433
AudioAnalyzePeak peak1;          //xy=604,299
AudioAnalyzePeak peak2;          //xy=605,332
AudioAnalyzePeak peak3;          //xy=605,366
AudioAnalyzePeak peak6;          //xy=605,467
AudioAnalyzePeak peak4;          //xy=607,399
AudioAnalyzeRMS rms5;           //xy=618,1246
AudioAnalyzeRMS rms6;           //xy=620,1279
AudioAnalyzeRMS rms3;           //xy=621,1180
AudioAnalyzeRMS rms1;           //xy=622,1115
AudioAnalyzeRMS rms2;           //xy=622,1148
AudioAnalyzeRMS rms4;           //xy=622,1213
AudioMixer4 mixer1;         //xy=787,364
AudioMixer4 mixer4; //xy=788,502
AudioMixer4 mixer2;         //xy=789,428
AudioMixer4 mixer5; //xy=790,566
AudioMixer4 mixer7; //xy=791,640
AudioMixer4 mixer8; //xy=793,704
AudioMixer4 mixer10; //xy=795,773
AudioMixer4 mixer11; //xy=797,837
AudioMixer4 mixer13; //xy=799,913
AudioMixer4 mixer14; //xy=801,977
AudioMixer4 mixer16; //xy=803,1046
AudioMixer4 mixer17; //xy=805,1110
AudioMixer4 mixer3;         //xy=949,395
AudioMixer4 mixer6; //xy=951,536
AudioMixer4 mixer9; //xy=951,673
AudioMixer4 mixer12; //xy=955,803
AudioMixer4 mixer15; //xy=956,948
AudioMixer4 mixer18; //xy=957,1075
AudioOutputI2SQuad i2s_quad2;      //xy=1324,614
AudioOutputUSB usb2;           //xy=1331,997
AudioAnalyzeRMS rms7;           //xy=1335,1094
AudioAnalyzeRMS rms8;           //xy=1336,1126
AudioAnalyzeRMS rms11;          //xy=1336,1221
AudioAnalyzeRMS rms12;          //xy=1336,1254
AudioAnalyzeRMS rms9;           //xy=1337,1158
AudioAnalyzeRMS rms10;          //xy=1338,1190
AudioAnalyzePeak peak7;          //xy=1342,270
AudioAnalyzePeak peak9;          //xy=1342,335
AudioAnalyzePeak peak10;         //xy=1342,366
AudioAnalyzePeak peak8;          //xy=1343,303
AudioAnalyzePeak peak11;         //xy=1343,397
AudioAnalyzePeak peak12;         //xy=1343,428
AudioConnection patchCord1(i2s_quad1, 1, peak1, 0);
AudioConnection patchCord2(i2s_quad1, 1, rms1, 0);
AudioConnection patchCord3(i2s_quad1, 1, mixer1, 0);
AudioConnection patchCord4(i2s_quad1, 1, mixer4, 0);
AudioConnection patchCord5(i2s_quad1, 1, mixer7, 0);
AudioConnection patchCord6(i2s_quad1, 1, mixer10, 0);
AudioConnection patchCord7(i2s_quad1, 1, mixer13, 0);
AudioConnection patchCord8(i2s_quad1, 1, mixer16, 0);
AudioConnection patchCord9(i2s_quad1, 0, mixer1, 1);
AudioConnection patchCord10(i2s_quad1, 0, mixer4, 1);
AudioConnection patchCord11(i2s_quad1, 0, mixer7, 1);
AudioConnection patchCord12(i2s_quad1, 0, mixer10, 1);
AudioConnection patchCord13(i2s_quad1, 0, mixer13, 1);
AudioConnection patchCord14(i2s_quad1, 0, mixer16, 1);
AudioConnection patchCord15(i2s_quad1, 0, peak2, 0);
AudioConnection patchCord16(i2s_quad1, 0, rms2, 0);
AudioConnection patchCord17(i2s_quad1, 3, mixer1, 2);
AudioConnection patchCord18(i2s_quad1, 3, mixer4, 2);
AudioConnection patchCord19(i2s_quad1, 3, mixer7, 2);
AudioConnection patchCord20(i2s_quad1, 3, mixer10, 2);
AudioConnection patchCord21(i2s_quad1, 3, mixer13, 2);
AudioConnection patchCord22(i2s_quad1, 3, mixer16, 2);
AudioConnection patchCord23(i2s_quad1, 3, peak3, 0);
AudioConnection patchCord24(i2s_quad1, 3, rms3, 0);
AudioConnection patchCord25(i2s_quad1, 2, mixer1, 3);
AudioConnection patchCord26(i2s_quad1, 2, mixer4, 3);
AudioConnection patchCord27(i2s_quad1, 2, mixer7, 3);
AudioConnection patchCord28(i2s_quad1, 2, mixer10, 3);
AudioConnection patchCord29(i2s_quad1, 2, mixer13, 3);
AudioConnection patchCord30(i2s_quad1, 2, mixer16, 3);
AudioConnection patchCord31(i2s_quad1, 2, peak4, 0);
AudioConnection patchCord32(i2s_quad1, 2, rms4, 0);
AudioConnection patchCord33(pink1, 0, mixer2, 3);
AudioConnection patchCord34(pink1, 0, mixer5, 3);
AudioConnection patchCord35(pink1, 0, mixer8, 3);
AudioConnection patchCord36(pink1, 0, mixer11, 3);
AudioConnection patchCord37(pink1, 0, mixer14, 3);
AudioConnection patchCord38(pink1, 0, mixer17, 3);
AudioConnection patchCord39(sine1, 0, mixer2, 2);
AudioConnection patchCord40(sine1, 0, mixer5, 2);
AudioConnection patchCord41(sine1, 0, mixer8, 2);
AudioConnection patchCord42(sine1, 0, mixer11, 2);
AudioConnection patchCord43(sine1, 0, mixer14, 2);
AudioConnection patchCord44(sine1, 0, mixer17, 2);
AudioConnection patchCord45(usb1, 0, mixer2, 0);
AudioConnection patchCord46(usb1, 0, mixer5, 0);
AudioConnection patchCord47(usb1, 0, mixer8, 0);
AudioConnection patchCord48(usb1, 0, mixer11, 0);
AudioConnection patchCord49(usb1, 0, mixer14, 0);
AudioConnection patchCord50(usb1, 0, mixer17, 0);
AudioConnection patchCord51(usb1, 0, peak5, 0);
AudioConnection patchCord52(usb1, 0, rms5, 0);
AudioConnection patchCord53(usb1, 1, mixer2, 1);
AudioConnection patchCord54(usb1, 1, mixer5, 1);
AudioConnection patchCord55(usb1, 1, mixer8, 1);
AudioConnection patchCord56(usb1, 1, mixer11, 1);
AudioConnection patchCord57(usb1, 1, mixer14, 1);
AudioConnection patchCord58(usb1, 1, mixer17, 1);
AudioConnection patchCord59(usb1, 1, peak6, 0);
AudioConnection patchCord60(usb1, 1, rms6, 0);
AudioConnection patchCord61(mixer1, 0, mixer3, 0);
AudioConnection patchCord62(mixer4, 0, mixer6, 0);
AudioConnection patchCord63(mixer2, 0, mixer3, 1);
AudioConnection patchCord64(mixer5, 0, mixer6, 1);
AudioConnection patchCord65(mixer7, 0, mixer9, 0);
AudioConnection patchCord66(mixer8, 0, mixer9, 1);
AudioConnection patchCord67(mixer10, 0, mixer12, 0);
AudioConnection patchCord68(mixer11, 0, mixer12, 1);
AudioConnection patchCord69(mixer13, 0, mixer15, 0);
AudioConnection patchCord70(mixer14, 0, mixer15, 1);
AudioConnection patchCord71(mixer16, 0, mixer18, 0);
AudioConnection patchCord72(mixer17, 0, mixer18, 1);
AudioConnection patchCord73(mixer3, 0, i2s_quad2, 0);
AudioConnection patchCord74(mixer3, rms7);
AudioConnection patchCord75(mixer3, peak7);
AudioConnection patchCord76(mixer6, 0, i2s_quad2, 1);
AudioConnection patchCord77(mixer6, rms8);
AudioConnection patchCord78(mixer6, peak8);
AudioConnection patchCord79(mixer9, 0, i2s_quad2, 2);
AudioConnection patchCord80(mixer9, rms9);
AudioConnection patchCord81(mixer9, peak9);
AudioConnection patchCord82(mixer12, 0, i2s_quad2, 3);
AudioConnection patchCord83(mixer12, rms10);
AudioConnection patchCord84(mixer12, peak10);
AudioConnection patchCord85(mixer15, 0, usb2, 0);
AudioConnection patchCord86(mixer15, rms11);
AudioConnection patchCord87(mixer15, peak11);
AudioConnection patchCord88(mixer18, 0, usb2, 1);
AudioConnection patchCord89(mixer18, rms12);
AudioConnection patchCord90(mixer18, peak12);
// GUItool: end automatically generated code

AudioControlSGTL5000 sgtl5000_1;
AudioControlSGTL5000 sgtl5000_2;

AudioMixer4 *matrix[6][2] = {
	{&mixer1,  &mixer2},
	{&mixer4,  &mixer5},
	{&mixer7,  &mixer8},
	{&mixer10, &mixer11},
	{&mixer13, &mixer14},
	{&mixer16, &mixer17},
};

AudioAnalyzeRMS *ent_rms[12] = {
	&rms1,
	&rms2,
	&rms3,
	&rms4,
	&rms5,
	&rms6,
	&rms7,
	&rms8,
	&rms9,
	&rms10,
	&rms11,
	&rms12,
};


AudioAnalyzePeak *ent_peak[12] = {
	&peak1,
	&peak2,
	&peak3,
	&peak4,
	&peak5,
	&peak6,
	&peak7,
	&peak8,
	&peak9,
	&peak10,
	&peak11,
	&peak12,
};

String cmdbuffer = "";
bool echo = false;
bool send_meters = false;

void
set_crosspoint(int channel, int bus, float gain)
{
	matrix[bus][channel / 4]->gain(channel % 4, gain);
}

float
get_crosspoint(int channel, int bus)
{
	return matrix[bus][channel / 4]->getGain(channel % 4);
}

void
set_mix(int bus, float in1, float in2, float in3, float in4, float in5, float in6)
{
	bus--;
	matrix[bus][0]->gain(0, in1);
	matrix[bus][0]->gain(1, in2);
	matrix[bus][0]->gain(2, in3);
	matrix[bus][0]->gain(3, in4);
	matrix[bus][1]->gain(0, in5);
	matrix[bus][1]->gain(1, in6);
	matrix[bus][1]->gain(2, 0.0f);
	matrix[bus][1]->gain(3, 0.0f);
}

void
reset_state()
{
	// room PA
	set_mix(1, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// livestream
	set_mix(2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// Headphones
	set_mix(3, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	set_mix(4, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);

	// USB out
	set_mix(5, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	set_mix(6, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

void
onOscChannel(OSCMessage &msg, int patternOffset)
{
	char buf[12];
	int channel = -1;
	int addr;
	int offset;

	// /ch/<num>
	for (int i = 0; i < 6; i++) {
		sprintf(buf, "/%d", i);
		offset = msg.match(buf, patternOffset);
		if (offset) {
			channel = i;
			addr = offset + patternOffset;
			break;
		}
	}
	if (channel < 0) return;

	// /ch/<num>/mix
	offset = msg.match("/mix", addr);
	addr += offset;
	if (offset < 1) return;

	// /ch/<num>/mix/<bus>/level
	int bus = -1;
	for (int i = 0; i < 6; i++) {
		sprintf(buf, "/%d/level", i);
		int offset = msg.match(buf, addr);
		if (offset) {
			bus = i;
			break;
		}
	}
	if (bus < 0) return;

	if (msg.isFloat(0)) {
		set_crosspoint(channel, bus, msg.getFloat(0));
	} else {
		char address[22];
		snprintf(address, 22, "/ch/%d/mix/%d/level", channel, bus);
		OSCMessage response(address);
		response.add(get_crosspoint(channel, bus));
		slip.beginPacket();
		response.send(slip);
		slip.endPacket();
	}
}

void
onPacketReceived(OSCMessage msg)
{
	msg.route("/ch", onOscChannel);
}

void
setup()
{

#ifdef DISPLAY
	if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
		//Serial.println(F("SSD1306 allocation failed"));
	}
	display.display();
	delay(200);
	display.clearDisplay();
#endif

	AudioMemory(64);
	reset_state();

	sgtl5000_1.enable();
	sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000_1.volume(0.5);
	sgtl5000_1.lineInLevel(0, 0);
	sgtl5000_1.adcHighPassFilterDisable();

	sgtl5000_2.setWire(1);
	sgtl5000_2.enable();
	sgtl5000_2.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000_2.volume(0.5);
	sgtl5000_2.lineInLevel(0, 0);
	sgtl5000_2.adcHighPassFilterDisable();

	slip.begin(115200);
}

float
rmsToDb(float rms_in)
{
	// -40 - +7
	float dB = 20.0f * log10f(rms_in * 2.0f) + 6.0f;
	return dB;
}

float levels_rms[12];
float levels_peak[12];


void
loop()
{
	int size;
	OSCMessage msg;
	if (slip.available()) {
		while (!slip.endofPacket()) {
			if ((size = slip.available()) > 0) {
				while (size--)
					msg.fill(slip.read());
			}
		}
		if (!msg.hasError()) {
			onPacketReceived(msg);
		}
	}

	if (rms1.available()) {
		for (int i = 0; i < 12; i++) {
			levels_rms[i] = ent_rms[i]->read();
			levels_peak[i] = ent_peak[i]->read();
		}

#ifdef DISPLAY
		display.clearDisplay();

		for (int i = 0; i < 12; i++) {
			uint16_t offset = i > 5 ? 8 : 0;
			display.fillRect(10 * i + 1 + offset,
				SCREEN_HEIGHT - 11 - (int16_t) (((rmsToDb(levels_rms[i]) + 40.0f) / 47.0f) * SCREEN_HEIGHT), 6,
				SCREEN_HEIGHT, SSD1306_WHITE);
		}

		display.fillRect(0, SCREEN_HEIGHT - 11, SCREEN_WIDTH, 11, SSD1306_BLACK);
		display.fillRoundRect(0, SCREEN_HEIGHT - 10, 10, 10, 1, SSD1306_WHITE);
		display.fillRoundRect(10, SCREEN_HEIGHT - 10, 10, 10, 1, SSD1306_WHITE);
		display.fillRoundRect(20, SCREEN_HEIGHT - 10, 10, 10, 1, SSD1306_WHITE);
		display.fillRoundRect(30, SCREEN_HEIGHT - 10, 10, 10, 1, SSD1306_WHITE);
		display.fillRoundRect(40, SCREEN_HEIGHT - 10, 20, 10, 1, SSD1306_WHITE);

		display.fillRoundRect(68, SCREEN_HEIGHT - 10, 10, 10, 1, SSD1306_WHITE);
		display.fillRoundRect(78, SCREEN_HEIGHT - 10, 10, 10, 1, SSD1306_WHITE);
		display.fillRoundRect(88, SCREEN_HEIGHT - 10, 20, 10, 1, SSD1306_WHITE);
		display.fillRoundRect(108, SCREEN_HEIGHT - 10, 20, 10, 1, SSD1306_WHITE);

		display.setTextSize(1);
		display.setTextColor(SSD1306_BLACK);
		for (int i = 0; i < 4; i++) {
			display.setCursor(i * 10 + 2, SCREEN_HEIGHT - 9);
			display.write('1' + i);
		}
		display.setCursor(41, SCREEN_HEIGHT - 9);
		display.write("USB");

		display.setCursor(70, SCREEN_HEIGHT - 9);
		display.write('1');
		display.setCursor(80, SCREEN_HEIGHT - 9);
		display.write('2');

		display.setCursor(89, SCREEN_HEIGHT - 9);
		display.write("AFL");

		display.setCursor(109, SCREEN_HEIGHT - 9);
		display.write("USB");

		display.display();
#endif
	}

}

int
main()
{
	setup();
	while (1) {
		loop();
	}
};