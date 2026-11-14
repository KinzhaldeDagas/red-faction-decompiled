// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00621ECD crt_get_dword_02021e18_checked
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl outputDWORD pointer, plain RET. NonNULL output: load LIVE global02021E18, write oneDWORD, return0 without changing errno. NULL output: call6115E0
// __errno, store22 at returned address, call611578 __invalid_parameter with FIVE zero stack slots, ADD20. If invalid-parameter handler returns, return22; nonreturn/throw policy
// delegated. No output-capacity test beyond NULL, global update, input parsing or old errno restoration. Exact same instruction pattern across four globals; pointer/global accesses
// native32-bit.
int __cdecl crt_get_dword_02021e18_checked(_DWORD *a1)
{
  if ( a1 )
  {
    *a1 = unk_2021E18;
    return 0;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 22;
  }
}

