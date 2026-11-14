// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006180FD __raise_exc_ex
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl void FP exception record/raise/recovery helper
// with seven DWORD slots (record*,savedRawCW*,flags,operation,argPointer,resultPointer,isFloat). Nonzero isFloat selects binary32 storage, zero binary64; this is not locale/default
// selection. Zero record DWORDs+4,+8,+12 only, preserving other caller scratch fields. Original lowBYTE flags independently map in
// order0x10->recordCause1/exceptionC000008F,2->2/C0000093,1->4/C0000091,4->8/C000008E,8->0x10/C0000090. Later matches override exception code; no recognized bit leaves entire input
// flags DWORD as RaiseException code. Fill record+8 enable bits0x10,8,4,2,1 from complement of rawCW mask bits1,4,8,0x10,0x20 respectively. Read waiting raw x87 status via statfp and
// map status bits1,4,8,0x10,0x20 to record+12 bits0x10,8,4,2,1; raw denormal bit2 ignored. RecordDWORD0 low2 bits encode CW rounding; bits2..4 precision maps
// CW0->2,CW0x200->1,CW0x300->0, reservedCW0x100 leaves prior descriptor bits unchanged. Operation low12 bits replace descriptor bits5..16. Mark argument descriptor+0x20/result
// descriptor+0x60 valid bit0, set bits1..4 to0(float) or1(double), retain higher bits. Copy arg to record+0x10 and result to+0x50 using live x87 FLD/FSTP; arg2 fields remain
// caller-owned. Clear x87 exceptions via clrfp, then RaiseException(selectedCode,0,1,&localArgumentSlot): single exception-information DWORD is record pointer. After a returning
// handler, reread record; set enable bits only CLEAR corresponding CW mask bits, absent enable never re-masks. Rounding bits update CW bits0xC00. IMPORTANT native precision-recovery
// block reuses EDX=0xFFFFF3FF (ROUNDING mask), not a precision mask: descriptor precision0 writes (CW&0xFFFFF3FF)|0x300; precision1 writes (CW&0xFFFFF3FF)|0x200; precision2 writes
// CW&0xFFFFF3FF; other encodings leave CW unchanged. These clear rounding bits and retain existing precision bits (OR may set more). Preserve this observed quirk, do not normalize to
// intended precision conversion or pseudocode masks. Copy possibly handler-modified record result back in selected width. Does NOT FLDCW updated CW, reconstitute status or restore
// SSE state; callers handle CW. No own SEH/record-size/NULL checks or zeroing of padding; nonreturning RaiseException skips recovery. EAX incidental, not semantic status.
void __cdecl _raise_exc_ex(
        _DWORD *Arguments,
        unsigned int *a2,
        unsigned int dwExceptionCode,
        int a4,
        const void *a5,
        void *a6,
        int a7)
{
  char v7; // cl
  unsigned int *v8; // esi
  char v9; // al
  int v10; // eax
  _DWORD *v11; // eax
  unsigned int v12; // ecx
  int v13; // eax
  _DWORD *v14; // eax
  unsigned int v15; // ecx
  float *v16; // edi
  float *v17; // ecx
  int v18; // eax
  int v19; // eax
  int v20; // eax
  unsigned int v21; // eax
  int v22; // eax
  int v23; // eax
  unsigned int v24; // eax

  v7 = dwExceptionCode;
  Arguments[1] = 0;
  Arguments[2] = 0;
  Arguments[3] = 0;
  if ( (v7 & 0x10) != 0 )
  {
    Arguments[1] |= 1u;
    dwExceptionCode = -1073741681;
  }
  if ( (v7 & 2) != 0 )
  {
    Arguments[1] |= 2u;
    dwExceptionCode = -1073741677;
  }
  if ( (v7 & 1) != 0 )
  {
    Arguments[1] |= 4u;
    dwExceptionCode = -1073741679;
  }
  if ( (v7 & 4) != 0 )
  {
    Arguments[1] |= 8u;
    dwExceptionCode = -1073741682;
  }
  if ( (v7 & 8) != 0 )
  {
    Arguments[1] |= 0x10u;
    dwExceptionCode = -1073741680;
  }
  v8 = a2;
  Arguments[2] ^= (Arguments[2] ^ ~(16 * *a2)) & 0x10;
  Arguments[2] ^= (Arguments[2] ^ ~(2 * *v8)) & 8;
  Arguments[2] ^= (Arguments[2] ^ ~(*v8 >> 1)) & 4;
  Arguments[2] ^= (Arguments[2] ^ ~(*v8 >> 3)) & 2;
  Arguments[2] ^= (Arguments[2] ^ ~(*v8 >> 5)) & 1;
  v9 = _statfp();
  if ( (v9 & 1) != 0 )
    Arguments[3] |= 0x10u;
  if ( (v9 & 4) != 0 )
    Arguments[3] |= 8u;
  if ( (v9 & 8) != 0 )
    Arguments[3] |= 4u;
  if ( (v9 & 0x10) != 0 )
    Arguments[3] |= 2u;
  if ( (v9 & 0x20) != 0 )
    Arguments[3] |= 1u;
  v10 = *v8 & 0xC00;
  switch ( v10 )
  {
    case 0:
      *Arguments &= 0xFFFFFFFC;
      break;
    case 1024:
      v11 = Arguments;
      v12 = *Arguments & 0xFFFFFFFC | 1;
      goto LABEL_27;
    case 2048:
      v11 = Arguments;
      v12 = *Arguments & 0xFFFFFFFC | 2;
LABEL_27:
      *v11 = v12;
      break;
    case 3072:
      *Arguments |= 3u;
      break;
  }
  v13 = *v8 & 0x300;
  switch ( v13 )
  {
    case 0:
      v14 = Arguments;
      v15 = *Arguments & 0xFFFFFFE3 | 8;
      goto LABEL_36;
    case 512:
      v14 = Arguments;
      v15 = *Arguments & 0xFFFFFFE3 | 4;
LABEL_36:
      *v14 = v15;
      break;
    case 768:
      *Arguments &= 0xFFFFFFE3;
      break;
  }
  *Arguments ^= (*Arguments ^ (32 * a4)) & 0x1FFE0;
  Arguments[8] |= 1u;
  v16 = (float *)a6;
  if ( a7 )
  {
    Arguments[8] &= 0xFFFFFFE1;
    *((float *)Arguments + 4) = *(float *)a5;
    Arguments[24] |= 1u;
    Arguments[24] &= 0xFFFFFFE1;
    *((float *)Arguments + 20) = *v16;
  }
  else
  {
    Arguments[8] = Arguments[8] & 0xFFFFFFE1 | 2;
    *((double *)Arguments + 2) = *(double *)a5;
    Arguments[24] |= 1u;
    Arguments[24] = Arguments[24] & 0xFFFFFFE1 | 2;
    *((double *)Arguments + 10) = *(double *)v16;
  }
  _clrfp();
  RaiseException(dwExceptionCode, 0, 1u, (const ULONG_PTR *)&Arguments);
  v17 = (float *)Arguments;
  if ( (Arguments[2] & 0x10) != 0 )
    *v8 &= ~1u;
  if ( ((_BYTE)v17[2] & 8) != 0 )
    *v8 &= ~4u;
  if ( ((_BYTE)v17[2] & 4) != 0 )
    *v8 &= ~8u;
  if ( ((_BYTE)v17[2] & 2) != 0 )
    *v8 &= ~0x10u;
  if ( ((_BYTE)v17[2] & 1) != 0 )
    *v8 &= ~0x20u;
  v18 = *(_DWORD *)v17 & 3;
  if ( !v18 )
  {
    *v8 &= 0xFFFFF3FF;
    goto LABEL_59;
  }
  v19 = v18 - 1;
  if ( !v19 )
  {
    v21 = *v8 & 0xFFFFF3FF | 0x400;
    goto LABEL_56;
  }
  v20 = v19 - 1;
  if ( !v20 )
  {
    v21 = *v8 & 0xFFFFF3FF | 0x800;
LABEL_56:
    *v8 = v21;
    goto LABEL_59;
  }
  if ( v20 == 1 )
    *v8 |= 0xC00u;
LABEL_59:
  v22 = (*(_DWORD *)v17 >> 2) & 7;
  if ( !v22 )
  {
    v24 = *v8 & 0xFFFFF0FF | 0x300;
    goto LABEL_65;
  }
  v23 = v22 - 1;
  if ( !v23 )
  {
    v24 = *v8 & 0xFFFFF1FF | 0x200;
LABEL_65:
    *v8 = v24;
    goto LABEL_66;
  }
  if ( v23 == 1 )
    *v8 &= 0xFFFFF3FF;
LABEL_66:
  if ( a7 )
    *v16 = v17[20];
  else
    *(double *)v16 = *((double *)v17 + 10);
}

