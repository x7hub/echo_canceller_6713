// CPLD on C6713 DSK
#define CPLD            0x90080000  // CPLD base address

// control registers
extern cregister volatile unsigned int AMR;
extern cregister volatile unsigned int CSR;
extern cregister volatile unsigned int IFR;
extern cregister volatile unsigned int ISR;
extern cregister volatile unsigned int ICR;
extern cregister volatile unsigned int IER;
extern cregister volatile unsigned int ISTP;
extern cregister volatile unsigned int IRP;
extern cregister volatile unsigned int NRP;
extern cregister volatile unsigned int FADCR;
extern cregister volatile unsigned int FAUCR;
extern cregister volatile unsigned int FMCR;

// cache control register
#define CCFG            0x01840000  // cache configuration reg.

// device configuration register
#define DEVCFG          0x019C0200  // device configuration reg.

// EMIF registers  
#define EMIF_GBLCTL     0x01800000  // EMIF global control        
#define EMIF_CECTL0     0x01800008  // EMIF CE0 control
#define EMIF_CECTL1     0x01800004  // EMIF CE1 control             
#define EMIF_CECTL2     0x01800010  // EMIF CE2 control     
#define EMIF_CECTL3     0x01800014  // EMIF CE3 control      
#define EMIF_SDCTL      0x01800018  // EMIF SDRAM control         
#define EMIF_SDTIM      0x0180001c  // EMIF SDRM refresh period   
#define EMIF_SDEXT      0x01800020  // EMIF SDRAM extension       
 
// McBSP0 registers  
#define McBSP0_DRR      0x018c0000  // data receive reg.          
#define McBSP0_DXR      0x018c0004  // data transmit reg.         
#define McBSP0_SPCR     0x018c0008  // serial port contl. reg.    
#define McBSP0_RCR      0x018c000C  // receive control reg.       
#define McBSP0_XCR      0x018c0010  // transmit control reg.      
#define McBSP0_SRGR     0x018c0014  // sample rate generator      
#define McBSP0_MCR      0x018c0018  // multichannel reg.          
#define McBSP0_RCER     0x018c001C  // receive channel enable.    
#define McBSP0_XCER     0x018c0020  // transmit channel enable.   
#define McBSP0_PCR      0x018c0024  // pin control reg.           
#define McBSP0_DATA     0x30000000  // another data reg.

// McBSP1 registers  
#define McBSP1_DRR      0x01900000  // data receive reg.          
#define McBSP1_DXR      0x01900004  // data transmit reg.         
#define McBSP1_SPCR     0x01900008  // serial port contl. reg.    
#define McBSP1_RCR      0x0190000C  // receive control reg.       
#define McBSP1_XCR      0x01900010  // transmit control reg.      
#define McBSP1_SRGR     0x01900014  // sample rate generator      
#define McBSP1_MCR      0x01900018  // multichannel reg.          
#define McBSP1_RCER     0x0190001C  // receive channel enable.    
#define McBSP1_XCER     0x01900020  // transmit channel enable.   
#define McBSP1_PCR      0x01900024  // pin control reg.   
#define McBSP1_DATA     0x34000000  // another data reg.        

// interrupt registers  
#define MUXH            0x019c0000  // Interrupt multiplexer High 
#define MUXL            0x019c0004  // Interrupt multiplexer Low  
#define EXTPOL          0x019c0008  // Interrupt polarity reg.    

// timer0 registers  
#define TIMER0_CTRL     0x01940000  // timer0 control reg.        
#define TIMER0_PRD      0x01940004  // timer0 period reg.         
#define TIMER0_COUNT    0x01940008  // timer0 counter reg.        

// timer1 registers  
#define TIMER1_CTRL     0x01980000  // timer1 control reg.        
#define TIMER1_PRD      0x01980004  // timer1 period reg.         
#define TIMER1_COUNT    0x01980008  // timer1 counter reg.  

// PLL controller registers
#define PLLCSR          0x01B7C100  // PLL control/status reg.
#define PLLM            0x01B7C110  // PLL multiplier control reg.
#define PLLDIV0         0x01B7C114  // PLL divider 0 reg.
#define PLLDIV1         0x01B7C118  // PLL divider 1 reg.

#define PLLDIV2         0x01B7C11C  // PLL divider 2 reg.
#define PLLDIV3         0x01B7C120  // PLL divider 3 reg.
#define OSCDIV1         0x01B7C124  // oscillator divider 1 reg.      

// EDMA Registers 
#define ESEL0           0x01A0FF00  // ESEL0
#define ESEL1           0x01A0FF04  // ESEL1
#define ESEL3           0x01A0FF0C  // ESEL3
#define PQSR            0x01A0FFE0  // priority queue status reg.
#define CIPR            0x01A0FFE4  // channel interrupt pending reg.
#define CIER            0x01A0FFE8  // channel interrupt enable reg.
#define CCER            0x01A0FFEC  // channel chain enable reg. 
#define ER              0x01A0FFF0  // event reg.
#define EER             0x01A0FFF4  // event enable reg.
#define ECR             0x01A0FFF8  // event clear reg. 
#define ESR             0x01A0FFFC  // event set reg.   

// EDMA channel parameter RAM area
#define EVENT0          0x01A00000  // event  0 options parameter
#define EVENT1          0x01A00018  // event  1 options parameter
#define EVENT2          0x01A00030  // event  2 options parameter
#define EVENT3          0x01A00048  // event  3 options parameter
#define EVENT4          0x01A00060  // event  4 options parameter
#define EVENT5          0x01A00078  // event  5 options parameter
#define EVENT6          0x01A00090  // event  6 options parameter
#define EVENT7          0x01A000A8  // event  7 options parameter
#define EVENT8          0x01A000C0  // event  8 options parameter
#define EVENT9          0x01A000D8  // event  9 options parameter
#define EVENT10         0x01A000F0  // event 10 options parameter
#define EVENT11         0x01A00108  // event 11 options parameter
#define EVENT12         0x01A00120  // event 12 options parameter
#define EVENT13         0x01A00138  // event 13 options parameter
#define EVENT14         0x01A00150  // event 14 options parameter
#define EVENT15         0x01A00168  // event 15 options parameter
#define LINK0           0x01A00180  // reload/link parameter
#define LINK1           0x01A00198  // reload/link parameter
#define LINK2           0x01A001B0  // reload/link parameter
#define LINK3           0x01A001C8  // reload/link parameter

// EDMA channel parameter offset
#define OPT              0          // option parameter
#define SRC              4          // source address
#define CNT              8          // transfer count
#define DST             12          // destination address
#define IDX             16          // index
#define RLD             20          // count reload/link address 
