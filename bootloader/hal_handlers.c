/*
 * hal_handlers.c
 *
 * Author: Dan Green (danngreen1@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * See http://creativecommons.org/licenses/MIT/ for more information.
 *
 * -----------------------------------------------------------------------------
 */

 #include "hal_handlers.h"

void HAL_MspInit(void)
{
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);

  HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
  HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
  HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
  HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
  HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
  HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void _Error_Handler(const char* file, uint32_t line)
{ 
	volatile char f[100];
	volatile uint32_t l;
	uint8_t i=0;

	while (file[i])
		f[i] = file[i++];
	l=line;

	while (1)
	{
		UNUSED(f);
		UNUSED(l);
	}
}
void HardFault_Handler(void)
{ 
	volatile uint8_t foobar;
	uint32_t hfsr,dfsr,afsr,bfar,mmfar,cfsr;

	volatile uint8_t pause=1;

	foobar=0;
	mmfar=SCB->MMFAR;
	bfar=SCB->BFAR;

	hfsr=SCB->HFSR;
	afsr=SCB->AFSR;
	dfsr=SCB->DFSR;
	cfsr=SCB->CFSR;

	UNUSED(hfsr);
	UNUSED(afsr);
	UNUSED(dfsr);
	UNUSED(cfsr);
	UNUSED(mmfar);
	UNUSED(bfar);
	
	if (foobar){
		return;
	} else {
		while(pause){};
	}
}
void NMI_Handler(void)
{ 
	while(1){};
}
void MemManage_Handler(void)
{ 
	while(1){};
}
void BusFault_Handler(void)
{ 
	while(1){};
}
void UsageFault_Handler(void)
{ 
	while(1){};
}
void SVC_Handler(void)
{ 
	while(1){};
}
void DebugMon_Handler(void)
{ 
	while(1){};
}
void PendSV_Handler(void)
{ 
	while(1){};
}
