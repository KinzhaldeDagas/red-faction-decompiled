// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D394 __87except
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): x87 math-record exception adapter; ordinary void
// cdecl(operation,C-math-record pointer,const unsigned WORD* savedCWPointer), three stack DWORDs. Custom16-byte aligned frame copies return PC; incoming EBP is saved/restored, not
// input. Read source CW WORD once into local DWORD before reading record.type. Map types1/5->flags8,2->4,3->0x11,4->0x12,8->0x10; type7 becomes1 and skips handle/raise, all other
// types skip handle/raise. Selected flags call handle_exc(flags,&record.retval,savedCW). On zero, operation16(atan2),22(fmod),29(pow) copy arg2 to scratch+0x30 and set scratch
// DWORD+0x40 low5 bits=3; other operations clear only bit0. raise_exc(scratch,&localCW,flags,operation,&record.arg1,&record.retval) may change local CW/result. Always restore raw x87
// CW via ctrlfp(localCW,0xFFFF). Current type8 or mode0x666060 nonzero -> errno setter; otherwise direct zero stub0x61D8D7(record) then errno on zero (always with unchanged stub).
// Type8 leaves errno unchanged because setter only maps1/2/3. C record offsets0 type,4 name,8 arg1,16 arg2,24 retval; no C++ exception object. Source CW pointer is never written.
// Cookie check and restore ESP/nonvolatiles on return. No own SEH/pointer or record-size checks/SSE-state restore.
void __cdecl _87except(int a1, _DWORD *a2, const unsigned __int16 *a3)
{
  int v3; // ebp
  unsigned int v4; // ecx
  bool v5; // zf
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  unsigned int v12; // [esp-88h] [ebp-94h] BYREF
  unsigned int v13; // [esp-84h] [ebp-90h]
  int v14; // [esp-80h] [ebp-8Ch] BYREF
  double v15; // [esp-50h] [ebp-5Ch]
  unsigned int v16; // [esp-40h] [ebp-4Ch]
  unsigned int v17; // [esp-4h] [ebp-10h]
  _DWORD v18[3]; // [esp+0h] [ebp-Ch] BYREF
  _UNKNOWN *retaddr; // [esp+Ch] [ebp+0h]

  v18[0] = v3;
  v18[1] = retaddr;
  v17 = (unsigned int)v18 ^ dword_664BD8;
  v4 = *a3;
  v6 = *a2 - 1;
  v5 = *a2 == 1;
  v12 = v4;
  if ( v5 )
    goto LABEL_13;
  v7 = v6 - 1;
  if ( !v7 )
  {
    v13 = 4;
    goto LABEL_14;
  }
  v8 = v7 - 1;
  if ( !v8 )
  {
    v13 = 17;
    goto LABEL_14;
  }
  v9 = v8 - 1;
  if ( !v9 )
  {
    v13 = 18;
    goto LABEL_14;
  }
  v10 = v9 - 1;
  if ( !v10 )
  {
LABEL_13:
    v13 = 8;
LABEL_14:
    if ( !_handle_exc(v13, (double *)a2 + 3, v4) )
    {
      if ( a1 == 16 || a1 == 22 || a1 == 29 )
      {
        v15 = *((double *)a2 + 2);
        v16 = v16 & 0xFFFFFFE0 | 3;
      }
      else
      {
        v16 &= ~1u;
      }
      _raise_exc(&v14, &v12, v13, a1, (const double *)a2 + 1, (double *)a2 + 3);
    }
    goto LABEL_21;
  }
  v11 = v10 - 2;
  if ( !v11 )
  {
    *a2 = 1;
    goto LABEL_21;
  }
  if ( v11 == 1 )
  {
    v13 = 16;
    goto LABEL_14;
  }
LABEL_21:
  _ctrlfp(v12, 0xFFFFu);
  if ( *a2 == 8 || dword_666060 || !crt_return_zero_0061d8d7() )
    _set_errno_from_matherr(*a2);
  crt_check_security_cookie_ecx((unsigned int)v18 ^ v17);
}

