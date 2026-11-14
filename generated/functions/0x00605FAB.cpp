// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605FAB __onexit_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(callback), returns original callback on
// insertion or NULL on failure; refined _onexit_t ABI. Decode global begin2022F90/end2022F8C; require unsigned end>=begin and nonwrapping used+4, used=end-begin. Query msize(begin);
// sufficient capacity skips allocation. Otherwise try realloc_crt to capacity+min(capacity,2048), guarded against unsigned overflow; failure/overflow retries capacity+16 with
// overflow guard. Both fail -> NULL. After move, end=newBase+4*(SIGNED used SAR2), publish encoded newBase. Store encode(callback) at end, advance4 and publish encoded end. No
// callback NULL rejection: registering NULL can advance the array and still return NULL. No own lock, initialization guard, explicit msize SIZE_MAX failure handling,
// pointer/alignment/allocator-size validation, or own errno assignment; allocator behavior delegated. Correct operation assumes initialized consistent callback bounds; msize failure
// can pass the unsigned capacity comparison. Callback not invoked here.
_onexit_t __cdecl _onexit_nolock(_onexit_t a1)
{
  PVOID *v1; // edi
  PVOID *v2; // eax
  PVOID *v3; // esi
  int v4; // ebx
  size_t v5; // edi
  int v6; // eax
  size_t v7; // eax
  char *v8; // eax
  PVOID *Block; // [esp+Ch] [ebp-4h]

  v1 = (PVOID *)_decode_pointer(dword_2022F90);
  Block = v1;
  v2 = (PVOID *)_decode_pointer(dword_2022F8C);
  v3 = v2;
  if ( v2 >= v1 )
  {
    v4 = (char *)v2 - (char *)v1;
    if ( (unsigned int)((char *)v2 - (char *)v1) < 0xFFFFFFFC )
    {
      v5 = _msize(v1);
      if ( v5 >= v4 + 4 )
      {
LABEL_11:
        *v3 = _encode_pointer(a1);
        dword_2022F8C = _encode_pointer(v3 + 1);
        return a1;
      }
      v6 = 2048;
      if ( v5 < 0x800 )
        v6 = v5;
      v7 = v5 + v6;
      if ( v7 >= v5 && (v8 = (char *)_realloc_crt(Block, v7)) != nullptr
        || v5 + 16 >= v5 && (v8 = (char *)_realloc_crt(Block, v5 + 16)) != nullptr )
      {
        v3 = (PVOID *)&v8[4 * (v4 >> 2)];
        dword_2022F90 = _encode_pointer(v8);
        goto LABEL_11;
      }
    }
  }
  return nullptr;
}

