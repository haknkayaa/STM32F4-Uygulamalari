
#define bool int
#define True 1
#define False 0
#define EN1 GPIO_Pin_1 
#define EN2 GPIO_Pin_0
#define IN1 GPIO_Pin_3
#define IN2 GPIO_Pin_5
#define IN3 GPIO_Pin_2
#define IN4 GPIO_Pin_4

uint8_t duzDogruluk = 1;
extern __IO uint32_t TimmingDelay;
unsigned int i;
static int a = 0;

void GPIO_Hazirliklari(void);
void FAR(unsigned char durum);
void sag();
void sol();
void ileri();
void geri();
void stop();
void duz();
void Delay(__IO uint32_t time);

void usart_rxtx(void);
void USART_Configuration(void);
void NVIC_Configuration(void);
void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount);