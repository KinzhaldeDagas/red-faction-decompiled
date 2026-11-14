// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060BE03 __getdrive
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs, int drive number or0.
// GetCurrentDirectoryA(261,stack). SIGNED result>260 allocates calloc_crt(result+1,1), marks owned then queries again with result+1; no second size/growth validation. Allocation
// failure OR API result0 sets errno12 and returns0 regardless actual LastError, no dosmaperr/dosreset. Nonzero API result: if path[1]==colon return toupper(unsigned firstbyte)-64,
// otherwise0 (including UNC, without own error). Free owned allocation on normal return. No lock, alphabet/range validation, or exception-finally allocation cleanup.
int __cdecl _getdrive()
{
  CHAR *v0; // ebx
  signed int CurrentDirectoryA; // esi
  CHAR *v2; // eax
  int v3; // edi
  int v5; // [esp+10h] [ebp-110h]
  CHAR Buffer[264]; // [esp+14h] [ebp-10Ch] BYREF

  v5 = 0;
  v0 = Buffer;
  CurrentDirectoryA = GetCurrentDirectoryA(0x105u, Buffer);
  if ( CurrentDirectoryA > 260 )
  {
    v2 = (CHAR *)_calloc_crt(CurrentDirectoryA + 1, 1);
    v0 = v2;
    if ( v2 )
    {
      v5 = 1;
      CurrentDirectoryA = GetCurrentDirectoryA(CurrentDirectoryA + 1, v2);
    }
    else
    {
      *_errno() = 12;
      CurrentDirectoryA = 0;
    }
  }
  v3 = 0;
  if ( CurrentDirectoryA )
  {
    if ( v0[1] == 58 )
      v3 = toupper((unsigned __int8)*v0) - 64;
  }
  else
  {
    *_errno() = 12;
  }
  if ( v5 )
    free(v0);
  return v3;
}

