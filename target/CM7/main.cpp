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
#define LOGGING_USART_NUM 		USART_NUM::USART_2
#define SDRAM_CLK_PORT 			GPIO_PORT::G
#define SDRAM_CLK_PIN 			GPIO_PIN::PIN_8
#define SDRAM_NE0_PORT 			GPIO_PORT::C
#define SDRAM_NE0_PIN 			GPIO_PIN::PIN_4
#define SDRAM_CKE0_PORT 		GPIO_PORT::C
#define SDRAM_CKE0_PIN 			GPIO_PIN::PIN_5
#define SDRAM_NE1_PORT 			GPIO_PORT::H
#define SDRAM_NE1_PIN 			GPIO_PIN::PIN_6
#define SDRAM_CKE1_PORT 		GPIO_PORT::H
#define SDRAM_CKE1_PIN 			GPIO_PIN::PIN_7
#define SDRAM_CAS_PORT 			GPIO_PORT::G
#define SDRAM_CAS_PIN 			GPIO_PIN::PIN_15
#define SDRAM_RAS_PORT 			GPIO_PORT::F
#define SDRAM_RAS_PIN 			GPIO_PIN::PIN_11
#define SDRAM_WE_PORT 			GPIO_PORT::C
#define SDRAM_WE_PIN 			GPIO_PIN::PIN_0
#define SDRAM_NBL0_PORT 		GPIO_PORT::E
#define SDRAM_NBL0_PIN 			GPIO_PIN::PIN_0
#define SDRAM_NBL1_PORT 		GPIO_PORT::E
#define SDRAM_NBL1_PIN 			GPIO_PIN::PIN_1
#define SDRAM_BA0_PORT 			GPIO_PORT::G
#define SDRAM_BA0_PIN 			GPIO_PIN::PIN_4
#define SDRAM_BA1_PORT 			GPIO_PORT::G
#define SDRAM_BA1_PIN 			GPIO_PIN::PIN_5
#define SDRAM_A0_PORT 			GPIO_PORT::F
#define SDRAM_A0_PIN 			GPIO_PIN::PIN_0
#define SDRAM_A1_PORT 			GPIO_PORT::F
#define SDRAM_A1_PIN 			GPIO_PIN::PIN_1
#define SDRAM_A2_PORT 			GPIO_PORT::F
#define SDRAM_A2_PIN 			GPIO_PIN::PIN_2
#define SDRAM_A3_PORT 			GPIO_PORT::F
#define SDRAM_A3_PIN 			GPIO_PIN::PIN_3
#define SDRAM_A4_PORT 			GPIO_PORT::F
#define SDRAM_A4_PIN 			GPIO_PIN::PIN_4
#define SDRAM_A5_PORT 			GPIO_PORT::F
#define SDRAM_A5_PIN 			GPIO_PIN::PIN_5
#define SDRAM_A6_PORT 			GPIO_PORT::F
#define SDRAM_A6_PIN 			GPIO_PIN::PIN_12
#define SDRAM_A7_PORT 			GPIO_PORT::F
#define SDRAM_A7_PIN 			GPIO_PIN::PIN_13
#define SDRAM_A8_PORT 			GPIO_PORT::F
#define SDRAM_A8_PIN 			GPIO_PIN::PIN_14
#define SDRAM_A9_PORT 			GPIO_PORT::F
#define SDRAM_A9_PIN 			GPIO_PIN::PIN_15
#define SDRAM_A10_PORT 			GPIO_PORT::G
#define SDRAM_A10_PIN 			GPIO_PIN::PIN_0
#define SDRAM_A11_PORT 			GPIO_PORT::G
#define SDRAM_A11_PIN 			GPIO_PIN::PIN_1
#define SDRAM_D0_PORT 			GPIO_PORT::D
#define SDRAM_D0_PIN 			GPIO_PIN::PIN_14
#define SDRAM_D1_PORT 			GPIO_PORT::D
#define SDRAM_D1_PIN 			GPIO_PIN::PIN_15
#define SDRAM_D2_PORT 			GPIO_PORT::D
#define SDRAM_D2_PIN 			GPIO_PIN::PIN_0
#define SDRAM_D3_PORT 			GPIO_PORT::D
#define SDRAM_D3_PIN 			GPIO_PIN::PIN_1
#define SDRAM_D4_PORT 			GPIO_PORT::E
#define SDRAM_D4_PIN 			GPIO_PIN::PIN_7
#define SDRAM_D5_PORT 			GPIO_PORT::E
#define SDRAM_D5_PIN 			GPIO_PIN::PIN_8
#define SDRAM_D6_PORT 			GPIO_PORT::E
#define SDRAM_D6_PIN 			GPIO_PIN::PIN_9
#define SDRAM_D7_PORT 			GPIO_PORT::E
#define SDRAM_D7_PIN 			GPIO_PIN::PIN_10
#define SDRAM_D8_PORT 			GPIO_PORT::E
#define SDRAM_D8_PIN 			GPIO_PIN::PIN_11
#define SDRAM_D9_PORT 			GPIO_PORT::E
#define SDRAM_D9_PIN 			GPIO_PIN::PIN_12
#define SDRAM_D10_PORT 			GPIO_PORT::E
#define SDRAM_D10_PIN 			GPIO_PIN::PIN_13
#define SDRAM_D11_PORT 			GPIO_PORT::E
#define SDRAM_D11_PIN 			GPIO_PIN::PIN_14
#define SDRAM_D12_PORT 			GPIO_PORT::E
#define SDRAM_D12_PIN 			GPIO_PIN::PIN_15
#define SDRAM_D13_PORT 			GPIO_PORT::D
#define SDRAM_D13_PIN 			GPIO_PIN::PIN_8
#define SDRAM_D14_PORT 			GPIO_PORT::D
#define SDRAM_D14_PIN 			GPIO_PIN::PIN_9
#define SDRAM_D15_PORT 			GPIO_PORT::D
#define SDRAM_D15_PIN 			GPIO_PIN::PIN_10

