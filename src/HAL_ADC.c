#include "HAL_ADC.h"


void SetupADCPins()
{
	
}

void SetupADC()
{
	
	uint32_t ui32Value;
	//
	// Enable the ADC0 module.
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	//
	// Wait for the ADC0 module to be ready.
	//
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
	{
	}
	
	SetupADCPins();
	//
	// Enable the first sample sequencer to capture the value of channel 0 when
	// the processor trigger occurs.
	//
	ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 0,	ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
	ADCSequenceEnable(ADC0_BASE, 0);

	//
	// Trigger the sample sequence.
	//
	ADCProcessorTrigger(ADC0_BASE, 0);

	//
	// Wait until the sample sequence has completed.
	//

	while(!ADCIntStatus(ADC0_BASE, 0, false))
	{
	}
	//
	// Read the value from the ADC.
	//
	ADCSequenceDataGet(ADC0_BASE, 0, &ui32Value);

		
}

