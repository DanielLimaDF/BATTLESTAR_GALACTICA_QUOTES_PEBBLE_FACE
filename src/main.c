//FRAKKING TOASTER!
#include <pebble.h>
#include <math.h>

#define SETTINGS_KEY 1

Window *my_window;

//Text Layers
TextLayer *time1Text_layer;
TextLayer *time2Text_layer;
TextLayer *quotesText_layer;
TextLayer *batteryText_layer;
TextLayer *stepsText_layer;
TextLayer *weekDayText_layer;
TextLayer *dayText_layer;
TextLayer *monthText_layer;

//Rectangular text layer
TextLayer *rectSidebar1_layer;
TextLayer *rectSidebar2_layer;
TextLayer *rectSidebar3_layer;
TextLayer *rectBatteryStatus_layer;
TextLayer *rectDate1_layer;
TextLayer *rectDate2_layer;

//Bitmap Layers
static BitmapLayer *normalBatteryBitmapBackgroundLayer;
static BitmapLayer *chargingBatteryBitmapBackgroundLayer;
static BitmapLayer *feetBitmapBackgroundLayer;
static GBitmap *normalBatteryBitmapLayer;
static GBitmap *chargingBatteryBitmapLayer;
static GBitmap *feetBitmapLayer;

//Fonts
static GFont bsg_font;

//Complications booleans struct
// A structure containing settings
typedef struct ClaySettings {
  bool displayBattery;
  bool displayDate;
  bool displaySteps;
} __attribute__((__packed__)) ClaySettings;

ClaySettings settings;

//Other vars
char stepsStatus[20];
char batteryStatus[5];
float batteryBarCalculation;
int batteryStatusBarSize;
char currentQuoteText[60];
int currentQuote = 1;

//Update quotes
static void update_bsg_quotes(){
  
  switch (currentQuote){
    case 1:
      snprintf(currentQuoteText,60, "This Pebble device wish to know more about the Cylons");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_14,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_14, FONT_KEY_GOTHIC_14))));
    break;
    case 2:
      snprintf(currentQuoteText,60, "Pilots call me STARBUCK You may refer to me as GOD");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_14,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_14, FONT_KEY_GOTHIC_14))));
    break;
    case 3:
      snprintf(currentQuoteText,60, "GAIUS FRAKKIN BALTAR!");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_18,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_18, FONT_KEY_GOTHIC_18))));
    break;
    case 4:
      snprintf(currentQuoteText,60, "We’re the children of humanity");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_18,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_14, FONT_KEY_GOTHIC_18))));
    break;
    case 5:
      snprintf(currentQuoteText,60, "Sometimes, you have to roll a hard six");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_14,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_14, FONT_KEY_GOTHIC_14))));
    break;
    case 6:
      snprintf(currentQuoteText,60, "Frakkin Toasters!");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_18_BOLD,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_18_BOLD, FONT_KEY_GOTHIC_18_BOLD))));
    break;
    case 7:
      snprintf(currentQuoteText,60, "By your command!");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_18_BOLD,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_18_BOLD, FONT_KEY_GOTHIC_18_BOLD))));
    break;
    case 8:
      snprintf(currentQuoteText,60, "FTL OFFLINE!");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_18_BOLD,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_18_BOLD, FONT_KEY_GOTHIC_18_BOLD))));
    break;
    case 9:
      snprintf(currentQuoteText,60, "FRAK!");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_18_BOLD,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_18_BOLD, FONT_KEY_GOTHIC_18_BOLD))));
    break;
    case 10:
      snprintf(currentQuoteText,60, "GAIUS BALTAR?");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_18_BOLD,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_18_BOLD, FONT_KEY_GOTHIC_18_BOLD))));
    break;
    case 11:
      snprintf(currentQuoteText,60, "...as of this moment, we are at war!");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_14,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_14, FONT_KEY_GOTHIC_14))));
    break;
    case 12:
      snprintf(currentQuoteText,60, "SO SAY WE ALL!");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_18_BOLD,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_18_BOLD, FONT_KEY_GOTHIC_18_BOLD))));
    break;
    case 13:
      snprintf(currentQuoteText,60, "Action stations!");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_18_BOLD,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_18_BOLD, FONT_KEY_GOTHIC_18_BOLD))));
    break;
    case 14:
      snprintf(currentQuoteText,60, "Launch the alert vipers!");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_18_BOLD,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_18_BOLD, FONT_KEY_GOTHIC_18_BOLD))));
    break;
    case 15:
      snprintf(currentQuoteText,60, "God has a plan, Gaius.");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_18_BOLD,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_18_BOLD, FONT_KEY_GOTHIC_18_BOLD))));
    break;
    case 16:
      snprintf(currentQuoteText,60, "What the frak?");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_18_BOLD,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_18_BOLD, FONT_KEY_GOTHIC_18_BOLD))));
    break;
    case 17:
      snprintf(currentQuoteText,60, "“Nothing but the rain.” – Starbuck");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_14,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_14, FONT_KEY_GOTHIC_14))));
    break;
    case 18:
      snprintf(currentQuoteText,60, "They have a plan");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_18_BOLD,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_18_BOLD, FONT_KEY_GOTHIC_18_BOLD))));
    break;
    case 19:
      snprintf(currentQuoteText,60, "I want to see gamma rays");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_18,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_18, FONT_KEY_GOTHIC_18))));
    break;
    case 20:
      snprintf(currentQuoteText,60, "All of this has happened before...");
      text_layer_set_font(quotesText_layer, fonts_get_system_font(PBL_IF_BW_ELSE(FONT_KEY_GOTHIC_14,PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_14, FONT_KEY_GOTHIC_14))));
    break;
  }
  
  text_layer_set_text(quotesText_layer, currentQuoteText);
  
  if(currentQuote < 20){
    currentQuote++;
  }else{
    currentQuote = 1;
  }
  
}

