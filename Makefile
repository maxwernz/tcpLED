all:
	gcc server.c led.cpp ws2812-rpi.cpp -o server_led