    .ref    _c_int00    
    .ref    _mcbsp1_rx_intr         
    .sect   "vectors"
    
RESET:
    b   _c_int00
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

NMI:    
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

RESV1:
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

RESV2:
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

INT4:   
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

INT5:   
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
                   
INT6:   
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

INT7:   
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

INT8:   
    b _mcbsp1_rx_intr
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

INT9:   
    NOP                                       
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

INT10:  
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

INT11:  
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

INT12:  
    NOP    
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

INT13:  
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

INT14:  
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

INT15:  
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
 

