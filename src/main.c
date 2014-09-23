#include <pebble.h>

Window *my_window = NULL;

char time_string[] = "00:00";
TextLayer *time_text_layer = NULL;
enum appKeys {
    status_key,
    image_key
};
time_t current_time;
char date_string[64];
TextLayer *date_text_layer = NULL;
BitmapLayer *bitmap_layer = NULL;
GBitmap *gbitmap_ptr = NULL;

//automatically detected
int max_images = 0; 
//images start at resource = 1
int image_index = 1; 

//fuction which loads images given a resouce id
void load_image_resource(uint32_t resource_id){
        if (gbitmap_ptr) {
        gbitmap_destroy(gbitmap_ptr);
        gbitmap_ptr = NULL;
    }
    gbitmap_ptr = gbitmap_create_with_resource(resource_id);
    image_index = resource_id;
    layer_mark_dirty(bitmap_layer_get_layer(bitmap_layer));
}

//fuction which determine taps/flicks from accelerometer
void tap_handler(AccelAxisType axis, int32_t direction){
    image_index = (image_index >= max_images) ? 1 : (image_index + 1);
    load_image_resource(image_index);
}

//fuction which determine taps/flicks from system clock
void tick_handler(struct tm *tick_time, TimeUnits units_changed){
    if (units_changed & HOUR_UNIT) {
        // Before 8am
        if (tick_time->tm_hour < 20 ) {
            load_image_resource(RESOURCE_ID_IMAGE_PANDA_HAPPY);
        }
    //hes tired so lets make him sad
        else { 
            load_image_resource(RESOURCE_ID_IMAGE_PANDA_SAD);
        }
        //sample code for special case tuesday @ 8
        if (tick_time->tm_wday == 2 && tick_time->tm_hour == 8) {
            // Do soemthing
        }
        //Special case friday @ 5pm 
        if (tick_time->tm_wday == 5 && tick_time->tm_hour == 17) {
             // Do something
        }
        layer_mark_dirty(bitmap_layer_get_layer(bitmap_layer));
    }
    
     //Display time
    if (units_changed & DAY_UNIT) {
         current_time = time(NULL);
        strftime(date_string, sizeof(date_string), "%a, %b %d", localtime(&current_time));
        layer_mark_dirty(text_layer_get_layer(date_text_layer));
    }
    clock_copy_time_string(time_string,sizeof(time_string));
    layer_mark_dirty(text_layer_get_layer(time_text_layer));
}

//windows loading function
static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);
    bitmap_layer = bitmap_layer_create(bounds);
    load_image_resource(RESOURCE_ID_IMAGE_PANDA_SAD);
    bitmap_layer_set_bitmap(bitmap_layer, gbitmap_ptr);

    //Add background first
    layer_add_child(window_layer, bitmap_layer_get_layer(bitmap_layer));

    //Setup the time display
    time_text_layer = text_layer_create(GRect(34, 0, 88, 30));
    text_layer_set_text(time_text_layer, time_string);
	text_layer_set_font(time_text_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
    text_layer_set_text_alignment(time_text_layer, GTextAlignmentCenter);
    clock_copy_time_string(time_string,sizeof(time_string));
  
    //Add clock text second
    layer_add_child(window_layer, text_layer_get_layer(time_text_layer));

    //Setup the date display
    current_time = time(NULL);
    strftime(date_string, sizeof(date_string), "%a, %b %d", localtime(&current_time));
    date_text_layer = text_layer_create(GRect(4, 140, 88, 18));
    text_layer_set_text(date_text_layer, date_string);
    text_layer_set_font(date_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
 
    layer_add_child(window_layer, text_layer_get_layer(date_text_layer));
  
    //Setup hour and minute handlers
    tick_timer_service_subscribe((MINUTE_UNIT | HOUR_UNIT | DAY_UNIT), tick_handler);
  
    //Setup tap service
    accel_tap_service_subscribe(tap_handler);
}

static void window_unload(Window *window) {
}


void handle_init(void) {
  //Discover how many images from base index
    while (resource_get_handle(max_images + 1)) {
        max_images++;
    }  
    my_window = window_create();
    window_set_fullscreen(my_window, true);
    window_set_window_handlers(my_window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload,
    });
    window_stack_push(my_window, false/*animated*/);
}

void handle_deinit(void) {
    bitmap_layer_destroy(bitmap_layer);
    text_layer_destroy(time_text_layer);
    window_destroy(my_window);
}

static void in_received_handler(DictionaryIterator *iter, void *context) {
    Tuple *tuple = dict_read_first(iter);
    //while data transmission exists
    while (tuple) {
        //check jey for tuple
        switch (tuple->key) {
            case image_key:
            //APP_LOG(APP_LOG_LEVEL_DEBUG, "received png_data:%d bytes", tuple->length);
            if (tuple->value->data ==0){
                load_image_resource(RESOURCE_ID_IMAGE_PANDA_SAD);
            }
            else if (tuple->value->data[0] ==1)
            {
                load_image_resource(RESOURCE_ID_IMAGE_PANDA_HAPPY);
            }
            break;
            //case  status_key:
	        //if (tuple->value->data ==0) {
                //do something
            //}
            //else if (tuple->value->data[0] ==1){
	            //do something else
            //}
	        //break;
            default:
            break;
        }
        tuple = dict_read_next(iter);
    }
}


static void app_message_init(void) {
    //Register message handlers
    app_message_register_inbox_received(in_received_handler);
    //app_message_register_inbox_dropped(in_dropped_handler);
    //app_message_register_outbox_sent(out_sent_handler);
    //app_message_register_outbox_failed(out_failed_handler);

    // Init AppMessage buffers (larger than MAX_CHUNKSIZE for chunk tuple overhead)
    AppMessageResult msgResult = app_message_open(app_message_inbox_size_maximum(), 96);
}


int main(void) {
      app_message_init();
      handle_init();
	  app_event_loop();
	  handle_deinit();
}