#define SDRAM1_MEM_START 		0xC0000000
#define SDRAM2_MEM_START 		0xD0000000
#define SDRAM_SIZE 			8000000
#define SDRAM_FREQ 			75

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
	LLPD::rcc_start_pll2( SDRAM_FREQ * 2 );

	// enable gpio clocks
	// LLPD::gpio_enable_clock( GPIO_PORT::A );
	// LLPD::gpio_enable_clock( GPIO_PORT::B );
	LLPD::gpio_enable_clock( GPIO_PORT::C );
	LLPD::gpio_enable_clock( GPIO_PORT::D );
	LLPD::gpio_enable_clock( GPIO_PORT::E );
	LLPD::gpio_enable_clock( GPIO_PORT::F );
	LLPD::gpio_enable_clock( GPIO_PORT::G );
	LLPD::gpio_enable_clock( GPIO_PORT::H );

	// setup sdram pins
	LLPD::gpio_output_setup( SDRAM_CLK_PORT, SDRAM_CLK_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_NE0_PORT, SDRAM_NE0_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_CKE0_PORT, SDRAM_CKE0_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_NE1_PORT, SDRAM_NE1_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_CKE1_PORT, SDRAM_CKE1_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_CAS_PORT, SDRAM_CAS_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_RAS_PORT, SDRAM_RAS_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_WE_PORT, SDRAM_WE_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_NBL0_PORT, SDRAM_NBL0_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_NBL1_PORT, SDRAM_NBL1_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_BA0_PORT, SDRAM_BA0_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_BA1_PORT, SDRAM_BA1_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_A0_PORT, SDRAM_A0_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_A1_PORT, SDRAM_A1_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_A2_PORT, SDRAM_A2_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_A3_PORT, SDRAM_A3_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_A4_PORT, SDRAM_A4_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_A5_PORT, SDRAM_A5_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_A6_PORT, SDRAM_A6_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_A7_PORT, SDRAM_A7_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_A8_PORT, SDRAM_A8_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_A9_PORT, SDRAM_A9_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_A10_PORT, SDRAM_A10_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_A11_PORT, SDRAM_A11_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_D0_PORT, SDRAM_D0_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_D1_PORT, SDRAM_D1_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_D2_PORT, SDRAM_D2_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_D3_PORT, SDRAM_D3_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_D4_PORT, SDRAM_D4_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_D5_PORT, SDRAM_D5_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12);
	LLPD::gpio_output_setup( SDRAM_D6_PORT, SDRAM_D6_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12);
	LLPD::gpio_output_setup( SDRAM_D7_PORT, SDRAM_D7_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12);
	LLPD::gpio_output_setup( SDRAM_D8_PORT, SDRAM_D8_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12);
	LLPD::gpio_output_setup( SDRAM_D9_PORT, SDRAM_D9_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12);
	LLPD::gpio_output_setup( SDRAM_D10_PORT, SDRAM_D10_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_D11_PORT, SDRAM_D11_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_D12_PORT, SDRAM_D12_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_D13_PORT, SDRAM_D13_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_D14_PORT, SDRAM_D14_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );
	LLPD::gpio_output_setup( SDRAM_D15_PORT, SDRAM_D15_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 12 );

	// USART setup
	LLPD::usart_init( LOGGING_USART_NUM, USART_WORD_LENGTH::BITS_8, USART_PARITY::NONE, USART_CONF::TX_AND_RX,
				USART_STOP_BITS::BITS_1, 120000000, 9600 );
	LLPD::usart_log( LOGGING_USART_NUM, "SIGIL starting up ----------------------------" );

	// timer setup (for 30 kHz sampling rate at 480 MHz / 2 timer clock)
	LLPD::tim6_counter_setup( 0, 8000, 30000 );

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

	// sdram setup
	LLPD::fmc_sdram_init( FMC_SDRAM_BANK::BANK_5, FMC_SDRAM_COL_ADDR_BITS::BITS_8, FMC_SDRAM_ROW_ADDR_BITS::BITS_12,
			FMC_SDRAM_DATA_ADDR_BITS::BITS_16, FMC_SDRAM_NUM_BANKS::BANKS_4, FMC_SDRAM_CLOCK_CONFIG::CYCLES_2,
			FMC_SDRAM_CAS_LATENCY::CYCLES_3, true, FMC_SDRAM_RPIPE_DELAY::CYCLES_2, false, 2, 11, 7, 9, 4, 3, 3 );
	LLPD::fmc_sdram_init( FMC_SDRAM_BANK::BANK_6, FMC_SDRAM_COL_ADDR_BITS::BITS_8, FMC_SDRAM_ROW_ADDR_BITS::BITS_12,
			FMC_SDRAM_DATA_ADDR_BITS::BITS_16, FMC_SDRAM_NUM_BANKS::BANKS_4, FMC_SDRAM_CLOCK_CONFIG::CYCLES_2,
			FMC_SDRAM_CAS_LATENCY::CYCLES_3, true, FMC_SDRAM_RPIPE_DELAY::CYCLES_2, false, 2, 11, 7, 9, 4, 3, 3 );
	LLPD::fmc_sdram_start( true, true, 2, 64, 4096, SDRAM_FREQ * 2, 0 | (0b011 << 4) | (0b1 << 9) );

	// flush denormals
	__set_FPSCR( __get_FPSCR() | (1 << 24) );

	// enable instruction cache
	SCB_EnableICache();

	// enable data cache (will only be useful for constant values stored in flash)
	SCB_InvalidateDCache();
	SCB_EnableDCache();

	volatile uint8_t* someValue1 = (volatile uint8_t*) SDRAM1_MEM_START;
	volatile uint8_t* someValue2 = (volatile uint8_t*) SDRAM2_MEM_START;

	// zero out sram
	for ( unsigned int byte = 0; byte < SDRAM_SIZE; byte++ )
	{
		someValue1[byte] = 0;
		someValue2[byte] = 0;

		if ( someValue1[byte] != 0 || someValue2[byte] != 0 )
		{
			while ( true )
			{
				LLPD::usart_log( LOGGING_USART_NUM, "SDRAM zeroing failed! -------------------------------" );
			}
		}
	}

	LLPD::usart_log( LOGGING_USART_NUM, "SIGIL setup complete, entering while loop -------------------------------" );

	while ( true )
	{
		*someValue1 += 2;
		*someValue2 += 1;

		if ( *someValue1 >= 60 )
		{
			*someValue1 -=4;
			*someValue2 -= 1;
			LLPD::usart_log_int( LOGGING_USART_NUM, "test: ", *someValue1 );
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
