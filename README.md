# M5Stack parking system

Wow, it can count and display some information - **How inovating!**

This repository includes all code used on the _M5Stack-part_, whilst [M242](https://github.com/FlurinBruehwiler/M242)
contains all the code used by the "backend".

## The techy stuff

As you've probably noticed, everything in this repository is coded in `C++`,
'_what a pain in th-_'...Anyway - the 'native' stuff has been programmed in
plain `C++` with some additions of the `Arduino` libraries.

> But wait. The requirement of the project was to use two separate M5Stacks.
What about the information-exchange-part? How did you solve that?

This part has been solved by an MQTT-connection to an already existing server
using knolleary's [pubsubclient](https://github.com/knolleary/pubsubclient), which
for one publishes information regarding the current `parkState` of the parking space
but also receives information published to the server by [the backend](https://github.com/FlurinBruehwiler/M242).

The JSON sent to the MQTT-server

```json
{
    "isOccupied": 0,
    "parkSpace": "left"
}
```

The JSON received by the MQTT-server

```text
0:1
```

## The system iteself

As seen above, two M5Stacks are involved in this system: One which just publishes
information regarding the current `parkingState` of its parking space, and another
one doing the exact same, whilst additionally receiving the latter JSON, evaluating
it and then showing _the amount of free parking spaces left_ and _an arrow indicating
which of the two spaces isn't taken yet_.

Information by the second M5Stack might look as follows*:

```text
Number of free parking spaces: 2    // Two not taken
Next free parking space: <-->       // Both are free
```

```text
Number of free parking spaces: 1    // One left untaken
Next free parking space: <--        // Left one still free
```

*simplified, due to StackOverflow-toxicity taking over and hating on any pictures used in .md files.

## Anleitung
1. Clone Repository
2. Open it in VS Code
3. Install the PlatformIO Extension
4. Fill in the WiFi Inforrmawtion in requestclient.cpp:10
5. Upload the Code to the M5StackCore2.
	- One should have the boolean isTopM5Stack == true and the other one false in application_state.cpp:14

## The test cases

| The case                          | Expected behaviour                    | Actual behaviour                      | OK/NOK |
|:----------------------------------|:--------------------------------------|:--------------------------------------|:------:|
| M5Stack not connected to WIFI     | In endless loop where nothing happens | In endless loop where nothing happens |   OK   |
| M5Stack not connected to MQTT     | M5Stack retries connection each 5 sec | M5Stack retries connection each 5 sec |   OK   |
| Sensor not plugged in             | M5Stack won't start                   | M5Stack won't start                   |   OK   |
| Working: L & R sensor range > 90  | 2 free spaces & displays "<-->"       | 2 free spaces & displays "<-->"       |   OK   |
| Working: L sensor range < 44      | 1 free spaces & displays "-->"        | 1 free spaces & displays "-->"        |   OK   |
| Working: R sensor range < 90      | 1 free spaces & displays "<--"        | 1 free spaces & displays "<--"        |   OK   |
| Working: L & R sensor range < 44  | 0 free spaces & displays ":("         | 0 free spaces & displays ":("         |   OK   |

