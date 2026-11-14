// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006217FC __control87
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(unsigned NewValue,unsigned Mask),return actual
// combined logical controls,not old rawCW. Waiting FSTCW writes16-bit local,decoder uses only lowWORD despite initial DWORD load of uninitialized upper half. Native x87 masks
// {1,2,4,8,10h,20h}->{10h,80000h,8,4,2,1};round0C00h>>2 ->logical0300h;native precision0000h->020000h,0200h->010000h,0100h/0300h->0;native1000h->040000h. Compute
// wantedX=(decodedX&~ORIGINALMask)|(NewValue&ORIGINALMask),store into own Mask stack slot. If equal decodedX,skip x87 write;otherwise EBX=wantedX,call hw_cw,zero-extend
// output16,FLDCW,WAIT/FSTCW read ACTUAL hardware CW,redecode it and replace own Mask slot with actualX. Does not preserve unmapped native bits on rebuild. Even a requested logical
// SSE-only/unknown set bit can cause x87 rebuild before it is discarded by encoder. Query Mask0 skips writes,but waiting FSTCW can deliver pending FP exceptions;no own catch/clear.
// If LIVE global2021F64==0 return X alone,no MXCSR access/ambiguity flag. Otherwise restrict ORIGINAL mask (saved inEDI) to0308031Fh;STMXCSR old fullDWORD,decode only mask
// bits80h..1000h into same six logical masks,6000h>>5 into0300h,denormal bits8040h into {0->0,8040h->01000000h,0040h->02000000h,8000h->03000000h}. Low status bits ignored by decoder.
// wantedS=(oldS&~effectiveSSEMask)|(NewValue&effectiveSSEMask). If equal oldS skip setter,preserve current MXCSR bits. Else EDX=wantedS,call hw_cw_sse2 (ECX NOT an argument),push
// rebuilt word,set_fpsr_sse2,ignore EAX,re-read ACTUAL STMXCSR and decode result. Rebuilt word zeros all six prior status bits; setter may additionally clear bit40h/latch,so returned
// S comes from readback,not request. Original x87/SSE initial and readback decoder pairs agree for all65536 lowWORD patterns; canonical encoders roundtrip separately verified. Return
// actualX OR actualS; if ((actualX XOR actualS)&0008031Fh)!=0 additionallyOR80000000h ambiguity marker. Compare ONLY common exception-mask/rounding fields,not x87-only
// precision/infinity or SSE-only denormal modes. No runtime CPU recheck,validation of NewValue/Mask,errno,lock,full FP context save or rollback. x87 update precedes SSE; later
// trap/failure can leave partial update. FLDCW/LDMXCSR/readback effects use live environment and CPU behavior. Does not FNCLEX x87 flags; own STMXCSR access unguarded. Output is
// normalized/possibly ambiguous aggregate,not proof both engines accepted identical requested state.
unsigned int __cdecl _control87(unsigned int NewValue, unsigned int Mask)
{
  int v2; // edx
  int v3; // eax
  unsigned int result; // eax
  __int16 v6; // ax
  __int16 v7; // bx
  unsigned int v8; // edx
  int v9; // eax
  int v10; // esi
  __int16 v11; // ax
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  unsigned int v15; // edx
  int v16; // eax
  __int16 v17; // cx
  int v18; // edx
  int v19; // eax
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  unsigned int v23; // [esp+14h] [ebp-Ch]
  __int16 v24; // [esp+18h] [ebp-8h]
  unsigned int Maska; // [esp+2Ch] [ebp+Ch]

  v2 = 0;
  if ( (v24 & 1) != 0 )
    v2 = 16;
  if ( (v24 & 4) != 0 )
    v2 |= 8u;
  if ( (v24 & 8) != 0 )
    v2 |= 4u;
  if ( (v24 & 0x10) != 0 )
    v2 |= 2u;
  if ( (v24 & 0x20) != 0 )
    v2 |= 1u;
  if ( (v24 & 2) != 0 )
    v2 |= 0x80000u;
  v3 = v24 & 0xC00;
  if ( v3 )
  {
    switch ( v3 )
    {
      case 1024:
        v2 |= 0x100u;
        break;
      case 2048:
        v2 |= 0x200u;
        break;
      case 3072:
        v2 |= 0x300u;
        break;
    }
  }
  if ( (v24 & 0x300) != 0 )
  {
    if ( (v24 & 0x300) == 0x200 )
      v2 |= 0x10000u;
  }
  else
  {
    v2 |= 0x20000u;
  }
  if ( (v24 & 0x1000) != 0 )
    v2 |= 0x40000u;
  result = Mask & NewValue | v2 & ~Mask;
  Maska = result;
  if ( result != v2 )
  {
    v6 = _hw_cw(result);
    v7 = v6;
    v8 = 0;
    if ( (v6 & 1) != 0 )
      v8 = 16;
    if ( (v6 & 4) != 0 )
      v8 |= 8u;
    if ( (v6 & 8) != 0 )
      v8 |= 4u;
    if ( (v6 & 0x10) != 0 )
      v8 |= 2u;
    if ( (v6 & 0x20) != 0 )
      v8 |= 1u;
    if ( (v6 & 2) != 0 )
      v8 |= 0x80000u;
    v9 = v6 & 0xC00;
    if ( (v7 & 0xC00) != 0 )
    {
      switch ( v9 )
      {
        case 1024:
          v8 |= 0x100u;
          break;
        case 2048:
          v8 |= 0x200u;
          break;
        case 3072:
          v8 |= 0x300u;
          break;
      }
    }
    if ( (v7 & 0x300) != 0 )
    {
      if ( (v7 & 0x300) == 0x200 )
        v8 |= 0x10000u;
    }
    else
    {
      v8 |= 0x20000u;
    }
    if ( (v7 & 0x1000) != 0 )
      v8 |= 0x40000u;
    Maska = v8;
    result = v8;
  }
  v10 = 0;
  if ( unk_2021F64 )
  {
    v11 = _mm_getcsr();
    if ( (v11 & 0x80u) != 0 )
      v10 = 16;
    if ( (v11 & 0x200) != 0 )
      v10 |= 8u;
    if ( (v11 & 0x400) != 0 )
      v10 |= 4u;
    if ( (v11 & 0x800) != 0 )
      v10 |= 2u;
    if ( (v11 & 0x1000) != 0 )
      v10 |= 1u;
    if ( (v11 & 0x100) != 0 )
      v10 |= 0x80000u;
    v12 = v11 & 0x6000;
    if ( (v11 & 0x6000) != 0 )
    {
      switch ( v12 )
      {
        case 8192:
          v10 |= 0x100u;
          break;
        case 16384:
          v10 |= 0x200u;
          break;
        case 24576:
          v10 |= 0x300u;
          break;
      }
    }
    v13 = (v11 & 0x8040) - 64;
    if ( v13 )
    {
      v14 = v13 - 32704;
      if ( v14 )
      {
        if ( v14 == 64 )
          v10 |= (unsigned int)&unk_1000000;
      }
      else
      {
        v10 |= 0x3000000u;
      }
    }
    else
    {
      v10 |= (unsigned int)&unk_2000000;
    }
    v15 = NewValue & Mask & 0x308031F | v10 & ~(Mask & 0x308031F);
    if ( v15 == v10 )
    {
      v16 = v10;
    }
    else
    {
      v23 = __hw_cw_sse2(v15);
      __set_fpsr_sse2(v23);
      v17 = _mm_getcsr();
      v18 = 0;
      if ( (v17 & 0x80u) != 0 )
        v18 = 16;
      if ( (v17 & 0x200) != 0 )
        v18 |= 8u;
      if ( (v17 & 0x400) != 0 )
        v18 |= 4u;
      if ( (v17 & 0x800) != 0 )
        v18 |= 2u;
      if ( (v17 & 0x1000) != 0 )
        v18 |= 1u;
      if ( (v17 & 0x100) != 0 )
        v18 |= 0x80000u;
      v19 = v17 & 0x6000;
      if ( (v17 & 0x6000) != 0 )
      {
        switch ( v19 )
        {
          case 8192:
            v18 |= 0x100u;
            break;
          case 16384:
            v18 |= 0x200u;
            break;
          case 24576:
            v18 |= 0x300u;
            break;
        }
      }
      v20 = (v17 & 0x8040) - 64;
      if ( v20 )
      {
        v21 = v20 - 32704;
        if ( v21 )
        {
          if ( v21 == 64 )
            v18 |= (unsigned int)&unk_1000000;
        }
        else
        {
          v18 |= 0x3000000u;
        }
      }
      else
      {
        v18 |= (unsigned int)&unk_2000000;
      }
      v16 = v18;
    }
    v22 = Maska ^ v16;
    result = Maska | v16;
    if ( (v22 & 0x8031F) != 0 )
      result |= 0x80000000;
  }
  return result;
}

