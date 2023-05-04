//==================================================
//=[ Some code in this project was taken from     ]=
//=[ https://github.com/alptbz/core2guitofexample ]=
//==================================================

#include "ui.h"
#include "setup_display.h"
#include "requestclient.h"
#include "application_state.h"

// Sensors
VL53L0X sensor;

// Common
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];
uint32_t startTime, frame = 0; // For frames-per-second estimate

void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
	Serial.println("Message arrived " + String(topic));
	auto topicS = String(topic);
	String room = topicS.substring(0, topicS.lastIndexOf("/"));
	room = room.substring(room.lastIndexOf("/") + 1);

	// Parse Payload into String
	auto *buf = (char *)malloc((sizeof(char) * (length + 1)));
	memcpy(buf, payload, length);
	buf[length] = '\0';
	auto payloadS = String(buf);
	payloadS.trim();

	Serial.println(payloadS);

	uint8_t begin;
	uint8_t end;
}

void setup()
{
	set_up_m5stack_defaults();

	Wire.begin();
	sensor.setTimeout(500);

	// Program should not continue
	// if no sensor was detected
	if (!sensor.init())
	{
		Serial.println("Failed to detect and initialize sensor!");
		while (1)
		{
		}
	}
	else
	{
		sensor.startContinuous();
	}

	//-------------------------------------------------------------------
	lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);
	lv_init();
	startTime = millis();

	//-------------------------------------------------------------------
	/*Initialize the display*/
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.hor_res = 320;
	disp_drv.ver_res = 240;
	disp_drv.flush_cb = my_disp_flush;
	disp_drv.buffer = &disp_buf;
	lv_disp_drv_register(&disp_drv);

	//-------------------------------------------------------------------
	/*Initialize the (dummy) input device driver*/
	lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = my_touchpad_read;
	lv_indev_drv_register(&indev_drv);

	//-------------------------------------------------------------------
	/*Create a Tab view object*/
	lv_obj_t *tabview;
	tabview = lv_tabview_create(lv_scr_act(), NULL);

	//-------------------------------------------------------------------
	/*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
	lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Distance");

	set_up_buttons(tab1);

	set_up_labels(tab1);

	// MQTT stuff
	setup_wifi();
  	mqtt_init(mqtt_callback);
}

void loop_for_top_sensor(long millimeter_distance)
{
	if (millimeter_distance < 44L)
	{
		set_spots_text(numOfSpotsOccupied(), true);
		switchLeftSpotOccupied();
		mqtt_publish("garagepp", "r-state: true");
	}
	else
	{
		set_spots_text(numOfSpotsOccupied(), false);
		switchLeftSpotUnOccupied();
		mqtt_publish("garagepp", "r-state: false");
	}
}

void loop_for_side_sensor(long millimeter_distance)
{

	if (millimeter_distance < 90L)
	{
		set_spots_text(numOfSpotsOccupied(), true);
		switchRightSpotOccupied();
	}
	else
	{
		set_spots_text(numOfSpotsOccupied(), false);
		switchRightSpotUnOccupied();
	}
}

void loop()
{
	lv_task_handler();

	if (nextSensorRead() < millis())
	{
		unsigned long millimeter_distance = (unsigned long)sensor.readRangeContinuousMillimeters();

		lv_label_set_text(label_distance_mm, (String(millimeter_distance, 10) + " mm").c_str());

		if (isTopM5Stack())
		{
			loop_for_top_sensor(millimeter_distance);
		}
		else
		{
			loop_for_side_sensor(millimeter_distance);
		}

		Serial.print(millimeter_distance);
		if (sensor.timeoutOccurred())
		{
			Serial.print(" TIMEOUT");
		}

		Serial.println();
		addToSensorRead(millis());
	}
	delay(5);

	mqtt_loop();
}
