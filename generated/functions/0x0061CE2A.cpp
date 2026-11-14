// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061CE2A ___wtomb_environ
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs, wide-to-narrow environ conversion0/-1;
// assumes global wideenv2021368 nonNULL and dereferences it without guard. Empty wide pointer array returns0 WITHOUT creating narrowenv. For each wide string use
// WideCharToMultiByte(CP_ACP0,flags0,cch=-1) sizequery;0 ->-1. calloc_crt(bytes,1),NULL ->-1. Second conversion0 frees current allocation/-1. Call crtsetenv(&localOwned,0); NEGATIVE
// status is IGNORED as overall failure: free localOwned if still nonNULL, then continue next wide entry. Nonnegative call transfers/consumes ownership according to crtsetenv. End
// returns0 even earlier insertion failures; partial narrowenv retained on conversion/allocation failure. No own lock, invalid callback, rollback or wide-array free.
int __wtomb_environ()
{
  LPCWCH *v0; // edi
  const WCHAR *v1; // eax
  size_t v2; // eax
  void *v3; // eax
  int cbMultiByte; // [esp+Ch] [ebp-8h]
  void *Block; // [esp+10h] [ebp-4h] BYREF

  v0 = (LPCWCH *)unk_2021368;
  Block = nullptr;
  v1 = (const WCHAR *)*unk_2021368;
  if ( !*unk_2021368 )
    return 0;
  while ( 1 )
  {
    v2 = WideCharToMultiByte(0, 0, v1, -1, nullptr, 0, nullptr, nullptr);
    cbMultiByte = v2;
    if ( !v2 )
      break;
    v3 = _calloc_crt(v2, 1u);
    Block = v3;
    if ( !v3 )
      break;
    if ( !WideCharToMultiByte(0, 0, *v0, -1, (LPSTR)v3, cbMultiByte, nullptr, nullptr) )
    {
      free(Block);
      return -1;
    }
    if ( __crtsetenv((const unsigned __int8 **)&Block, 0) < 0 )
    {
      if ( Block )
      {
        free(Block);
        Block = nullptr;
      }
    }
    v1 = *++v0;
    if ( !*v0 )
      return 0;
  }
  return -1;
}