//Steps count update

static void health_handler(HealthEventType event, void *context) {
  
  if(settings.displaySteps){
  
    HealthMetric metric = HealthMetricStepCount;
    time_t start = time_start_of_today();
    time_t end = time(NULL);
    
    int totalSteps;
    
    HealthServiceAccessibilityMask mask = health_service_metric_accessible(metric, 
    start, end);
    
    if(mask & HealthServiceAccessibilityMaskAvailable) {
      
      totalSteps = (int)health_service_sum_today(metric);
      
      snprintf(stepsStatus,20, "%d", totalSteps);
      
      text_layer_set_text(stepsText_layer, stepsStatus);
      
      //Test only
      //text_layer_set_text(stepsText_layer, "999999");
      
    }
    
    layer_set_hidden(bitmap_layer_get_layer(feetBitmapBackgroundLayer),false);
    layer_set_hidden(text_layer_get_layer(stepsText_layer),false);
    
  }else{
    
    layer_set_hidden(bitmap_layer_get_layer(feetBitmapBackgroundLayer),true);
    layer_set_hidden(text_layer_get_layer(stepsText_layer),true);
    
  }
  
  
}

//Battery update
static void updateBattery() {
  
  if(settings.displayBattery){
  
    //Battery status
    BatteryChargeState state = battery_state_service_peek();
    int statusValue = (int)state.charge_percent;
    snprintf(batteryStatus,5, "%d%%", statusValue);
    text_layer_set_text(batteryText_layer, batteryStatus);
    
    batteryBarCalculation = statusValue*19;
    batteryBarCalculation = batteryBarCalculation/100;
    
    batteryStatusBarSize = roundf(batteryBarCalculation);
    
    //Change size
    text_layer_set_size(rectBatteryStatus_layer, GSize(batteryStatusBarSize,5));
    
    if(statusValue <= 20){
      text_layer_set_background_color(rectBatteryStatus_layer, PBL_IF_COLOR_ELSE(GColorOrange,GColorLightGray));
    }else{
      text_layer_set_background_color(rectBatteryStatus_layer, PBL_IF_COLOR_ELSE(GColorYellow,GColorBlack));
    }
    
    //Check if battery is charging
    if(state.is_charging){
      //Hide normal battery icon and show charging battery bitmap
      
      layer_set_hidden(bitmap_layer_get_layer(normalBatteryBitmapBackgroundLayer),true);
      layer_set_hidden(bitmap_layer_get_layer(chargingBatteryBitmapBackgroundLayer),false);
      layer_set_hidden(text_layer_get_layer(rectBatteryStatus_layer),true);
      layer_set_hidden(text_layer_get_layer(batteryText_layer),true);
      
    }else{
      //You know...
      
      layer_set_hidden(bitmap_layer_get_layer(normalBatteryBitmapBackgroundLayer),false);
      layer_set_hidden(bitmap_layer_get_layer(chargingBatteryBitmapBackgroundLayer),true);
      layer_set_hidden(text_layer_get_layer(rectBatteryStatus_layer),false);
      layer_set_hidden(text_layer_get_layer(batteryText_layer),false);
      
    }
    
  }else{
    //hide elements
    layer_set_hidden(bitmap_layer_get_layer(normalBatteryBitmapBackgroundLayer),true);
    layer_set_hidden(bitmap_layer_get_layer(chargingBatteryBitmapBackgroundLayer),true);
    layer_set_hidden(text_layer_get_layer(rectBatteryStatus_layer),true);
    layer_set_hidden(text_layer_get_layer(batteryText_layer),true);
    
  }
  
  
}

