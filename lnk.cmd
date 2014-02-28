MEMORY
{
    vecs:       o=00000000h   l=00000200h
    IRAM:       o=00000200h   l=0002FE00h    
    CE0:        o=80000000h   l=00800000h 
}

SECTIONS
{
    "vectors"   >       vecs
    .cinit      >       IRAM
    .text       >       IRAM
    .stack      >       IRAM
    .bss        >       IRAM
    .const      >       IRAM
    .data       >       IRAM
    .far        >       IRAM
    .switch     >       IRAM
    .sysmem     >       IRAM
    .tables     >       IRAM
    .cio        >       IRAM
    .sdram      >       CE0
}                             

 
