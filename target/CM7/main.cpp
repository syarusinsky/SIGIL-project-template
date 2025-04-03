#include "../../lib/STM32h745bi-HAL/llpd/include/LLPD.hpp"

#define SYS_CLOCK_FREQUENCY = 480000000;

// global variables
// volatile bool adcSetupComplete = false; // should be set to true after adc has been initialized

// peripheral defines
// #define EFFECT_ADC_PORT 		GPIO_PORT::A
// #define EFFECT_ADC_NUM 			ADC_NUM::ADC_1_2
// #define EFFECT1_ADC_PIN 		GPIO_PIN::PIN_2
// #define EFFECT1_ADC_CHANNEL 		ADC_CHANNEL::CHAN_14
// #define EFFECT2_ADC_PIN 		GPIO_PIN::PIN_3
// #define EFFECT2_ADC_CHANNEL 		ADC_CHANNEL::CHAN_15
// #define EFFECT3_ADC_PIN 		GPIO_PIN::PIN_0
// #define EFFECT3_ADC_CHANNEL 		ADC_CHANNEL::CHAN_16
// #define EFFECT_BUTTON_PORT 		GPIO_PORT::E
// #define EFFECT1_BUTTON_PIN 		GPIO_PIN::PIN_0
// #define EFFECT2_BUTTON_PIN 		GPIO_PIN::PIN_1
// #define LOGGING_USART_NUM 		USART_NUM::USART_2

// these pins are unconnected on SIGIL Rev 2 development board, so we disable them as per the ST recommendations
void disableUnusedPIns()
{
	// LLPD::gpio_output_setup( GPIO_PORT::A, GPIO_PIN::PIN_1, GPIO_PUPD::PULL_DOWN, GPIO_OUTPUT_TYPE::PUSH_PULL,
	// 				GPIO_OUTPUT_SPEED::LOW );
}

int main(void)
{
	// setup clock 480MHz (also prescales peripheral clocks to fit rate limitations)
	LLPD::rcc_clock_start_max_cpu1();

	// enable gpio clocks
	// LLPD::gpio_enable_clock( GPIO_PORT::A );
	// LLPD::gpio_enable_clock( GPIO_PORT::B );
	// LLPD::gpio_enable_clock( GPIO_PORT::C );
	// LLPD::gpio_enable_clock( GPIO_PORT::D );
	// LLPD::gpio_enable_clock( GPIO_PORT::E );
	// LLPD::gpio_enable_clock( GPIO_PORT::F );
	// LLPD::gpio_enable_clock( GPIO_PORT::G );
	// LLPD::gpio_enable_clock( GPIO_PORT::H );

	// USART setup
	// LLPD::usart_init( LOGGING_USART_NUM, USART_WORD_LENGTH::BITS_8, USART_PARITY::NONE, USART_CONF::TX_AND_RX,
	// 			USART_STOP_BITS::BITS_1, 120000000, 9600 );
	// LLPD::usart_log( LOGGING_USART_NUM, "SIGIL starting up ----------------------------" );

	// adc setup (note this must be done after the tim6_counter_start() call since it uses the delay funtion)
	// LLPD::gpio_analog_setup( EFFECT_ADC_PORT, EFFECT1_ADC_PIN );
	// LLPD::gpio_analog_setup( EFFECT_ADC_PORT, EFFECT2_ADC_PIN );
	// LLPD::gpio_analog_setup( EFFECT_ADC_PORT, EFFECT3_ADC_PIN );
	// LLPD::gpio_analog_setup( AUDIO_IN_PORT, AUDIO1_IN_PIN );
	// LLPD::gpio_analog_setup( AUDIO_IN_PORT, AUDIO2_IN_PIN );
	// LLPD::adc_init( ADC_NUM::ADC_1_2, ADC_CYCLES_PER_SAMPLE::CPS_64p5 );
	// LLPD::adc_init( ADC_NUM::ADC_3, ADC_CYCLES_PER_SAMPLE::CPS_32p5 );
	// LLPD::adc_set_channel_order( ADC_NUM::ADC_1_2, 3, EFFECT1_ADC_CHANNEL, EFFECT2_ADC_CHANNEL, EFFECT3_ADC_CHANNEL );
	// LLPD::adc_set_channel_order( ADC_NUM::ADC_3, 2, AUDIO1_IN_ADC_CHANNEL, AUDIO2_IN_ADC_CHANNEL );
	// adcSetupComplete = true;

	// pushbutton setup
	// LLPD::gpio_digital_input_setup( EFFECT_BUTTON_PORT, EFFECT1_BUTTON_PIN, GPIO_PUPD::PULL_UP );
	// LLPD::gpio_digital_input_setup( EFFECT_BUTTON_PORT, EFFECT2_BUTTON_PIN, GPIO_PUPD::PULL_UP );

	// LLPD::usart_log( LOGGING_USART_NUM, "SIGIL setup complete, entering while loop -------------------------------" );

	// flush denormals
	__set_FPSCR( __get_FPSCR() | (1 << 24) );

	// enable instruction cache
	SCB_EnableICache();

	// enable data cache (will only be useful for constant values stored in flash)
	SCB_InvalidateDCache();
	SCB_EnableDCache();

	volatile int someValue = 0;

	while ( true )
	{
		someValue += 2;

		if ( someValue >= 60 )
		{
			someValue -=4;
		}

		// LLPD::adc_perform_conversion_sequence( EFFECT_ADC_NUM );
		// uint16_t effect1Val = LLPD::adc_get_channel_value( EFFECT_ADC_NUM, EFFECT1_ADC_CHANNEL );
		// uint16_t effect2Val = LLPD::adc_get_channel_value( EFFECT_ADC_NUM, EFFECT2_ADC_CHANNEL );
		// uint16_t effect3Val = LLPD::adc_get_channel_value( EFFECT_ADC_NUM, EFFECT3_ADC_CHANNEL );
		// LLPD::usart_log_int( LOGGING_USART_NUM, "EFFECT 1 VALUE: ", effect1Val );
		// LLPD::usart_log_int( LOGGING_USART_NUM, "EFFECT 2 VALUE: ", effect2Val );
		// LLPD::usart_log_int( LOGGING_USART_NUM, "EFFECT 3 VALUE: ", effect3Val );

		// if ( ! LLPD::gpio_input_get(EFFECT_BUTTON_PORT, EFFECT1_BUTTON_PIN) )
		// {
		// 	LLPD::usart_log( LOGGING_USART_NUM, "BUTTON 1 PRESSED" );
		// }

		// if ( ! LLPD::gpio_input_get(EFFECT_BUTTON_PORT, EFFECT2_BUTTON_PIN) )
		// {
		// 	LLPD::usart_log( LOGGING_USART_NUM, "BUTTON 2 PRESSED" );
		// }
	}
}

extern "C" void USART2_IRQHandler (void) // logging usart
{
	// loopback test code for usart recieve
	// uint16_t data = LLPD::usart_receive( LOGGING_USART_NUM );
	// LLPD::usart_transmit( LOGGING_USART_NUM, data );
}