static void battery_state_handler(BatteryChargeState charge) {
  updateBattery();
}



//Time loop
static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  
  // Write the current hours and minutes into a buffer
  static char H_buffer[8];
  static char M_buffer[8];
  
  strftime(H_buffer, sizeof(H_buffer), clock_is_24h_style() ?
                                          "%H" : "%I", tick_time);
  strftime(M_buffer, sizeof(M_buffer), clock_is_24h_style() ?
                                          "%M" : "%M", tick_time);
  
  // Display this time on the TextLayer
  text_layer_set_text(time1Text_layer, H_buffer);
  text_layer_set_text(time2Text_layer, M_buffer);
  
  
  
  if(settings.displayDate){
    
    //date
    static char day_buffer[6];
    static char month_buffer[6];
    static char weekDay_buffer[6];
    
    strftime(day_buffer, sizeof(day_buffer), "%d", tick_time);
    strftime(month_buffer, sizeof(month_buffer), "%b", tick_time);
    strftime(weekDay_buffer, sizeof(weekDay_buffer), "%a", tick_time);
    
    // Show date
    text_layer_set_text(weekDayText_layer, weekDay_buffer);
    text_layer_set_text(dayText_layer, day_buffer);
    text_layer_set_text(monthText_layer, month_buffer);
    
  }else{
    
    text_layer_set_text(weekDayText_layer, "");
    text_layer_set_text(dayText_layer, "");
    text_layer_set_text(monthText_layer, "");
    
  }
  
  //show new quote
  update_bsg_quotes();
  
  
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}
//End of time loop





//Clay settings

static void prv_default_settings() {
  settings.displayBattery = true;
  settings.displayDate = true;
  settings.displaySteps = true;
}

