// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DCC0 __trandisp1
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal unary x87 dispatcher. Inputs EDX
// descriptor, EBP caller-prepared scratch frame, ST0 extended operand and incoming ECX bit10; no ordinary stack arguments/own frame/epilogue. Descriptor byte+14==5 selects
// workingCW=(savedWORD[EBP-0xA4]&0xFC00)|0x023F, otherwise0x133F; store at frame-0xA2 and FLDCW. FXAM classifies live ST0, waiting FSTSW writes frame-0xA0, descriptor pointer saved
// frame-0x94, byte frame-0x90 cleared. Native SHL/SAR/ROL of status highBYTE forms low-nibble index=(C3<<0)|(C0<<1)|(C1<<2)|(C2<<3). XLAT uses16 original bytes at0x6650AC:
// 08,04,08,08,08,04,08,08,00,04,0C,08,00,04,0C,08. Sign-extend table byte and TAIL JMP through DWORD[descriptor+16+offset]. ECX becomes incoming bit10 plus FXAM C1 in bit2
// (AND0x404); EBX holds selected pointer-slot address. FP status is GENERATED here, not an incoming fpstat argument. No own EAX integer return; selected target returns to
// dispatcher's caller and leaves FP result in ST0. Does not pop input/restore CW/validate descriptor or stack capacity; caller and selected target own remaining protocol.
long double __usercall _trandisp1@<st0>(void *a1@<edx>, unsigned int a2@<ecx>, void *a3@<ebp>, long double _ST7@<st0>)
{
  __int16 v4; // fps
  __int16 v5; // bx

  if ( *((_BYTE *)a1 + 14) == 5 )
  {
    HIBYTE(v5) = HIBYTE(*((_WORD *)a3 - 82)) & 0xFC | 2;
    LOBYTE(v5) = 63;
  }
  else
  {
    v5 = 4927;
  }
  *((_WORD *)a3 - 81) = v5;
  _EBX = &unk_6650AC;
  __asm { fxam; UNREALRED VERIFIED: FXAM generates status locally from live ST0; no incoming fpstat argument. }
  *((_DWORD *)a3 - 37) = a1;
  *((_WORD *)a3 - 80) = v4;
  *((char *)a3 - 144) = 0;
  LOBYTE(a2) = __ROL1__((char)(2 * *((char *)a3 - 159)) >> 1, 1);
  _AL = a2 & 0xF;
  __asm { xlat; UNREALRED VERIFIED: XLAT16-byte table converts FXAM status nibble to pointer-slot offset0/4/8/12. }
  (*(void (__thiscall **)(unsigned int))((char *)a1 + _AL + 16))(a2 & 0x404);
  return _ST7;
}

