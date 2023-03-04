// ///////////////////// //
// Red Panda + Harness //
// ///////////////////// //

void red_set_led(uint8_t color, bool enabled) {
  switch (color) {
    case LED_RED:
      set_gpio_output(GPIOD, 11, !enabled);
      break;
     case LED_GREEN:
      set_gpio_output(GPIOD, 10, !enabled);
      break;
    case LED_BLUE:
      set_gpio_output(GPIOD, 9, !enabled);
      break;
    default:
      break;
  }
}

void red_set_can_mode(uint8_t mode) {
  switch (mode) {
    case CAN_MODE_NORMAL:
    case CAN_MODE_OBD_CAN2:
      if ((bool)(mode == CAN_MODE_NORMAL) != (bool)(car_harness_status == HARNESS_STATUS_FLIPPED)) {
        // B12,B13: disable normal mode
        set_gpio_pullup(GPIOB, 12, PULL_NONE);
        set_gpio_mode(GPIOB, 12, MODE_ANALOG);

        set_gpio_pullup(GPIOB, 13, PULL_NONE);
        set_gpio_mode(GPIOB, 13, MODE_ANALOG);

        // B5,B6: FDCAN2 mode
        set_gpio_pullup(GPIOB, 5, PULL_NONE);
        set_gpio_alternate(GPIOB, 5, GPIO_AF9_FDCAN2);

        set_gpio_pullup(GPIOB, 6, PULL_NONE);
        set_gpio_alternate(GPIOB, 6, GPIO_AF9_FDCAN2);
      } else {
        // B5,B6: disable normal mode
        set_gpio_pullup(GPIOB, 5, PULL_NONE);
        set_gpio_mode(GPIOB, 5, MODE_ANALOG);

        set_gpio_pullup(GPIOB, 6, PULL_NONE);
        set_gpio_mode(GPIOB, 6, MODE_ANALOG);
        // B12,B13: FDCAN2 mode
        set_gpio_pullup(GPIOB, 12, PULL_NONE);
        set_gpio_alternate(GPIOB, 12, GPIO_AF9_FDCAN2);

        set_gpio_pullup(GPIOB, 13, PULL_NONE);
        set_gpio_alternate(GPIOB, 13, GPIO_AF9_FDCAN2);
      }
      break;
    default:
      break;
  }
}

bool red_check_ignition(void) {
  // ignition is checked through harness
  return harness_check_ignition();
}

void red_init(void) {
  common_init_gpio();

  // Initialize RTC
  rtc_init();

  // Disable LEDs
  red_set_led(LED_RED, false);
  red_set_led(LED_GREEN, false);
  red_set_led(LED_BLUE, false);

  // Set normal CAN mode
  red_set_can_mode(CAN_MODE_NORMAL);

}

const harness_configuration red_harness_config = {
  .has_harness = true,
  .GPIO_SBU1 = GPIOC,
  .GPIO_SBU2 = GPIOA,
  .GPIO_relay_SBU1 = GPIOC,
  .GPIO_relay_SBU2 = GPIOC,
  .pin_SBU1 = 4,
  .pin_SBU2 = 1,
  .pin_relay_SBU1 = 10,
  .pin_relay_SBU2 = 11,
  .adc_channel_SBU1 = 4, //ADC12_INP4
  .adc_channel_SBU2 = 17 //ADC1_INP17
};

const board board_red = {
  .board_type = "Red",
  .board_tick = unused_board_tick,
  .harness_config = &red_harness_config,
  .has_gps = false,
  .has_hw_gmlan = false,
  .has_obd = true,
  .has_lin = false,
  .has_spi = false,
  .has_canfd = true,
  .has_rtc_battery = false,
  .fan_max_rpm = 0U,
  .init = red_init,
  .enable_can_transceiver = false,
  .enable_can_transceivers = false,
  .set_led = red_set_led,
  .set_gps_mode = unused_set_gps_mode,
  .set_can_mode = red_set_can_mode,
  .check_ignition = red_check_ignition,
  .read_current = unused_read_current,
  .set_fan_enabled = unused_set_fan_enabled,
  .set_ir_power = unused_set_ir_power,
  .set_phone_power = unused_set_phone_power,
  .set_siren = unused_set_siren,
  .read_som_gpio = unused_read_som_gpio
};
