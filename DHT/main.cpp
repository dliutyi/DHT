#include "Controller.h"
#include "Configuration.h"

int main() {
	Controller controller;
	controller.Start(Config.input_file);
}