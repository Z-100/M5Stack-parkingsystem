#include "ui.h"

// Labels
lv_obj_t *label_distance_mm;
lv_obj_t *label_car_detected;
lv_obj_t *label_free_spot_count;
lv_obj_t *label_free_spot_direction;

// At this point I gave up
char *free_spot_count_0 = "Number of free parking sports: 0";
char *free_spot_count_1 = "Number of free parking sports: 1";
char *free_spot_count_2 = "Number of free parking sports: 2";

char *free_spot_direction_none = "No free parking spots :(";
char *free_spot_direction_left = "Next free parking spot: <--";
char *free_spot_direction_right = "Next free parking spot: -->";
char *free_spot_direction_both = "Next free parking spot: <-->";

bool my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    TouchPoint_t pos = M5.Touch.getPressPoint();

    bool isTouched = (pos.x != -1);
    if (!isTouched)
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = pos.x;
        data->point.y = pos.y;
    }
    return false;
}

void set_up_buttons(lv_obj_t *tab1)
{
    //-------------------------------------------------------------------
    /*Add content to the tabs*/
    static lv_anim_path_t path_overshoot;
    lv_anim_path_init(&path_overshoot);
    lv_anim_path_set_cb(&path_overshoot, lv_anim_path_overshoot);

    static lv_anim_path_t path_ease_out;
    lv_anim_path_init(&path_ease_out);
    lv_anim_path_set_cb(&path_ease_out, lv_anim_path_ease_out);

    static lv_anim_path_t path_ease_in_out;
    lv_anim_path_init(&path_ease_in_out);
    lv_anim_path_set_cb(&path_ease_in_out, lv_anim_path_ease_in_out);
}

void set_up_labels(lv_obj_t *tab1)
{
    // Label 1: Distance text
    lv_obj_t *label_distance_text = lv_label_create(tab1, NULL);
    lv_label_set_text(label_distance_text, "Distance:");
    lv_label_set_align(label_distance_text, LV_LABEL_ALIGN_CENTER);
    lv_label_set_long_mode(label_distance_text, LV_LABEL_LONG_EXPAND);

    lv_obj_align(label_distance_text, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);

    // Label2: Distance in mm
    label_distance_mm = lv_label_create(tab1, NULL);
    lv_label_set_text(label_distance_mm, "...");
    lv_label_set_align(label_distance_mm, LV_LABEL_ALIGN_CENTER);
    lv_label_set_long_mode(label_distance_mm, LV_LABEL_LONG_EXPAND);

    lv_obj_align(label_distance_mm, NULL, LV_ALIGN_IN_TOP_MID, -10, 10);

    // Label 3: Car detection label
    label_car_detected = lv_label_create(tab1, NULL);
    lv_label_set_text(label_car_detected, "No car detected");
    lv_label_set_align(label_car_detected, LV_LABEL_ALIGN_CENTER);
    lv_label_set_long_mode(label_car_detected, LV_LABEL_LONG_EXPAND);

    lv_obj_align(label_car_detected, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 25);

    // Label 3: Car detection label
    label_free_spot_count = lv_label_create(tab1, NULL);
    lv_label_set_text(label_free_spot_count, free_spot_count_0);
    lv_label_set_align(label_free_spot_count, LV_LABEL_ALIGN_CENTER);
    lv_label_set_long_mode(label_free_spot_count, LV_LABEL_LONG_EXPAND);

    lv_obj_align(label_free_spot_count, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 40);

    // Label 5: Free spot direction label
    label_free_spot_direction = lv_label_create(tab1, NULL);
    lv_label_set_text(label_free_spot_direction, free_spot_direction_none);
    lv_label_set_align(label_free_spot_direction, LV_LABEL_ALIGN_CENTER);
    lv_label_set_long_mode(label_free_spot_direction, LV_LABEL_LONG_EXPAND);

    lv_obj_align(label_free_spot_direction, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 55);
}

void set_spots_text(int n_free_spots, bool free_spot_is_left)
{
    if (n_free_spots == 0)
    {
        lv_label_set_text(label_free_spot_count, free_spot_count_2);
        lv_label_set_text(label_free_spot_direction, free_spot_direction_both);
    }
    else if (n_free_spots == 1)
    {
        lv_label_set_text(label_free_spot_count, free_spot_count_1);
        lv_label_set_text(label_free_spot_direction, !free_spot_is_left ? free_spot_direction_left : free_spot_direction_right);
    }
    else if (n_free_spots == 2)
    {
        lv_label_set_text(label_free_spot_count, free_spot_count_0);
        lv_label_set_text(label_free_spot_direction, free_spot_direction_none);
    }
}
