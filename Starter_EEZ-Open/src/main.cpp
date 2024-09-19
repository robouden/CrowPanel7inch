#include <PCA9557.h>
#include <lvgl.h>
#include <Crowbits_DHT20.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include "ui/ui.h"
#include "ui/vars.h"
#include "ui/actions.h" 
#include "lgfx/lgfx.h"

// Setup the panel.
void setup()
{
  // Three second delay to wait for serial monitor to be running.  Not sure this is necessary going forward
  // delay(100);
  Serial.begin(115200);
  // delay(100);

  Serial.println("Running setup...");
  set_var_label_count_value("-");

  // Setup the panel
  lcd.setup();

  // Initialize the UI
  ui_init();

  // Run the LVGL timer handler once to get things started
  lv_timer_handler();
}

int clickCount = 0;

char labelValue[512];
extern const char *get_var_label_count_value()
{
  return labelValue;
}
extern void set_var_label_count_value(const char *value)
{
  Serial.println("set_var_label_count_value");
  Serial.println(value);
  strlcpy(labelValue, value, sizeof(labelValue));
}

// Handle Click event for counts and screen wakeup
void action_button_click_action(lv_event_t *e)
{
  Serial.println("action_button_click_action_count_plus");
  clickCount++;
  char ClickBuffer[20];
  snprintf(ClickBuffer, sizeof(ClickBuffer), "%d", clickCount);
  set_var_label_count_value(ClickBuffer);
  digitalWrite(2, HIGH);
}
// Handle Click event
void action_button_click_action_1(lv_event_t *e)
{
//goto screen blank 
  Serial.println("action_button_sleeping"); 
    digitalWrite(2, LOW);
}

// Handle Click event for wakeup
void action_button_click_action_2(lv_event_t *e)
{
   Serial.println("action_button_waking up"); 
    digitalWrite(2, HIGH);
}

// Handle Click event for wakeup
void action_button_click_action_3(lv_event_t *e)
{
   Serial.println("action_button_slider"); 

    digitalWrite(2, HIGH);
}



// Run Ardunio event loop
void loop()
{
  ui_tick();
  lv_timer_handler(); /* let the GUI do its work */
  delay(10);
}
