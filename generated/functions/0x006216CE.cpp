// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006216CE __hw_cw
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Register ABI unsigned logical control inEBX,unsigned
// EAX native x87 controlword bits; no stack inputs,EBX unchanged,ESI saved/restored,ECX/EDX scratch. Integer-only encoder,not an FLDCW itself. Logical mask bits {10h,80000h,8,4,2,1}
// map to native {1,2,4,8,10h,20h}. Logical rounding field0300h maps left2 to native0C00h. Logical precision field030000h:0 ->native0300h;010000h ->0200h;020000h OR030000h ->0000h
// (noncanonical3 collapses). Logical040000h ->native1000h. All other bits ignored; output rebuilt from zero,does NOT retain native reserved/unrepresented bits. Return only bits1F3Fh
// domain,upper16zero. Native decoding inside control87 maps native precision0000h ->logical020000h,0200h ->010000h,0100h or0300h ->0; reserved0100h and logical030000h therefore not
// invertible. Canonical field-domain roundtrips independently interpreted from native integer instructions. Existing int types corrected unsigned; actual input register retained.
unsigned int __usercall _hw_cw@<eax>(unsigned int a1@<ebx>)
{
  unsigned int result; // eax
  unsigned int v2; // ecx

  result = (a1 & 0x10) != 0;
  if ( (a1 & 8) != 0 )
    result |= 4u;
  if ( (a1 & 4) != 0 )
    result |= 8u;
  if ( (a1 & 2) != 0 )
    result |= 0x10u;
  if ( (a1 & 1) != 0 )
    result |= 0x20u;
  if ( (a1 & 0x80000) != 0 )
    result |= 2u;
  v2 = a1 & 0x300;
  if ( (a1 & 0x300) != 0 )
  {
    switch ( v2 )
    {
      case 0x100u:
        result |= 0x400u;
        break;
      case 0x200u:
        result |= 0x800u;
        break;
      case 0x300u:
        result |= 0xC00u;
        break;
    }
  }
  if ( (a1 & 0x30000) != 0 )
  {
    if ( (a1 & 0x30000) == 0x10000 )
      result |= 0x200u;
  }
  else
  {
    result |= 0x300u;
  }
  if ( (a1 & 0x40000) != 0 )
    result |= 0x1000u;
  return result;
}

