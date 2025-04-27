#include "main.h"
#include "sensor_temperature.h"
#include "sensor_MPX.h"
#include "sensor_YF.h"
#include "sensor_Ultrasonic.h"
#include "pump.h"
#include "katup_pemanas.h"
#include "heater.h"
#include "stdio.h"
#include "string.h"

// Handle Global
extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;
TIM_HandleTypeDef htim2;
extern I2C_HandleTypeDef hi2c1;

// Konstanta
#define BUFFER_SIZE 100U
#define DELAY_TIME 1000U

char uart_buf[BUFFER_SIZE];

heater_t heater;

// Function Prototype
void SystemClock_Config(void);
void Error_Handler(void);
extern void MX_GPIO_Init(void);          
extern void MX_USART2_UART_Init(void);   
void MX_TIM2_Init(void);          
void MX_ADC1_Init(void);         

// Error Handler
void Error_Handler(void) {
    printf("System encountered an error!\r\n");
    __disable_irq();
    while (1) {
        HAL_Delay(500);
    }
}

/*void HardFault_Handler(void)
{
    __ASM("TST lr, #4"); 
    __ASM("ITE EQ"); 
		__ASM("CMP R0, #0");     // Compare R0 with 0 (as an example of condition setting)
    __ASM("B HardFault_HandlerC");
		__ASM("IT EQ");          // If-Then block for EQ (Equal)
		__ASM("MRSEQ r0, MSP");  // Move MSP to r0 if EQ condition is true
		__ASM("IT NE");          // If-Then block for NE (Not Equal)
		__ASM("MRSNE r0, PSP");  // Move PSP to r0 if NE condition is true

}

void HardFault_HandlerC(uint32_t *hardfault_args)
{
    volatile uint32_t stacked_r0  = ((uint32_t)hardfault_args[0]);
    volatile uint32_t stacked_r1  = ((uint32_t)hardfault_args[1]);
    volatile uint32_t stacked_r2  = ((uint32_t)hardfault_args[2]);
    volatile uint32_t stacked_r3  = ((uint32_t)hardfault_args[3]);
    volatile uint32_t stacked_r12 = ((uint32_t)hardfault_args[4]);
    volatile uint32_t stacked_lr  = ((uint32_t)hardfault_args[5]);
    volatile uint32_t stacked_pc  = ((uint32_t)hardfault_args[6]);
    volatile uint32_t stacked_psr = ((uint32_t)hardfault_args[7]);

    // Sekarang kamu bisa lihat variable 'stacked_pc' (program counter)
    // Itu alamat terakhir sebelum crash
    while (1);
}
*/

void MX_TIM2_Init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 8399;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 9999;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }

    HAL_TIM_Base_Start(&htim2);
}

// System Clock Config
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // Configure Oscillator
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    // Configure Clocks
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
        Error_Handler();
    }
}

// === MAIN PROGRAM ===
int main(void) {
    int32_t echo_time_us;
    float distance;

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_TIM2_Init();
    MX_ADC1_Init();
    // MX_I2C1_Init(); 

    // Inisialisasi Module
    Heater_Init(&heater, GPIOB, GPIO_PIN_0);
    MPX5700AP_Init(&hadc1);
    YF_S201_Init(&htim2);
    HCSR04_Init(&htim2, GPIOB, GPIO_PIN_6, GPIOB, GPIO_PIN_7);

    char buffer[BUFFER_SIZE];

    while (1) {
        HCSR04_Trigger();
        echo_time_us = Read_Echo_Time();
        distance = HCSR04_ReadDistance(echo_time_us);

        float temp = DS18B20_ReadTemperature();
        float pressure = MPX5700AP_ReadPressure();
        float flow = YF_S201_ReadFlow();

        // Kirim Data ke UART
        snprintf(buffer, BUFFER_SIZE, "Temp: %.2f C\r\n", temp);
        HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);

        snprintf(buffer, BUFFER_SIZE, "Pressure: %.2f kPa\r\n", pressure);
        HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);

        snprintf(buffer, BUFFER_SIZE, "Flow: %.2f L/min\r\n", flow);
        HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);

        snprintf(buffer, BUFFER_SIZE, "Level: %.2f cm\r\n", distance);
        HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);

        // Logika Kontrol
        if (distance > 15.0f) {
            Heater_Off(&heater);
            Valve_Close();
            Pump_Off();
            HAL_UART_Transmit(&huart2, (uint8_t*)"Status: Tank Empty. System OFF\r\n", 32, HAL_MAX_DELAY);
        } else {
            if (temp < 80.0f) {
                Heater_On(&heater);
                Valve_Close();
                HAL_UART_Transmit(&huart2, (uint8_t*)"Heater ON, Valve Closed\r\n", 25, HAL_MAX_DELAY);
            } else if (temp >= 90.0f) {
                Heater_Off(&heater);
                Valve_Open();
                HAL_UART_Transmit(&huart2, (uint8_t*)"Heater OFF, Valve Open\r\n", 24, HAL_MAX_DELAY);
            }

            if (flow < 2.0f) {
                Pump_On();
                HAL_UART_Transmit(&huart2, (uint8_t*)"Pump ON\r\n", 9, HAL_MAX_DELAY);
            } else {
                Pump_Off();
                HAL_UART_Transmit(&huart2, (uint8_t*)"Pump OFF\r\n", 10, HAL_MAX_DELAY);
            }
        }

        HAL_Delay(DELAY_TIME);
    }
	}
