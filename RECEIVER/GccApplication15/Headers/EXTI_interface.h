#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

void MEXTI_voidInitInt0(void);
void MEXTI_voidEnableInt0(void);
void MEXTI_voidDisableInt0(void);
void MEXTI_voidEnableGlobalInterrupt(void);
void MEXTI_voidSetCallBackInt0(void (*Copy_pvNotificationFunc)(void));

#endif