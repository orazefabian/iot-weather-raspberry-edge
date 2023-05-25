#include <RF24/RF24.h>
#include <iostream>
#include <unistd.h>

RF24 radio(15,0);
const uint8_t ADDRESS[2][6] = {"1Node", "2Node"};

struct SensorData{
	float temperature;
	float humidity;
};

void setup(){

	if(!radio.begin()){
	    std::cout << "cannot start radio!!" << std::endl;
	}else {
	    std::cout << "receiving started!!" << std::endl;
	}
	radio.setPayloadSize(sizeof(SensorData));
	radio.openWritingPipe(ADDRESS[0]);
	radio.openReadingPipe(1, ADDRESS[1]);

	radio.startListening();
}


void loop(){
	if(radio.available()){
		SensorData data{};
		radio.read(&data, sizeof(data));
		std::cout << "temperature: " <<  data.temperature << " humidity: " << data.humidity << std::endl;
	}else{
		std::cout << "no data available..." << std::endl;
	}
}

int main(){
	setup();
	while(1){
		loop();
		sleep(1);
	}
	return 0;
}
