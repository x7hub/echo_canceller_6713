#include "c6713dsk.h"             

#define UINT    unsigned int
#define USHORT  unsigned short

#define ALPHA   0.3
//#define BUF_LEN 12000                                    

//#pragma DATA_SECTION(buf, "sdram");      
//short   buf[BUF_LEN];
//int     ix_buf=0;
                                           
float   l_dc=0.0;
float   r_dc=0.0;

// zzz
#define FIR_LEN 100
#define FIR_ALPHA 0.2
short    fir_buf[2*FIR_LEN];
float    fir_coef[FIR_LEN];
unsigned fir_ix;

// zzz
/*float fast_fir(float in, float coef[], float buf[], unsigned *index, unsigned length) {
  float    out;
  unsigned i;

  buf[*index]=in;
  buf[*index+length]=in;
  *index=*index+1;
  if (*index==length) *index=0;
  out=0.0;
  for (i=0; i<length; i=i+1) out=out+coef[i]*buf[*index+i];

  return out;
}*/

// zzz
float conv(short buf[], float h[], unsigned int* ix) {
  float sum;
  USHORT i;

  sum = 0.0f;

  for (i=0; i<FIR_LEN; i++) {
    sum += h[i] * buf[(*ix-i) % FIR_LEN];
  }
  return sum;
}

// zzz
float get_power(short buf[], unsigned length) {
  float rt;
  int j;

  rt = 0.0;
  for(j=0; j<length; j++) {
    rt += buf[j] * buf[j];
  }

  return rt;

}



//================================================================    
// wait routine with LED flash

void wait(int loop) {
  int i, j;

  for (i=1; i<=8; i=i*2) {
    for (j=0; j<loop; j=j+1) *(char *)CPLD=i; 
  }
}  

//================================================================    
// SPI (McBSP0) transmit routine

void spi_tx(USHORT adrs, USHORT data) {
  USHORT tx_stream;
  
  while ((*(UINT *)McBSP0_SPCR&0x00020000)==0);  // wait until tx ready  
  tx_stream=(adrs&0x0f)<<9;
  tx_stream=tx_stream|(data&0x01ff);
  *(USHORT *)McBSP0_DXR=tx_stream;
}
   
//================================================================   
// McBSP1 rx interrupt routine 
           
interrupt void mcbsp1_rx_intr(void) {
  UINT temp;
  short l_in, r_in, l_out, r_out;
  
  // zzz
  int j;
  float power_x;
  float delta_h[FIR_LEN];
  
  temp=*(UINT *)McBSP1_DRR;         // read A/D
  l_in=temp>>16;                    // l_in : left ch. in
  r_in=temp&0xffff;                 // r_in : right ch. in      
  l_dc=(1.0-ALPHA)*l_dc+ALPHA*l_in; // accumulate DC level
  r_dc=(1.0-ALPHA)*r_dc+ALPHA*r_in; // accumulate DC level
  l_in=l_in-l_dc;                   // eliminate DC offset
  r_in=r_in-r_dc;                   // eliminate DC offset

  // something to do here
  //l_out=buf[ix_buf];                // read ring buffer
  //buf[ix_buf]=l_in;                 // write ring buffer
  //ix_buf=(ix_buf+1)%BUF_LEN;        // update buffer pointer
  //r_out=r_in;                       // pass through 

  // zzz
  //l_out=l_in-fast_fir(l_in, fir_coef, fir_buf, &fir_ix, FIR_LEN);
  fir_buf[fir_ix]=l_in;
  l_out=l_in-conv(fir_buf, fir_coef, &fir_ix);
  r_out=l_out;
  //r_out=r_in;


  // zzz
  // update h in fir filter
  power_x=get_power(fir_buf, FIR_LEN);
  for(j=0; j<FIR_LEN; j++) {
    delta_h[j]=l_out * fir_buf[(fir_ix-j) % FIR_LEN] / power_x;
    fir_coef[j] = fir_coef[j] + FIR_ALPHA * delta_h[j];
  }

  // zzz
  // update index for FIR
  fir_ix=(fir_ix+1)%FIR_LEN;


  temp=l_out<<16;                   // l_out : left ch. out
  temp=temp|(r_out&0xffff);         // r_out : right ch. out
  *(UINT *)McBSP1_DXR=temp;         // write D/A
}                     
                                       
//================================================================    

