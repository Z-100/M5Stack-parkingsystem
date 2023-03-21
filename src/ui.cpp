#include "ui.h"

// Labels
lv_obj_t *label_distance_mm;
lv_obj_t *label_car_detected;

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
    // Return `false` because we are not buffering and no more data to read
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

    //-------------------------------------------------------------------
    /*Gum-like button*/
    static lv_style_t style_gum;
    lv_style_init(&style_gum);
    lv_style_set_transform_width(&style_gum, LV_STATE_PRESSED, 10);
    lv_style_set_transform_height(&style_gum, LV_STATE_PRESSED, -10);
    lv_style_set_value_letter_space(&style_gum, LV_STATE_PRESSED, 5);
    lv_style_set_transition_path(&style_gum, LV_STATE_DEFAULT, &path_overshoot);
    lv_style_set_transition_path(&style_gum, LV_STATE_PRESSED, &path_ease_in_out);
    lv_style_set_transition_time(&style_gum, LV_STATE_DEFAULT, 250);
    lv_style_set_transition_delay(&style_gum, LV_STATE_DEFAULT, 100);
    lv_style_set_transition_prop_1(&style_gum, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
    lv_style_set_transition_prop_2(&style_gum, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);
    lv_style_set_transition_prop_3(&style_gum, LV_STATE_DEFAULT, LV_STYLE_VALUE_LETTER_SPACE);

    lv_obj_t *btn1 = lv_btn_create(tab1, NULL);
    lv_obj_align(btn1, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -15, -15);
    lv_obj_add_style(btn1, LV_BTN_PART_MAIN, &style_gum);

    //-------------------------------------------------------------------
    /*Instead of creating a label add a values string*/
    lv_obj_set_style_local_value_str(btn1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, "Gum");
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
}