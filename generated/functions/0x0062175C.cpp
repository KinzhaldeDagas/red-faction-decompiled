// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062175C ___hw_cw_sse2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Register ABI ONLY unsigned EDX logical control,EAX
// packed MXCSR controls; entryECX is phantom (overwritten before read),removed old fastcall first argument. Integer-only encoder,no SSE instruction/global access. Logical masks
// {10h,80000h,8,4,2,1} ->MXCSR {80h,100h,200h,400h,800h,1000h}. Rounding0300h shifts left5 ->6000h. Logical denormal-mode03000000h maps
// {0->0,01000000h->8040h,02000000h->0040h,03000000h->8000h}. These are literal mode constants despite IDA offset labels,not pointer dereferences. Ignore logical x87
// precision/infinity and all other bits. Rebuild from zero: ONLY hardware bitsFFC0h can be set,LOW SIX STATUS BITS ALWAYS0. Calling control87 uses this full rebuilt word,so actual
// SSE control update clears prior status bits. Preserve EBX/ESI/EDI;ECX/EDX clobbered,EDX finally masked03000000h. Canonical1024 mode combinations and two native inverse decoders
// independently checked; corrected unsigned EDX-only prototype.
unsigned int __usercall __hw_cw_sse2@<eax>(unsigned int a1@<edx>)
{
  unsigned int result; // eax
  unsigned int v2; // ecx
  void *v3; // edx

  result = 0;
  if ( (a1 & 0x10) != 0 )
    result = 128;
  if ( (a1 & 8) != 0 )
    result |= 0x200u;
  if ( (a1 & 4) != 0 )
    result |= 0x400u;
  if ( (a1 & 2) != 0 )
    result |= 0x800u;
  if ( (a1 & 1) != 0 )
    result |= 0x1000u;
  if ( (a1 & 0x80000) != 0 )
    result |= 0x100u;
  v2 = a1 & 0x300;
  if ( (a1 & 0x300) != 0 )
  {
    switch ( v2 )
    {
      case 0x100u:
        result |= 0x2000u;
        break;
      case 0x200u:
        result |= 0x4000u;
        break;
      case 0x300u:
        result |= 0x6000u;
        break;
    }
  }
  v3 = (void *)(a1 & 0x3000000);
  if ( v3 == &unk_1000000 )
  {
    result |= 0x8040u;
  }
  else if ( v3 == &unk_2000000 )
  {
    result |= 0x40u;
  }
  else if ( v3 == (void *)50331648 )
  {
    result |= 0x8000u;
  }
  return result;
}