void main(void) {          
  UINT  temp;     
  UINT  dip_sw, led;

  CSR                 =0x00000100;  // disable all interrupts
  *(UINT *)CCFG       =0;           // cache off
  *(UINT *)DEVCFG     =0;           // ECLK<--SYSCLK3, McASP disable
 
  // PLL setup 
  *(UINT *)PLLCSR     =0x00000000;  // bypass PLL
  wait(1000);                       // wait
  *(UINT *)PLLCSR     =0x00000008;  // reset PLL
  *(UINT *)PLLDIV0    =0x00008000;  // PLLREF=50MHz/1=50MHz
  *(UINT *)PLLM       =0x00000009;  // PLLOUT=50MHz*9=450MHz
  *(UINT *)OSCDIV1    =0x00000004;  // CLKOUT3=50MHz/5=10MHz
  *(UINT *)PLLDIV3    =0x00008004;  // ECLKOUT=450MHz/5=90MHz
  wait(1000);                       // wait
  *(UINT *)PLLDIV2    =0x00008003;  // SYSCLK2=450MHz/4=112.5MHz
  wait(1000);                       // wait
  *(UINT *)PLLDIV1    =0x00008001;  // SYSCLK1=450MHz/2=225MHz  
  wait(1000);                       // wait
  *(UINT *)PLLCSR     =0x00000000;  // bring PLL out of reset
  wait(1000);                       // wait
  *(UINT *)PLLCSR     =0x00000001;  // enable PLL
 
  // EMIF setting       
  *(UINT *)EMIF_GBLCTL=0x00003078;  // EMIF global control
  *(UINT *)EMIF_CECTL0=0xffffff37;  // EMIF CE0 control, 32bit SDRAM   
  *(UINT *)EMIF_CECTL1=0xffffff07;  // EMIF CE1 control, 8bit async
  *(UINT *)EMIF_CECTL2=0xffffff27;  // EMIF CE2 control, 32bit async
  *(UINT *)EMIF_CECTL3=0xffffff27;  // EMIF CE3 control, 32bit async

  // EMIF SDRAM control setting for MT48LC2M32B2-6 (Micron)
  *(UINT *)EMIF_SDTIM =0x00000578;  // SDRAM refresh period          
  *(UINT *)EMIF_SDEXT =0x000a8529;  // SDRAM extension  
  *(UINT *)EMIF_SDCTL =0x47115000;  // SDRAM control                         

  // daughter card reset  
  *(char *)(CPLD+1)   =0x08;        // daughter card reset on
  wait(10000);                      // wait
  *(char *)(CPLD+1)   =0;           // daughter card reset off

  // McBSP0 setting (CODEC control, DSP is master, SPI)
  *(UINT *)McBSP0_SPCR=0x00000000;  // reset McBSP0
  *(UINT *)McBSP0_SRGR=0x20000020;  // clock=112.5MHz/33=3.4MHz
  *(UINT *)McBSP0_PCR =0x00000a0a;  // use internal clock
  *(UINT *)McBSP0_XCR =0x00000040;  // 16bit/word
  *(UINT *)McBSP0_SPCR=0x00c01000;  // enable sample rate clock
  wait(1000);                       // wait
  *(UINT *)McBSP0_SPCR=0x00c11000;  // enable McBSP0 tx
  wait(1000);                       // wait
  
  // CODEC setting
  spi_tx( 9, 0x000);                // CODEC disable  
  spi_tx( 0, 0x017);                // enable line input (left)
  spi_tx( 1, 0x017);                // enable line input (right)
  spi_tx( 2, 0x0f7);                // enable headphone out (left)
  spi_tx( 3, 0x0f7);                // enable headphone out (right)
  spi_tx( 4, 0x015);                // mic line input (+20dB)
  //spi_tx( 4, 0x012);                // enable line input
  spi_tx( 5, 0x000);                // enable HPF, disable de-emphasis
  spi_tx( 6, 0x000);                // all power on
  spi_tx( 7, 0x043);                // CODEC is master, DSP mode
  spi_tx( 8, 0x00d);                // Fs=8kHz (USB mode, MCLK=12MHz)
  //spi_tx( 8, 0x001);                // Fs=48kHz (USB mode, MCLK=12MHz)
  spi_tx( 9, 0x001);                // CODEC enable
    
  // McBSP1 setting (CODEC data, DSP is slave)
  *(UINT *)McBSP1_SPCR=0x00000000;  // reset McBSP1
  *(UINT *)McBSP1_PCR =0x00000000;  // use external clock
  *(UINT *)McBSP1_RCR =0x000100a0;  // 32bit/word, 1bit data delay
  *(UINT *)McBSP1_XCR =0x000000a0;  // 32bit/word
  wait(1000);                       // wait
  *(UINT *)McBSP1_SPCR=0x00010001;  // enable McBSP1   
  
  temp=*(UINT *)MUXL&~(0x1f<<21);   // read interrupt multiplexer (MUXL)
  temp=temp|(0x0f<<21);             // set INTSEL8 <-- RINT1
  *(UINT *)MUXL=temp;               // update MUXL
  ICR=0x0000ffff;                   // clear all pending interrupt
 
  // clear ring buffer
  //for (temp=0; temp<BUF_LEN; temp=temp+1) buf[temp]=0;   
  
  // zzz
  // initialize FIR filter
  for (temp=0; temp<FIR_LEN; temp=temp+1) {
    fir_coef[temp]=0.0;
    fir_buf[temp]=0.0;
    fir_buf[temp+FIR_LEN]=0.0;
  }
    
  IER=0x00000102;                   // enable NMI & INT8
  CSR=CSR|1;                        // enable interrupt (global)
  
  // forever loop
  while(1) {      
    dip_sw=~(*(char *)CPLD)>>4;     // read DIP SW
    led=dip_sw;                     // control LED by DIP SW
    *(char *)CPLD=led;              // LED on/off
  }           
  
}
       
