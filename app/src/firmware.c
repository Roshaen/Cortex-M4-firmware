#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define LED_PORT (GPIOA)  // Port A
#define LED_PIN  (GPIO5)  // Pin 5  (1 << 5 )

static void rcc_setup(void) {
  rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]); // setting clock frequency to 84MHz
}

static void gpio_setup(void) {
  rcc_periph_clock_enable(RCC_GPIOA);
  gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
}

static void delay_cycles(uint32_t cycles) {  // delay function
  for (uint32_t i = 0; i < cycles; i++) {
    __asm__("nop");  // no operation for restricting compiler optimization
  }
}

int main(void) {
  rcc_setup();
  gpio_setup();

  while (1) {
    gpio_toggle(LED_PORT, LED_PIN);  // toggle the LED
    delay_cycles(84000000 / 4);
  }

  // Never return
  return 0;
}
