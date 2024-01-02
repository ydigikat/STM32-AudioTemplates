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
- (more coming soon)


# Audio Modes
Each template supports audio at 44kHz and 48kHz, 16 or 24-bit resolution, with or without an I2S master clock.

You select the audio mode as a parameter to the audio streaming init function:

```c
	audio_config_t *pConfig = audio_streaming_run(audio_buffer, I2S_44_32);
```

The full set of I2S configurations are:
```c
/*
 * From the reference table in the STM32F411 ref manual I2S section.
 *
 * This is a LUT of the various config items we support for specific audio modes.
 */
audio_config_t configs[] =
		{
				{.N = 302, .R = 2, .DIV = 53, .ODD = 1, .MCKOE = 0, .bits = 16, .type = I2S_44_16, .fsr = 44100.46875f},
				{.N = 192, .R = 5, .DIV = 12, .ODD = 1, .MCKOE = 0, .bits = 16, .type = I2S_48_16, .fsr = 48000.0f},
				{.N = 429, .R = 4, .DIV = 19, .ODD = 0, .MCKOE = 0, .bits = 32, .type = I2S_44_32, .fsr = 44099.50781f},
				{.N = 384, .R = 5, .DIV = 12, .ODD = 1, .MCKOE = 0, .bits = 32, .type = I2S_48_32, .fsr = 48000.0f},
				{.N = 271, .R = 2, .DIV = 6, .ODD = 0, .MCKOE = 1, .bits = 16, .type = I2S_44_MCKOE_16, .fsr = 44108.07422f},
				{.N = 271, .R = 2, .DIV = 6, .ODD = 0, .MCKOE = 1, .bits = 16, .type = I2S_48_MCKOE_16, .fsr = 47991.07031},
				{.N = 258, .R = 3, .DIV = 3, .ODD = 1, .MCKOE = 1, .bits = 32, .type = I2S_44_MCKOE_32, .fsr = 44108.07422f},
				{.N = 258, .R = 3, .DIV = 3, .ODD = 1, .MCKOE = 1, .bits = 32, .type = I2S_48_MCKOE_32, .fsr = 47991.07031}};

```

Note that the inaccuracy of some of the sample rates is a limitation of the PLL configuration on the STM32F4.  It is inaudible to all intents and purposes.

The ```main()``` loops forever, checking buf_state to see if it needs to do anything. The DMA will set the buf_state flag to indicate which half of the audio buffer needs to be refreshed, and your job is to do that part.

```C
if (buf_state != REFILL_DONE)
		{

			GenerateSaw(TEST_TONE / pConfig->fsr);			

			/* DMA tells us which half to refill */
			int16_t *ptr =
					buf_state == REFILL_PING ? audio_buffer : audio_buffer + AUDIO_BUF_SGL;

       /* Check the rest of the code for an example of filling 
          the buffer since this varies depending on the I2S mode */   
```


# Where Now?

For people familiar with CMake and embedded code, the structure of the projects will be self-evident and you'll probably start by changing the template to suit your needs.

I've provided some limited additional information in the docs folder for those not so experienced with CMake and/or embedded projects. 

Click on the links below to go to these.

- [Folder Structure](<./docs/01. Folder Structure>)
- [CMake Files](<./docs/02. CMake.md>)
- [The Code](<./docs/03. The Code.md>)
