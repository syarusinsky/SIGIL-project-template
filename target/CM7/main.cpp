#include "../../lib/STM32h745bi-HAL/llpd/include/LLPD.hpp"
#include "OutputSurface.hpp"
#include "Smoll.h"
#include "boxTex.h"

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
#define LOGGING_USART_NUM 		USART_NUM::USART_1
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

#define LCD_BRIGHT_PORT 		GPIO_PORT::A
#define LCD_BRIGHT_PIN 			GPIO_PIN::PIN_0
#define LCD_DE_PORT 			GPIO_PORT::F
#define LCD_DE_PIN 			GPIO_PIN::PIN_10
#define LCD_CLK_PORT 			GPIO_PORT::G
#define LCD_CLK_PIN 			GPIO_PIN::PIN_7
#define LCD_VSYN_PORT 			GPIO_PORT::I
#define LCD_VSYN_PIN 			GPIO_PIN::PIN_9
#define LCD_HSYN_PORT 			GPIO_PORT::I
#define LCD_HSYN_PIN 			GPIO_PIN::PIN_10
#define LCD_R0_PORT 			GPIO_PORT::H
#define LCD_R0_PIN 			GPIO_PIN::PIN_2
#define LCD_R1_PORT 			GPIO_PORT::A
#define LCD_R1_PIN 			GPIO_PIN::PIN_2
#define LCD_R2_PORT 			GPIO_PORT::A
#define LCD_R2_PIN 			GPIO_PIN::PIN_1
#define LCD_R3_PORT 			GPIO_PORT::B
#define LCD_R3_PIN 			GPIO_PIN::PIN_0
#define LCD_R4_PORT 			GPIO_PORT::A
#define LCD_R4_PIN 			GPIO_PIN::PIN_5
#define LCD_R5_PORT 			GPIO_PORT::H
#define LCD_R5_PIN 			GPIO_PIN::PIN_11
#define LCD_R6_PORT 			GPIO_PORT::B
#define LCD_R6_PIN 			GPIO_PIN::PIN_1
#define LCD_R7_PORT 			GPIO_PORT::J
#define LCD_R7_PIN 			GPIO_PIN::PIN_6
#define LCD_G0_PORT 			GPIO_PORT::E
#define LCD_G0_PIN 			GPIO_PIN::PIN_5
#define LCD_G1_PORT 			GPIO_PORT::E
#define LCD_G1_PIN 			GPIO_PIN::PIN_6
#define LCD_G2_PORT 			GPIO_PORT::A
#define LCD_G2_PIN 			GPIO_PIN::PIN_6
#define LCD_G3_PORT 			GPIO_PORT::J
#define LCD_G3_PIN 			GPIO_PIN::PIN_10
#define LCD_G4_PORT 			GPIO_PORT::B
#define LCD_G4_PIN 			GPIO_PIN::PIN_10
#define LCD_G5_PORT 			GPIO_PORT::H
#define LCD_G5_PIN 			GPIO_PIN::PIN_4
#define LCD_G6_PORT 			GPIO_PORT::I
#define LCD_G6_PIN 			GPIO_PIN::PIN_11
#define LCD_G7_PORT 			GPIO_PORT::K
#define LCD_G7_PIN 			GPIO_PIN::PIN_2
#define LCD_B0_PORT 			GPIO_PORT::E
#define LCD_B0_PIN 			GPIO_PIN::PIN_4
#define LCD_B1_PORT 			GPIO_PORT::A
#define LCD_B1_PIN 			GPIO_PIN::PIN_10
#define LCD_B2_PORT 			GPIO_PORT::D
#define LCD_B2_PIN 			GPIO_PIN::PIN_6
#define LCD_B3_PORT 			GPIO_PORT::A
#define LCD_B3_PIN 			GPIO_PIN::PIN_8
#define LCD_B4_PORT 			GPIO_PORT::G
#define LCD_B4_PIN 			GPIO_PIN::PIN_12
#define LCD_B5_PORT 			GPIO_PORT::A
#define LCD_B5_PIN 			GPIO_PIN::PIN_3
#define LCD_B6_PORT 			GPIO_PORT::B
#define LCD_B6_PIN 			GPIO_PIN::PIN_8
#define LCD_B7_PORT 			GPIO_PORT::B
#define LCD_B7_PIN 			GPIO_PIN::PIN_9

