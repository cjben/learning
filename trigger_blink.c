#include <aos/aos.h>
#include <hal/soc/soc.h>

#define GPIO_LED_IO1    22
#define GPIO_LED_IO2    67
#define GPIO_LED_IO3    63
#define GPIO_KEY_IO3    74

static void app_led_low_action(void *arg);
static void app_led_high_action(void *arg);

gpio_dev_t led1;
gpio_dev_t led2;
gpio_dev_t led3;
gpio_dev_t key3;

int status = 0;

static void app_led_low_action(void *arg)
{
    hal_gpio_output_low(&arg);
    aos_post_delayed_action(500, app_led_high_action, arg);
}

static void app_led_high_action(void *arg)
{
    hal_gpio_output_high(&arg);
    aos_post_delayed_action(500, app_led_low_action, arg);
}

static void gpio_isr_handler(void *arg)
{
    LOG("function calling!");
    status = 1;
}

static void my_blink_function(void *arg)
{
    if(1 == status){
        LOG("function calling!");
        aos_post_delayed_action(1200, app_led_low_action, led1.port);
        aos_post_delayed_action(1400, app_led_low_action, led2.port);
        aos_post_delayed_action(1600, app_led_low_action, led3.port);
        status = 0;
    }
    aos_post_delayed_action(1000, my_blink_function, NULL);
    
}

int application_start(int argc, char *argv[])
{
    LOG("APP start");
    /* gpio port config */
    led1.port = GPIO_LED_IO1;
    /* set as output mode */
    led1.config = OUTPUT_PUSH_PULL;
    /* configure GPIO with the given settings */
    hal_gpio_init(&led1);

    /* gpio port config */
    led2.port = GPIO_LED_IO2;
    /* set as output mode */
    led2.config = OUTPUT_PUSH_PULL;
    /* configure GPIO with the given settings */
    hal_gpio_init(&led2);

    /* gpio port config */
    led3.port = GPIO_LED_IO3;
    /* set as output mode */
    led3.config = OUTPUT_PUSH_PULL;
    /* configure GPIO with the given settings */
    hal_gpio_init(&led3);

    /* input pin config */
    key3.port = GPIO_KEY_IO3;
    /* set as interrupt mode */
    key3.config = IRQ_MODE;
    /* configure GPIO with the given settings */
    hal_gpio_init(&key3);
    LOG("key3 initialized");

    my_blink_function(NULL);
    hal_gpio_enable_irq(&key3, IRQ_TRIGGER_RISING_EDGE, gpio_isr_handler, (void *) GPIO_KEY_IO3);
    
    aos_loop_run();
    LOG("Program quit\n");
    return 0;
}
