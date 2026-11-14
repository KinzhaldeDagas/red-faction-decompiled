// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061755D __XcptFilter
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(unsigned exceptionCode,EXCEPTION_POINTERS*),
// returns filter disposition. getptd_noexit NULL->0. PTD+92 is RAW table pointer; records12 bytes {DWORD exceptionCode,int signal,RAW action}. Scan using global count665CEC
// (original10), first record read BEFORE bound test; no table NULL/count validation. No match/action0 ->0 search. Action5 resets matched RAW action0 and returns1 execute handler.
// Action1 returns-1 continue execution unchanged. Other action: save PTD+96, temporarily assign passed exception pointers. For signal8, clear RAW actions0 across live group
// start665CE0/count665CE4 (original3/7), save PTD+100 fpecode; map codes C000008E->83h,0090->81h,0091->84h,0093->85h,008D->82h,008F->86h,0092->8Ah; other leaves old fpecode. Invoke
// callback with TWO cdecl args (8,PTD.fpecode), despite misleading single-argument pseudocode; normal restore fpecode. Other signals clear only matched action0, call
// callback(signal). Normal restore exception pointers, return-1. No lock, EH/finally, bounds checking or callback decoding. Throw/longjmp leaves actions reset and temporary PTD
// fields unrestored.
int __cdecl _XcptFilter(unsigned int a1, struct _EXCEPTION_POINTERS *a2)
{
  int result; // eax
  _DWORD *v3; // esi
  int *v4; // edx
  int *v5; // ecx
  int *v6; // eax
  void (__cdecl *v7)(int); // ebx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // eax
  int v12; // edi
  int v13; // [esp+4h] [ebp-8h]

  result = (int)_getptd_noexit();
  v3 = (_DWORD *)result;
  if ( result )
  {
    v4 = *(int **)(result + 92);
    v5 = v4;
    do
    {
      if ( *v5 == a1 )
        break;
      v5 += 3;
    }
    while ( v5 < &v4[3 * dword_665CEC[0]] );
    if ( v5 < &v4[3 * dword_665CEC[0]] && *v5 == a1 )
      v6 = v5;
    else
      v6 = nullptr;
    if ( v6 && (v7 = (void (__cdecl *)(int))v6[2]) != nullptr )
    {
      if ( v7 == (void (__cdecl *)(int))5 )
      {
        v6[2] = 0;
        return 1;
      }
      else
      {
        if ( v7 != (void (__cdecl *)(int))1 )
        {
          v13 = v3[24];
          v3[24] = a2;
          v8 = v6[1];
          if ( v8 == 8 )
          {
            v9 = dword_665CE0;
            if ( dword_665CE0 < dword_665CE0 + dword_665CE4 )
            {
              v10 = 12 * dword_665CE0;
              do
              {
                *(_DWORD *)(v10 + v3[23] + 8) = 0;
                ++v9;
                v10 += 12;
              }
              while ( v9 < dword_665CE0 + dword_665CE4 );
            }
            v11 = *v6;
            v12 = v3[25];
            switch ( v11 )
            {
              case -1073741682:
                v3[25] = 131;
                break;
              case -1073741680:
                v3[25] = 129;
                break;
              case -1073741679:
                v3[25] = 132;
                break;
              case -1073741677:
                v3[25] = 133;
                break;
              case -1073741683:
                v3[25] = 130;
                break;
              case -1073741681:
                v3[25] = 134;
                break;
              case -1073741678:
                v3[25] = 138;
                break;
            }
            v7(8);
            v3[25] = v12;
          }
          else
          {
            v6[2] = 0;
            v7(v8);
          }
          v3[24] = v13;
        }
        return -1;
      }
    }
    else
    {
      return 0;
    }
  }
  return result;
}

