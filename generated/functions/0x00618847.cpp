// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00618847 __set_statfp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl one raw status-mask DWORD (missing in old
// void() prototype),void; inspect only original lowBYTE copied once toCL. Sequential independent bit actions in order1,8,10h,4,20h. Bit1: FLD original80-bit665EC0=+2^1041,FISTP DWORD
// over own argument slot,FWAIT. Bit8: waiting FSTSW AX,load same huge extended constant,FSTP binary64 local,FWAIT,waiting FSTSW AX. Bit10h: FLD
// original80-bit665ECC=(1+2^-63)*2^-4095,FSTP binary64 local,FWAIT. Bit4: FLDZ,FLD1,FDIVRP (1/0),FSTP ST0 discard,FWAIT. Bit20h: FLDPI,FSTP binary64 local,FWAIT. Other bits
// including2 ignored. Operations attempt to generate native FP conditions through conversion/arithmetic,not direct status-register OR. Input CL retained even after FISTP overwrites
// by-value argument memory. No own clearing/masking/controlword change,errno,SEH,guaranteed completion of later actions or full x87-stack/context save. Respect LIVE masks/rounding
// and pending exceptions; unmasked conditions can trap. Normal completed own loads/pops balance depth,require capacity. Old empty pseudocode omits real FP instructions.
void __cdecl _set_statfp(unsigned int a1)
{
  ;
}

