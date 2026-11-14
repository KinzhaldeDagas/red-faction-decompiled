// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061771F _raise
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(signal), int0/-1. Accept exactly
// {2,4,6,8,11,15,21,22}; unsupported -> errno22, invalid_parameter(0,0,0,0,0), -1. Thread signals4/8/11: getptd_noexit NULL->-1 without own errno assignment; siglookup(signal,RAW
// PTD.table+92), then action at entry+8 WITHOUT NULL-entry guard. Global signals2/21/6-or22/15 use encoded slots2021C7C/80/84/88; load/decode handler BEFORE acquiring lock0. Handler1
// ignore returns0 before locking/mutation; handler0 QUICK _exit3. Custom global handler acquires lock0; custom thread handler no lock. EH4 scope65EEC0 protects setup/reset only.
// Thread signals save/clear PTD+96; signal8 also save fpecode+100 and set140(8Ch). Signal8 clears RAW actions0 in live group start/count (original3/7); others write encoded_null() to
// selected slot, INCLUDING RAW thread4/11 slots (not normalized to raw0; provider-dependent encoding). Disable try, invoke finally ENTRY61788D/body617893, unlocking0 iff global
// handler. Invoke CAPTURED callback AFTER unlock and OUTSIDE try: two cdecl args(8,fpecode) for8; one(signal) otherwise. Normal restore thread exception pointers/fpecode and return0.
// Throw/longjmp does not restore temporary PTD fields; one-use actions already reset. Capture-before-lock permits concurrent changes to be missed. No own last-error/doserrno mapping
// or table bounds validation.
int __cdecl raise(int Signal)
{
  DWORD *v1; // edi
  DWORD *v2; // eax
  int result; // eax
  PVOID *v4; // esi
  void *v5; // eax
  void (__cdecl *v6)(int, DWORD); // eax
  DWORD v7; // [esp+10h] [ebp-30h]
  DWORD v8; // [esp+14h] [ebp-2Ch]
  int i; // [esp+1Ch] [ebp-24h]
  void (__cdecl *v10)(int, DWORD); // [esp+20h] [ebp-20h]
  int v11; // [esp+24h] [ebp-1Ch]

  v1 = nullptr;
  v11 = 0;
  if ( Signal > 11 )
  {
    if ( Signal == 15 )
    {
      v4 = (PVOID *)dword_2021C88;
      v5 = (void *)dword_2021C88[0];
      goto LABEL_18;
    }
    if ( Signal == 21 )
    {
      v4 = (PVOID *)&dword_2021C80;
      v5 = (void *)dword_2021C80;
      goto LABEL_18;
    }
    if ( Signal != 22 )
      goto LABEL_14;
    goto LABEL_15;
  }
  if ( Signal != 11 )
  {
    if ( Signal == 2 )
    {
      v4 = (PVOID *)&dword_2021C7C;
      v5 = (void *)dword_2021C7C;
LABEL_18:
      v11 = 1;
      v6 = (void (__cdecl *)(int, DWORD))_decode_pointer(v5);
      goto LABEL_19;
    }
    if ( Signal != 4 )
    {
      if ( Signal != 6 )
      {
        if ( Signal == 8 )
          goto LABEL_7;
LABEL_14:
        *_errno() = 22;
        _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
        return -1;
      }
LABEL_15:
      v4 = (PVOID *)&dword_2021C84;
      v5 = (void *)dword_2021C84;
      goto LABEL_18;
    }
  }
LABEL_7:
  v2 = _getptd_noexit();
  v1 = v2;
  if ( !v2 )
    return -1;
  v4 = (PVOID *)(siglookup(Signal, (_DWORD *)v2[23]) + 2);
  v6 = (void (__cdecl *)(int, DWORD))*v4;
LABEL_19:
  v10 = v6;
  result = 0;
  if ( v10 == (void (__cdecl *)(int, DWORD))1 )
    return result;
  if ( !v10 )
    _exit(3);
  if ( v11 )
    _lock(0);
  if ( Signal == 8 || Signal == 11 || Signal == 4 )
  {
    v8 = v1[24];
    v1[24] = 0;
    if ( Signal != 8 )
      goto LABEL_33;
    v7 = v1[25];
    v1[25] = 140;
  }
  if ( Signal == 8 )
  {
    for ( i = dword_665CE0; i < dword_665CE0 + dword_665CE4; ++i )
      *(_DWORD *)(12 * i + v1[23] + 8) = 0;
    goto LABEL_37;
  }
LABEL_33:
  *v4 = _encoded_null();
LABEL_37:
  if ( v11 )
    _unlock(0);
  if ( Signal == 8 )
    v10(8, v1[25]);
  else
    ((void (__cdecl *)(int))v10)(Signal);
  if ( Signal == 8 || Signal == 11 || Signal == 4 )
  {
    v1[24] = v8;
    if ( Signal == 8 )
      v1[25] = v7;
  }
  return 0;
}

