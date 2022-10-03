all:
	g++ -std=c++14 server.cpp led.cpp ws2812-rpi.cpp -o server_led