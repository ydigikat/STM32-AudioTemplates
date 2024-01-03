# Audio Project Starter Templates

> <i>Disclaimer: This code has not been stringently tested or gone through any verification process.  It has been used in a number of my blog projects, so it can be considered 'smoke tested'.  

>You're free to use it as you see fit, but you'll have to fix any problems you find; I won't, nor do I need to be told about them, thanks but if there are problems that impact me, I'll fix them, myself, until then I don't care about them. </i>

This repository contains my starter projects for various boards I use for digital synthesiser and effects units.

The starter template only configures board support for audio; other onboard devices are left unconfigured.

Where there is an onboard Audio DAC, it will be used; otherwise, you will need to supply an external Audio DAC and connect it to the I2S peripheral (typically I2S2).

For boards without an Audio DAC, I test with a UDA1334A DAC (no master clock) and a Cirrus CS4344 (with master clock).

All the projects provide the same primary starter set of features:

- I2S configuration.
- DMA circular streaming from memory to I2S peripheral.
- Basic GPIO for onboard LED and BTN.

I prefer to use copies of code for templates rather than build libraries or links to standard shared files.  It all gets very messy otherwise.

Templates are available for the following boards:

- Generic "Blackpill" (STM32F411CEU6)
- STM32F411-Disco (STM32F411VET6)
- (more coming soon)


