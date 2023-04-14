#include <mosquitto.h>

void on_connect(struct mosquitto *mosq, void *userdata, int result) {
	if (result == 0) {
		printf("MQTT connected\n");
	}
	else {
		fprintf(stderr, "MQTT connection failed: %s\n", mosquitto_connack_string(result));
	}
}

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
	if (message->payloadlen) {
		printf("%s %s\n", message->topic, (char *)message->payload);
	}
}

void publish_park_states(const char* address, int port, const char* topic, bool isOccupied, int parkSpace) {
	struct mosquitto *mosq = nullptr;
	int rc = 0;

	mosquitto_lib_init();

	mosq = mosquitto_new(nullptr, true, nullptr);
	if (!mosq) {
		fprintf(stderr, "Error: Out of memory.\n");
		mosquitto_lib_cleanup();
		return;
	}

	mosquitto_connect_callback_set(mosq, on_connect);
	mosquitto_message_callback_set(mosq, on_message);

	rc = mosquitto_connect(mosq, address, port, 60);
	if (rc != MOSQ_ERR_SUCCESS) {
		fprintf(stderr, "MQTT connection error: %s\n", mosquitto_strerror(rc));
		mosquitto_destroy(mosq);
		mosquitto_lib_cleanup();
		return;
	}

	char payload[50];
	snprintf(payload, sizeof(payload), "{\"isOccupied\":%s,\"parkSpace\":%d}", isOccupied ? "true" : "false", parkSpace);

	rc = mosquitto_publish(mosq, nullptr, topic, strlen(payload), payload, 0, false);
	if (rc != MOSQ_ERR_SUCCESS) {
		fprintf(stderr, "MQTT publish error: %s\n", mosquitto_strerror(rc));
	}

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
}

void subscribe_park_states(const char* address, int port, const char* topic) {
	struct mosquitto *mosq = nullptr;
	int rc = 0;

	mosquitto_lib_init();

	mosq = mosquitto_new(nullptr, true, nullptr);
	if (!mosq) {
		fprintf(stderr, "Error: Out of memory.\n");
		mosquitto_lib_cleanup();
		return;
	}

	mosquitto_connect_callback_set(mosq, on_connect);
	mosquitto_message_callback_set(mosq, on_message);

	rc = mosquitto_connect(mosq, address, port, 60);
	if (rc != MOSQ_ERR_SUCCESS) {
		fprintf(stderr, "MQTT connection error: %s\n", mosquitto_strerror(rc));
		mosquitto_destroy(mosq);
		mosquitto_lib_cleanup();
		return;
	}

	rc = mosquitto_subscribe(mosq, nullptr, topic, 0);
	if (rc != MOSQ_ERR_SUCCESS) {
		fprintf(stderr, "MQTT subscribe error: %s\n", mosquitto_strerror(rc));
		mosquitto_disconnect(mosq);
		mosquitto_destroy(mosq);
		mosquitto_lib_cleanup();
		return;
	}

	mosquitto_loop_forever(mosq, -1, 1);

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
}