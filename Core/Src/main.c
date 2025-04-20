#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include "sensor_temperature.h"
#include "sensor_MPX.h"
#include "sensor_YF.h"
#include "sensor_Ultrasonic.h"
#include "pump.h"
#include "katup pemanas.h"
#include "heater.h"
#include "stdio.h"
#include "string.h"
#include "main.h"
#include "adc.h"

void Error_Handler(void) {

    printf("System encountered an error!\r\n");
    __disable_irq();
    while (1)
    {
        HAL_Delay(1000); // bisa ditambahkan LED blink
    }
}

// Deklarasi UART_HandleTypeDef sebagai variabel global
static UART_HandleTypeDef huart2;
I2C_HandleTypeDef hi2c1;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim2; 

extern ADC_HandleTypeDef hadc1;


char uart_buf[100];

// Deklarasi fungsi untuk menginisialisasi UART
static void UART_Init(void);
static void UART_SendString(const char* str);

// Konstanta
#define UART_BAUD_RATE 9600U
#define UART_TX_PIN GPIO_PIN_2
#define UART_PORT GPIOA
#define UART_TIMEOUT HAL_MAX_DELAY
#define BUFFER_SIZE 50U
#define DELAY_TIME 1000U 

#define HEATER_PORT    GPIOB
#define FAN_PIN        GPIO_PIN_1
#define FAN_PORT       GPIOB

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART2_UART_Init(void);
void Error_Handler(void);


 void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // Mengatur HSE (High-Speed External) sebagai sumber clock
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8; // Pembagi PLL
    RCC_OscInitStruct.PLL.PLLN = 336; // Pengali PLL
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2; // Pembagi PLL
    RCC_OscInitStruct.PLL.PLLQ = 7; // Pembagi PLL untuk USB
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        // Penanganan kesalahan
        Error_Handler();
    }

    // Mengatur clock sistem
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
        // Penanganan kesalahan
        Error_Handler();
    }
}

void MX_TIM2_Init(void)
{
    htim2.Instance = TIM2;  // Pilih timer 2
    htim2.Init.Prescaler = 0;  // Set prescaler sesuai kebutuhan
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;  // Mode penghitung naik
    htim2.Init.Period = 1000;  // Set periode
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;  // Pembagian clock
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;  // Auto-reload preload

    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler();  // Panggil error handler jika inisialisasi gagal
    }
}

int main(void) {
    // Inisialisasi HAL
    HAL_Init();
		//MX_I2C1_Init(); // Inisialisasi I2C
    //MX_TIM4_Init(); // Inisialisasi timer
    // Inisialisasi sistem clock
    SystemClock_Config();

    // Inisialisasi UART
    UART_Init();

    // Inisialisasi sensor
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    // Inisialisasi sensor
    DS18B20_Init(); // Sensor Temperatur
    MPX5700AP_Init(&hadc1); // Sensor Tekanan
    YF_S201_Init(&htim2); // Sensor Aliran
    HCSR04_Init(&htim2,GPIOB, GPIO_PIN_6, GPIOB, GPIO_PIN_7); 
		
		char buffer[BUFFER_SIZE];


    while (1)
			{
        float temp = DS18B20_ReadTemperature();
        float pressure = MPX5700AP_ReadPressure();
        float flow = YF_S201_ReadFlow();
        float distance = HCSR04_ReadDistance();

        // Kirim data via UART
        snprintf(buffer, BUFFER_SIZE, "Temp: %.2f C\r\n", temp);
        UART_SendString(buffer);

        snprintf(buffer, BUFFER_SIZE, "Pressure: %.2f kPa\r\n", pressure);
        UART_SendString(buffer);

        snprintf(buffer, BUFFER_SIZE, "Flow: %.2f L/min\r\n", flow);
        UART_SendString(buffer);

        snprintf(buffer, BUFFER_SIZE, "Level: %.2f cm\r\n", distance);
        UART_SendString(buffer);

        // ===== Logika Sistem Distilasi =====
        if (distance > 15.0) {
            // Tangki kosong
            Heater_Off();
            Valve_Close();
            Pump_Off();
            UART_SendString("Status: Tank Empty. System OFF\r\n");
        } else {
            if (temp < 80.0) {
                Heater_On();
                Valve_Close();
                UART_SendString("Heater ON, Valve Closed\r\n");
            } else if (temp >= 90.0) {
                Heater_Off();
                Valve_Open();
                UART_SendString("Heater OFF, Valve Open\r\n");
            }

            if (flow < 2.0) {
                Pump_On();
                UART_SendString("Pump ON\r\n");
            } else {
                Pump_Off();
                UART_SendString("Pump OFF\r\n");
            }
        }

        HAL_Delay(DELAY_TIME);
    }
}

static void UART_Init(void) {
    // Inisialisasi UART (misalnya USART2)
    __HAL_RCC_USART2_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Inisialisasi GPIO untuk TX
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = UART_TX_PIN; // TX pin
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(UART_PORT, &GPIO_InitStruct);

    // Inisialisasi UART
    huart2.Instance = USART2;
    huart2.Init.BaudRate = UART_BAUD_RATE;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK) {
        // Penanganan kesalahan jika inisialisasi UART gagal
        Error_Handler();
    }
}

static void UART_SendString(const char* str) {

    // Mengirim string melalui UART
HAL_UART_Transmit(&huart2, (const uint8_t*)str, strlen(str), HAL_MAX_DELAY);
			}

