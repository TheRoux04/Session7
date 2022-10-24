#pragma once
#include "Dispacher.hpp"
#include "Responders.hpp"

int main(int argc, char* argv[]){

    Dispacher central;

    central.addIncident("Fire");
    central.addIncident("Accident");
    central.addIncident("Hospilalisation");
    central.addIncident("Catastrophe");

    Policeman* John = new Policeman("John");
    FireFighter* hank = new FireFighter("Hank");
    Paramedic* mike = new Paramedic("Mike");

    central.available("Fire", hank);
    central.available("Accident", John);
    central.available("Hospilalisation", mike);
    central.available("Catastrophe", mike);
    central.available("Catastrophe", John);
    central.available("Catastrophe", hank);

    central.notify("Fire", "Fire in the kitchen");
    return 0;
};