// Read settings from persistent storage
static void prv_load_settings() {
  // Load the default settings
  prv_default_settings();
  // Read settings from persistent storage, if they exist
  persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

// Save the settings to persistent storage
static void prv_save_settings() {
  persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
}


static void prv_inbox_received_handler(DictionaryIterator *iter, void *context) {
  
  // Read boolean preferences
  Tuple *toggleBattery = dict_find(iter, MESSAGE_KEY_showBattery);
  if(toggleBattery) {
    settings.displayBattery = toggleBattery->value->int32 == 1;
  }
  
  Tuple *toggleDate = dict_find(iter, MESSAGE_KEY_showDate);
  if(toggleDate) {
    settings.displayDate = toggleDate->value->int32 == 1;
  }
  
  Tuple *toggleSteps = dict_find(iter, MESSAGE_KEY_showSteps);
  if(toggleSteps) {
    settings.displaySteps = toggleSteps->value->int32 == 1;
  }
  
  updateBattery();
  update_time();
  
  if(!settings.displaySteps){
    layer_set_hidden(bitmap_layer_get_layer(feetBitmapBackgroundLayer),true);
    layer_set_hidden(text_layer_get_layer(stepsText_layer),true);
  }else{
    layer_set_hidden(bitmap_layer_get_layer(feetBitmapBackgroundLayer),false);
    layer_set_hidden(text_layer_get_layer(stepsText_layer),false);
  }
  
  
  
  //show or hide date bars
  if(settings.displayDate){
    layer_set_hidden(text_layer_get_layer(rectDate1_layer ),false);
    layer_set_hidden(text_layer_get_layer(rectDate2_layer ),false);
  }else{
    layer_set_hidden(text_layer_get_layer(rectDate1_layer ),true);
    layer_set_hidden(text_layer_get_layer(rectDate2_layer ),true);
  }
  
  
  // Save the new settings to persistent storage
  prv_save_settings();
  
}

void prv_init(void) {
  
  //Load default or stored settings
  prv_load_settings();
  
  // Open AppMessage connection
  app_message_register_inbox_received(prv_inbox_received_handler);
  app_message_open(128, 128);
}





void handle_init(void) {
  //Window creation
  my_window = window_create();
  window_set_background_color(my_window, PBL_IF_COLOR_ELSE(GColorOxfordBlue,GColorBlack));
  
  #if defined(PBL_COLOR)
    
    //Font
    bsg_font = fonts_load_custom_font(resource_get_handle(PBL_IF_ROUND_ELSE(RESOURCE_ID_BSG_FONT_45,RESOURCE_ID_BSG_FONT_47)));
    
    //Rectangular layers
    rectSidebar1_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(131, 108), 0, 2, PBL_IF_ROUND_ELSE(180, 168)));
    rectSidebar2_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(135, 112), 0, PBL_IF_ROUND_ELSE(45, 32), PBL_IF_ROUND_ELSE(180, 168)));
    rectSidebar3_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(0, -100), 0, 32, PBL_IF_ROUND_ELSE(180, 168)));
    rectBatteryStatus_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(144, 117), PBL_IF_ROUND_ELSE(53, 10), 19, 5));
    
    rectDate1_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(141, 119), PBL_IF_ROUND_ELSE(103, 125), 18, 1));
    rectDate2_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(141, 119), PBL_IF_ROUND_ELSE(123, 146), 18, 1));
    
    text_layer_set_background_color(rectSidebar1_layer,GColorDarkCandyAppleRed);
    text_layer_set_background_color(rectSidebar2_layer,GColorDarkCandyAppleRed);
    text_layer_set_background_color(rectSidebar3_layer,GColorDarkCandyAppleRed);
    text_layer_set_background_color(rectBatteryStatus_layer,GColorYellow);
    text_layer_set_background_color(rectDate1_layer,GColorYellow);
    text_layer_set_background_color(rectDate2_layer,GColorYellow);
    
    //Bitmap Layers
    normalBatteryBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_BAT1_ICON);
    normalBatteryBitmapBackgroundLayer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(141, 114), PBL_IF_ROUND_ELSE(50, 7), 27, 11));
    
    chargingBatteryBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_BAT2_ICON);
    chargingBatteryBitmapBackgroundLayer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(141, 114), PBL_IF_ROUND_ELSE(50, 7), 27, 11));
    
    feetBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_FEET_ICON);
    feetBitmapBackgroundLayer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(5, 116),PBL_IF_ROUND_ELSE(72, 59),24,15));
    
  #elif defined(PBL_BW)
  
    //Font
    bsg_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_BSG_FONT_47));
  
    //Rectangular layers
    rectSidebar1_layer = text_layer_create(GRect(108, 0, 2, 168));
    rectSidebar2_layer = text_layer_create(GRect(112, 0, 32, 168));
    rectSidebar3_layer = text_layer_create(GRect(-100, 0, 32, 168));
    rectBatteryStatus_layer = text_layer_create(GRect(117, 10, 19, 5));
    
    rectDate1_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(141, 119), 125, 18, 1));
    rectDate2_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(141, 119), 146, 18, 1));
    
    text_layer_set_background_color(rectSidebar1_layer,GColorWhite);
    text_layer_set_background_color(rectSidebar2_layer,GColorWhite);
    text_layer_set_background_color(rectSidebar3_layer,GColorWhite);
    text_layer_set_background_color(rectBatteryStatus_layer,GColorBlack);
    text_layer_set_background_color(rectDate1_layer,GColorBlack);
    text_layer_set_background_color(rectDate2_layer,GColorBlack);
  
    //Bitmap Layers
    normalBatteryBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_BAT1_ICON);
    normalBatteryBitmapBackgroundLayer = bitmap_layer_create(GRect(114, 7, 27, 11));
    
    chargingBatteryBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_BAT2_ICON);
    chargingBatteryBitmapBackgroundLayer = bitmap_layer_create(GRect(114, 7, 27, 11));
  
  #endif
  
  //Add rectangle Layers to window
  layer_add_child(window_get_root_layer(my_window), (Layer*) rectSidebar1_layer);
  layer_add_child(window_get_root_layer(my_window), (Layer*) rectSidebar2_layer);
  layer_add_child(window_get_root_layer(my_window), (Layer*) rectSidebar3_layer);
  layer_add_child(window_get_root_layer(my_window), (Layer*) rectBatteryStatus_layer);
  layer_add_child(window_get_root_layer(my_window), (Layer*) rectDate1_layer);
  layer_add_child(window_get_root_layer(my_window), (Layer*) rectDate2_layer);
  
  //Add bitmap layers to window
  
  #if defined(PBL_COLOR)
    
    bitmap_layer_set_bitmap(normalBatteryBitmapBackgroundLayer, normalBatteryBitmapLayer);
    bitmap_layer_set_bitmap(chargingBatteryBitmapBackgroundLayer, chargingBatteryBitmapLayer);
    bitmap_layer_set_bitmap(feetBitmapBackgroundLayer, feetBitmapLayer);
  
    bitmap_layer_set_background_color(normalBatteryBitmapBackgroundLayer,GColorClear);
    bitmap_layer_set_background_color(chargingBatteryBitmapBackgroundLayer,GColorClear);
    bitmap_layer_set_background_color(feetBitmapBackgroundLayer,GColorClear);
    
    bitmap_layer_set_compositing_mode(normalBatteryBitmapBackgroundLayer, GCompOpSet);
    bitmap_layer_set_compositing_mode(chargingBatteryBitmapBackgroundLayer, GCompOpSet);
    bitmap_layer_set_compositing_mode(feetBitmapBackgroundLayer, GCompOpSet);
    
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(normalBatteryBitmapBackgroundLayer));
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(chargingBatteryBitmapBackgroundLayer));
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(feetBitmapBackgroundLayer));
    
    
  #elif defined(PBL_BW)
    
    bitmap_layer_set_bitmap(normalBatteryBitmapBackgroundLayer, normalBatteryBitmapLayer);
    bitmap_layer_set_bitmap(chargingBatteryBitmapBackgroundLayer, chargingBatteryBitmapLayer);
  
    bitmap_layer_set_background_color(normalBatteryBitmapBackgroundLayer,GColorClear);
    bitmap_layer_set_background_color(chargingBatteryBitmapBackgroundLayer,GColorClear);
    
    bitmap_layer_set_compositing_mode(normalBatteryBitmapBackgroundLayer, GCompOpSet);
    bitmap_layer_set_compositing_mode(chargingBatteryBitmapBackgroundLayer, GCompOpSet);
  
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(normalBatteryBitmapBackgroundLayer));
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(chargingBatteryBitmapBackgroundLayer));
    
  #endif
  
  //Text Layers
  #if defined(PBL_COLOR)
    time1Text_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(32, 0), PBL_IF_ROUND_ELSE(15, 7), PBL_IF_ROUND_ELSE(99, 108), PBL_IF_ROUND_ELSE(47, 58)));
    time2Text_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(32, 0), PBL_IF_ROUND_ELSE(66, 64), PBL_IF_ROUND_ELSE(99, 108), PBL_IF_ROUND_ELSE(47, 58)));
    quotesText_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(32, 0), PBL_IF_ROUND_ELSE(120, 122), PBL_IF_ROUND_ELSE(98, 108), PBL_IF_ROUND_ELSE(80, 43)));
    batteryText_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(138, 112), PBL_IF_ROUND_ELSE(61, 18), 32, 15));
    stepsText_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(0, 112), PBL_IF_ROUND_ELSE(89, 75), 32, 19));
    
    weekDayText_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(135, 112), PBL_IF_ROUND_ELSE(81, 104), PBL_IF_ROUND_ELSE(30, 32), 22));
    dayText_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(135, 112), PBL_IF_ROUND_ELSE(101, 124), PBL_IF_ROUND_ELSE(30, 32), 22));
    monthText_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(135, 112), PBL_IF_ROUND_ELSE(120, 144), PBL_IF_ROUND_ELSE(30, 32), 22));
    
    text_layer_set_text_color(time1Text_layer, GColorYellow);
    text_layer_set_text_color(time2Text_layer, GColorYellow);
    text_layer_set_text_color(quotesText_layer, GColorYellow);
    text_layer_set_text_color(batteryText_layer, GColorYellow);
    text_layer_set_text_color(stepsText_layer, GColorYellow);
    text_layer_set_text_color(weekDayText_layer, GColorYellow);
    text_layer_set_text_color(dayText_layer, GColorYellow);
    text_layer_set_text_color(monthText_layer, GColorYellow);
  
    text_layer_set_background_color(time1Text_layer,GColorClear);
    text_layer_set_background_color(time2Text_layer,GColorClear);
    text_layer_set_background_color(quotesText_layer,GColorClear);
    text_layer_set_background_color(batteryText_layer,GColorClear);
    text_layer_set_background_color(stepsText_layer,GColorClear);
    text_layer_set_background_color(weekDayText_layer,GColorClear);
    text_layer_set_background_color(dayText_layer,GColorClear);
    text_layer_set_background_color(monthText_layer,GColorClear);
    
    text_layer_set_font(time1Text_layer, bsg_font);
    text_layer_set_font(time2Text_layer, bsg_font);
    
    text_layer_set_font(quotesText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
    text_layer_set_font(batteryText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
    text_layer_set_font(stepsText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
    text_layer_set_font(weekDayText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
    text_layer_set_font(dayText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
    text_layer_set_font(monthText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
    
    text_layer_set_text_alignment(time1Text_layer, GTextAlignmentCenter);
    text_layer_set_text_alignment(time2Text_layer, GTextAlignmentCenter);
    //text_layer_set_text_alignment(quotesText_layer, PBL_IF_ROUND_ELSE(GTextAlignmentRight, GTextAlignmentCenter));
    text_layer_set_text_alignment(quotesText_layer, GTextAlignmentCenter);
    text_layer_set_text_alignment(batteryText_layer, GTextAlignmentCenter);
    text_layer_set_text_alignment(stepsText_layer, GTextAlignmentCenter);
    text_layer_set_text_alignment(weekDayText_layer, GTextAlignmentCenter);
    text_layer_set_text_alignment(dayText_layer, GTextAlignmentCenter);
    text_layer_set_text_alignment(monthText_layer, GTextAlignmentCenter);
    
    layer_add_child(window_get_root_layer(my_window), (Layer*) time1Text_layer);
    layer_add_child(window_get_root_layer(my_window), (Layer*) time2Text_layer);
    layer_add_child(window_get_root_layer(my_window), (Layer*) quotesText_layer);
    layer_add_child(window_get_root_layer(my_window), (Layer*) batteryText_layer);
    layer_add_child(window_get_root_layer(my_window), (Layer*) stepsText_layer);
    layer_add_child(window_get_root_layer(my_window), (Layer*) weekDayText_layer);
    layer_add_child(window_get_root_layer(my_window), (Layer*) dayText_layer);
    layer_add_child(window_get_root_layer(my_window), (Layer*) monthText_layer);
    
  #elif defined(PBL_BW)
    time1Text_layer = text_layer_create(GRect(0, 7, 108, 58));
    time2Text_layer = text_layer_create(GRect(0, 64, 108, 58));
    quotesText_layer = text_layer_create(GRect(0, 122, 108, 43));
    batteryText_layer = text_layer_create(GRect(112, 18, 32, 15));
  
    weekDayText_layer = text_layer_create(GRect(112, 104, 32, 22));
    dayText_layer = text_layer_create(GRect(112, 124, 32, 22));
    monthText_layer = text_layer_create(GRect(112, 144, 32, 22));
    
    text_layer_set_text_color(time1Text_layer, GColorWhite);
    text_layer_set_text_color(time2Text_layer, GColorWhite);
    text_layer_set_text_color(quotesText_layer, GColorWhite);
    text_layer_set_text_color(batteryText_layer, GColorBlack);
    text_layer_set_text_color(weekDayText_layer, GColorBlack);
    text_layer_set_text_color(dayText_layer, GColorBlack);
    text_layer_set_text_color(monthText_layer, GColorBlack);
    
    text_layer_set_background_color(time1Text_layer,GColorClear);
    text_layer_set_background_color(time2Text_layer,GColorClear);
    text_layer_set_background_color(quotesText_layer,GColorClear);
    text_layer_set_background_color(batteryText_layer,GColorClear);
    text_layer_set_background_color(weekDayText_layer,GColorClear);
    text_layer_set_background_color(dayText_layer,GColorClear);
    text_layer_set_background_color(monthText_layer,GColorClear);
  
    text_layer_set_font(time1Text_layer, bsg_font);
    text_layer_set_font(time2Text_layer, bsg_font);
    
    text_layer_set_font(quotesText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
    text_layer_set_font(batteryText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  
    text_layer_set_font(weekDayText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
    text_layer_set_font(dayText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
    text_layer_set_font(monthText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
    
    text_layer_set_text_alignment(time1Text_layer, GTextAlignmentCenter);
    text_layer_set_text_alignment(time2Text_layer, GTextAlignmentCenter);
    text_layer_set_text_alignment(quotesText_layer, GTextAlignmentCenter);
    text_layer_set_text_alignment(batteryText_layer, GTextAlignmentCenter);
    text_layer_set_text_alignment(weekDayText_layer, GTextAlignmentCenter);
    text_layer_set_text_alignment(dayText_layer, GTextAlignmentCenter);
    text_layer_set_text_alignment(monthText_layer, GTextAlignmentCenter);
    
    layer_add_child(window_get_root_layer(my_window), (Layer*) time1Text_layer);
    layer_add_child(window_get_root_layer(my_window), (Layer*) time2Text_layer);
    layer_add_child(window_get_root_layer(my_window), (Layer*) quotesText_layer);
    layer_add_child(window_get_root_layer(my_window), (Layer*) batteryText_layer);
    layer_add_child(window_get_root_layer(my_window), (Layer*) weekDayText_layer);
    layer_add_child(window_get_root_layer(my_window), (Layer*) dayText_layer);
    layer_add_child(window_get_root_layer(my_window), (Layer*) monthText_layer);
    
  #endif
  
  
  //Time events
  update_time();
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  //Battery events
  updateBattery();
  battery_state_service_subscribe(battery_state_handler);
  
  //Steps counting elements
  #if defined(PBL_HEALTH)
    
    if(health_service_events_subscribe(health_handler, NULL)) {
      
      //Test only
      //text_layer_set_text(stepsText_layer, "9999");
  
    }
      
  #endif
  
  window_stack_push(my_window, true);
}

void handle_deinit(void) {
  
  //Deinit text Layers
  text_layer_destroy(time1Text_layer);
  text_layer_destroy(time2Text_layer);
  text_layer_destroy(quotesText_layer);
  text_layer_destroy(batteryText_layer);
  text_layer_destroy(stepsText_layer);
  text_layer_destroy(weekDayText_layer);
  text_layer_destroy(dayText_layer);
  text_layer_destroy(monthText_layer);
  
  //Deinit rectangular layers
  text_layer_destroy(rectSidebar1_layer);
  text_layer_destroy(rectSidebar2_layer);
  text_layer_destroy(rectSidebar3_layer);
  text_layer_destroy(rectBatteryStatus_layer);
  text_layer_destroy(rectDate1_layer);
  text_layer_destroy(rectDate2_layer);
  
  //Deinit Bitmaps
  gbitmap_destroy(normalBatteryBitmapLayer);
  gbitmap_destroy(chargingBatteryBitmapLayer);
  gbitmap_destroy(feetBitmapLayer);
  bitmap_layer_destroy(normalBatteryBitmapBackgroundLayer);
  bitmap_layer_destroy(chargingBatteryBitmapBackgroundLayer);
  bitmap_layer_destroy(feetBitmapBackgroundLayer);
  
  //Deinit fonts
  fonts_unload_custom_font(bsg_font);
  
  //Unsubscribe events
  battery_state_service_unsubscribe();
  tick_timer_service_unsubscribe();
  health_service_events_unsubscribe();
  
  //Deinit window
  window_destroy(my_window);
  
  //So say we all!
}

int main(void) {
  prv_init();
  handle_init();
  app_event_loop();
  handle_deinit();
}