#define FB_WIDTH 		800
#define FB_HEIGHT 		480


// these pins are unconnected on SIGIL Rev 2 development board, so we disable them as per the ST recommendations
void disableUnusedPIns()
{
	// LLPD::gpio_output_setup( GPIO_PORT::A, GPIO_PIN::PIN_1, GPIO_PUPD::PULL_DOWN, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::LOW );
}

int main(void)
{
	// setup clock 480MHz (also prescales peripheral clocks to fit rate limitations)
	LLPD::rcc_clock_start_max_cpu1();
	LLPD::rcc_start_pll2( SDRAM_FREQ * 2 );
	LLPD::rcc_start_pll3();

	// enable gpio clocks
	LLPD::gpio_enable_clock( GPIO_PORT::A );
	LLPD::gpio_enable_clock( GPIO_PORT::B );
	LLPD::gpio_enable_clock( GPIO_PORT::C );
	LLPD::gpio_enable_clock( GPIO_PORT::D );
	LLPD::gpio_enable_clock( GPIO_PORT::E );
	LLPD::gpio_enable_clock( GPIO_PORT::F );
	LLPD::gpio_enable_clock( GPIO_PORT::G );
	LLPD::gpio_enable_clock( GPIO_PORT::H );
	LLPD::gpio_enable_clock( GPIO_PORT::I );
	LLPD::gpio_enable_clock( GPIO_PORT::J );
	LLPD::gpio_enable_clock( GPIO_PORT::K );

	// turn lcd brightness off before anything
	LLPD::gpio_output_setup( LCD_BRIGHT_PORT, LCD_BRIGHT_PIN, GPIO_PUPD::PULL_UP, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH);
	LLPD::gpio_output_set( LCD_BRIGHT_PORT, LCD_BRIGHT_PIN, false );

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

	// setup lcd pins
	LLPD::gpio_output_setup( LCD_DE_PORT, LCD_DE_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_CLK_PORT, LCD_CLK_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_VSYN_PORT, LCD_VSYN_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_HSYN_PORT, LCD_HSYN_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_R0_PORT, LCD_R0_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_R1_PORT, LCD_R1_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_R2_PORT, LCD_R2_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_R3_PORT, LCD_R3_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 9 );
	LLPD::gpio_output_setup( LCD_R4_PORT, LCD_R4_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_R5_PORT, LCD_R5_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_R6_PORT, LCD_R6_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 9 );
	LLPD::gpio_output_setup( LCD_R7_PORT, LCD_R7_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_G0_PORT, LCD_G0_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_G1_PORT, LCD_G1_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_G2_PORT, LCD_G2_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_G3_PORT, LCD_G3_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_G4_PORT, LCD_G4_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_G5_PORT, LCD_G5_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 9 );
	LLPD::gpio_output_setup( LCD_G6_PORT, LCD_G6_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 9 );
	LLPD::gpio_output_setup( LCD_G7_PORT, LCD_G7_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_B0_PORT, LCD_B0_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_B1_PORT, LCD_B1_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_B2_PORT, LCD_B2_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_B3_PORT, LCD_B3_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 13 );
	LLPD::gpio_output_setup( LCD_B4_PORT, LCD_B4_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 9 );
	LLPD::gpio_output_setup( LCD_B5_PORT, LCD_B5_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_B6_PORT, LCD_B6_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );
	LLPD::gpio_output_setup( LCD_B7_PORT, LCD_B7_PIN, GPIO_PUPD::NONE, GPIO_OUTPUT_TYPE::PUSH_PULL, GPIO_OUTPUT_SPEED::VERY_HIGH, true, 14 );

	// USART setup
	// LLPD::usart_init( LOGGING_USART_NUM, USART_WORD_LENGTH::BITS_8, USART_PARITY::NONE, USART_CONF::TX_AND_RX,
	// 			USART_STOP_BITS::BITS_1, 120000000, 9600 );
	// LLPD::usart_log( LOGGING_USART_NUM, "SIGIL starting up ----------------------------" );

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

	// setup mpu for sdram region to prevent unaligned access
	// TODO in the future, test this with "cachable" and see if it makes a difference
	// disable mpu
	__DMB();
	SCB->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_Msk;
	MPU->CTRL = 0;
	// region config for sdram as non-cacheable
	MPU->RNR = 0;
	MPU->RBAR = SDRAM1_MEM_START;
	MPU->RASR = 	0 			 	<< 	MPU_RASR_XN_Pos 	|
			ARM_MPU_AP_FULL 	 	<< 	MPU_RASR_AP_Pos 	|
			1 			 	<< 	MPU_RASR_TEX_Pos 	|
			1 			 	<< 	MPU_RASR_S_Pos 		|
			1 			 	<< 	MPU_RASR_C_Pos 		| // TODO maybe setting cachable will be faster?
			1 			 	<< 	MPU_RASR_B_Pos 		|
			0 			 	<< 	MPU_RASR_SRD_Pos 	|
			ARM_MPU_REGION_SIZE_8MB 	<< 	MPU_RASR_SIZE_Pos 	|
			1 				<< 	MPU_RASR_ENABLE_Pos;
	// enable mpu
	MPU->CTRL = MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_ENABLE_Msk;
	SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
	__DSB();
	__ISB();

	// sdram setup
	LLPD::fmc_sdram_init( FMC_SDRAM_BANK::BANK_5, FMC_SDRAM_COL_ADDR_BITS::BITS_8, FMC_SDRAM_ROW_ADDR_BITS::BITS_12,
			FMC_SDRAM_DATA_ADDR_BITS::BITS_16, FMC_SDRAM_NUM_BANKS::BANKS_4, FMC_SDRAM_CLOCK_CONFIG::CYCLES_2,
			FMC_SDRAM_CAS_LATENCY::CYCLES_3, true, FMC_SDRAM_RPIPE_DELAY::CYCLES_2, false, 2, 6, 4, 5, 4, 2, 2 );
	LLPD::fmc_sdram_init( FMC_SDRAM_BANK::BANK_6, FMC_SDRAM_COL_ADDR_BITS::BITS_8, FMC_SDRAM_ROW_ADDR_BITS::BITS_12,
			FMC_SDRAM_DATA_ADDR_BITS::BITS_16, FMC_SDRAM_NUM_BANKS::BANKS_4, FMC_SDRAM_CLOCK_CONFIG::CYCLES_2,
			FMC_SDRAM_CAS_LATENCY::CYCLES_3, true, FMC_SDRAM_RPIPE_DELAY::CYCLES_2, false, 2, 6, 4, 5, 4, 2, 2 );
	LLPD::fmc_sdram_start( true, true, 2, 64, 4096, SDRAM_FREQ, (0b011 << 4) ); // | (0b1 << 9) );

	uint8_t* sram1Ptr = (uint8_t*) SDRAM1_MEM_START;
	uint8_t* sram2Ptr = (uint8_t*) SDRAM2_MEM_START;

	// zero out sdram
	for ( unsigned int byte = 0; byte < SDRAM_SIZE; byte++ )
	{
		sram1Ptr[byte] = 0;
		sram2Ptr[byte] = 0;

		if ( sram1Ptr[byte] != 0 || sram2Ptr[byte] != 0 )
		{
			while ( true )
			{
				// LLPD::usart_log( LOGGING_USART_NUM, "SDRAM zeroing failed! -------------------------------" );
			}
		}
	}

	// fill framebuffers
	OutputSurface surface;
	if ( ! surface.placeGraphicsObjectsInMemory((uint8_t*) SDRAM1_MEM_START, SDRAM_SIZE) )
	{
		while ( true )
		{
			// LLPD::usart_log( LOGGING_USART_NUM, "Failed to create graphics objects! -------------------------------" );
		}
	}
	Font font( Smoll_data );
	Texture<CP_FORMAT::RGBA_32BIT, RENDER_API::SOFTWARE> boxTex( boxTex_data );
	surface.setBoxTex( &boxTex );
	surface.setFont( &font );
	surface.render();
	surface.advanceFrameBuffer().getPixels();
	surface.render();

	// setup ltdc and double buffered framebuffer
	LLPD::ltdc_init( 48, 88, 40, FB_WIDTH, 3, 32, 13, FB_HEIGHT, LTDC_HSYNC_POL::ACTIVE_LOW, LTDC_VSYNC_POL::ACTIVE_LOW, LTDC_DE_POL::ACTIVE_LOW,
				LTDC_PCLK_POL::ACTIVE_LOW, 0, 0, 0 );
	LLPD::ltdc_layer_init( LTDC_LAYER::LAYER_1, 0, FB_WIDTH, 0, FB_HEIGHT, LTDC_PIXEL_FORMAT::RGB888, 255, 0, LTDC_BLEND_FACTOR1::CONSTANT_ALPHA,
				LTDC_BLEND_FACTOR2::ONE_MINUS_CONSTANT_ALPHA, reinterpret_cast<unsigned int>(&surface.advanceFrameBuffer().getPixels()),
				FB_WIDTH, FB_HEIGHT, 0, 0, 0 );
	LLPD::ltdc_layer_enable( LTDC_LAYER::LAYER_1 );
	LLPD::ltdc_immediate_reload();
	LLPD::gpio_output_set( LCD_BRIGHT_PORT, LCD_BRIGHT_PIN, true );

	// flush denormals
	__set_FPSCR( __get_FPSCR() | (1 << 24) );

	// enable instruction cache
	SCB_EnableICache();

	// enable data cache (will only be useful for constant values stored in flash)
	SCB_InvalidateDCache();
	SCB_EnableDCache();

	// LLPD::usart_log( LOGGING_USART_NUM, "SIGIL setup complete, entering while loop -------------------------------" );

	// TODO remove after testing
	SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk;
	SCB->CCR &= ~(SCB_CCR_UNALIGN_TRP_Msk);

	while ( true )
	{
		surface.render();
		LLPD::ltdc_layer_set_fb_addr( LTDC_LAYER::LAYER_1, reinterpret_cast<unsigned int>(&surface.advanceFrameBuffer().getPixels()) );

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

extern "C" void HardFault_Handler (void)
{
	while (1)
	{
		volatile uint32_t cfsrReg = SCB->CFSR;
		SCB->CFSR = cfsrReg;
		volatile uint32_t bfarReg = SCB->BFAR;
		SCB->BFAR = bfarReg;
		// LLPD::usart_log( LOGGING_USART_NUM, "Hard Faulting -----------------------------" );
	}
}

extern "C" void MemManage_Handler (void)
{
	while (1)
	{
		volatile uint32_t cfsrReg = SCB->CFSR;
		SCB->CFSR = cfsrReg;
		// LLPD::usart_log( LOGGING_USART_NUM, "Mem Manage Faulting -----------------------------" );
	}
}

extern "C" void BusFault_Handler (void)
{
	while (1)
	{
		volatile uint32_t cfsrReg = SCB->CFSR;
		SCB->CFSR = cfsrReg;
		// LLPD::usart_log( LOGGING_USART_NUM, "Bus Faulting -----------------------------" );
	}
}

extern "C" void UsageFault_Handler (void)
{
	while (1)
	{
		volatile uint32_t cfsrReg = SCB->CFSR;
		SCB->CFSR = cfsrReg;
		// LLPD::usart_log( LOGGING_USART_NUM, "Usage Faulting -----------------------------" );
	}
}
