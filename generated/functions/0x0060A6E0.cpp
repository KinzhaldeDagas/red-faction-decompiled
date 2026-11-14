// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A6E0 __except_handler4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): EH4 exception dispatch, three used cdecl stack slots
// (exception record, registration, context). Decode registration[2] with LIVE global cookie 0x664BD8 before validating cookies; parent frame is registration+16. Scope header DWORDs
// are GS-cookie offset, GS-xor offset, EH-cookie offset, EH-xor offset. Optional GS check only when first offset != -2; EH check mandatory. Each cookie is memory[parent+cookieOffset]
// XOR ADDRESS(parent+xorOffset), not a second memory read. Flags &0x66 selects unwind: level -2 returns1; otherwise EH4_LocalUnwind(frame,-2,parent,&globalCookie), recheck both
// applicable cookies, return1. Normal dispatch stores address of temporary {exception,context} pair at registration-4 without restoring previous value. Walk 12-byte scope entries
// after 16-byte header, sentinel -2; save enclosing index before filter. NULL filter skips finally record. Filter adapter receives ECX=filter PC,EDX=parent; negative returns
// disposition0 after cookie recheck, zero continues at saved enclosing, positive selects handler. If any filter ran, exhausting search rechecks cookies; no filter means only initial
// checks. Positive path optionally invokes live destructor hook(exception,1) for code E06D7363 when slot 0x64905C is nonNULL and IsNonwritableInCurrentImage validates the SLOT
// address (not target). Global unwind to frame, local unwind to selected level if needed, publish pre-filter enclosing index, recheck cookies, transfer ECX=handler/EDX=parent.
// Transfer helper tail-JMPs handler, no supported return path. No scope count/index/cycle/pointer bounds checks or own SEH; malformed offsets use native 32-bit arithmetic.
int __cdecl _except_handler4(struct EHExceptionRecord *a1, _DWORD *TargetFrame, struct _CONTEXT *a3)
{
  unsigned int v3; // ebx
  int *v4; // esi
  int v5; // eax
  _DWORD *v6; // edi
  void *v7; // ecx
  unsigned int v8; // eax
  int v9; // eax
  _DWORD *v11; // eax
  _DWORD v12[2]; // [esp+Ch] [ebp-18h] BYREF
  int v13; // [esp+14h] [ebp-10h]
  int v14; // [esp+18h] [ebp-Ch]
  unsigned int v15; // [esp+1Ch] [ebp-8h]
  char v16; // [esp+23h] [ebp-1h]

  v3 = (unsigned int)TargetFrame;
  v4 = (int *)(dword_664BD8 ^ TargetFrame[2]);
  v5 = *v4;
  v16 = 0;
  v14 = 1;
  v6 = TargetFrame + 4;
  if ( v5 != -2 )
    crt_check_security_cookie_ecx(*(_DWORD *)((char *)v6 + v5) ^ ((unsigned int)v6 + v4[1]));
  crt_check_security_cookie_ecx(*(_DWORD *)((char *)v6 + v4[2]) ^ ((unsigned int)v6 + v4[3]));
  if ( (a1->ExceptionFlags & 0x66) != 0 )
  {
LABEL_25:
    if ( *(_DWORD *)(v3 + 12) == -2 )
      return v14;
    _EH4_LocalUnwind(v3, 0xFFFFFFFE, (int)v6, &dword_664BD8);
  }
  else
  {
    *(TargetFrame - 1) = v12;
    v3 = TargetFrame[3];
    v12[0] = a1;
    v12[1] = a3;
    if ( v3 == -2 )
      return v14;
    do
    {
      v7 = (void *)v4[3 * v3 + 5];
      v13 = (int)&v4[3 * v3 + 4];
      v8 = *(_DWORD *)v13;
      v15 = *(_DWORD *)v13;
      if ( v7 )
      {
        v9 = _EH4_CallFilterFunc(v7, v6);
        v16 = 1;
        if ( v9 < 0 )
        {
          v14 = 0;
          goto LABEL_11;
        }
        if ( v9 > 0 )
        {
          if ( a1->ExceptionCode == -529697949
            && __DestructExceptionObject
            && _IsNonwritableInCurrentImage((int)&off_64905C) )
          {
            __DestructExceptionObject(a1, 1u);
          }
          _EH4_GlobalUnwind(TargetFrame);
          v11 = TargetFrame;
          if ( TargetFrame[3] != v3 )
          {
            _EH4_LocalUnwind((int)TargetFrame, v3, (int)v6, &dword_664BD8);
            v11 = TargetFrame;
          }
          v11[3] = v15;
          if ( *v4 != -2 )
            crt_check_security_cookie_ecx(*(_DWORD *)((char *)v6 + *v4) ^ ((unsigned int)v6 + v4[1]));
          crt_check_security_cookie_ecx(*(_DWORD *)((char *)v6 + v4[2]) ^ ((unsigned int)v6 + v4[3]));
          _EH4_TransferToHandler(*(void **)(v13 + 8), v6);
          goto LABEL_25;
        }
        v8 = v15;
      }
      v3 = v8;
    }
    while ( v8 != -2 );
    if ( !v16 )
      return v14;
  }
LABEL_11:
  if ( *v4 != -2 )
    crt_check_security_cookie_ecx(*(_DWORD *)((char *)v6 + *v4) ^ ((unsigned int)v6 + v4[1]));
  crt_check_security_cookie_ecx(*(_DWORD *)((char *)v6 + v4[2]) ^ ((unsigned int)v6 + v4[3]));
  return v14;
}

