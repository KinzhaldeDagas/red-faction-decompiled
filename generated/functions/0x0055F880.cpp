// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F880 rf_string_uppercase_in_place_crt
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Recovered thiscall method. Iterates stored extent, calls CRT toupper on each SIGN-extended byte, and writes low return byte in place. Does not stop at NUL, recompute extent, normalize char to unsigned or validate buffer. No stack arguments; locale/CRT conversion semantics apply.
void __thiscall rf_string_uppercase_in_place_crt(void *this)
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < *(_DWORD *)this; ++i )
    *(_BYTE *)(*((_DWORD *)this + 1) + i) = toupper(*(char *)(*((_DWORD *)this + 1) + i));
}

