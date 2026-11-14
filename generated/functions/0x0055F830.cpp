// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F830 rf_string_lowercase_in_place_crt
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Recovered thiscall method. For signed indices0..storedExtent-1, sign-extends each char into int, calls CRT tolower and stores low return byte back. Uses extent rather than strlen, so reserved/stale trailing bytes are also processed. No NULL-buffer or unsigned-char normalization check; extent unchanged. No stack arguments or object return contract.
void __thiscall rf_string_lowercase_in_place_crt(void *this)
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < *(_DWORD *)this; ++i )
    *(_BYTE *)(*((_DWORD *)this + 1) + i) = tolower(*(char *)(*((_DWORD *)this + 1) + i));
}

