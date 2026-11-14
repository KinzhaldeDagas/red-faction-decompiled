// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006179AC __wincmdln
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs, borrowed pointer to command-line remainder.
// Initialize mb table if2022F94==0. Use command line2022F84 or static empty6392E5. Scan program portion toggling quote mode on EVERY doublequote, unsigned byte<=32 stops ONLYoutside
// quotes, NUL always stops. Each byte tested via ismbblead; lead consumes extra byte without checking trail/NUL, possibly stepping past terminator. After break skip all nonNUL
// unsigned bytes<=32, return cursor. No backslash/escaped-quote grammar, allocation, copying or validation; grammar differs from parse_cmdline.
const char *_wincmdln()
{
  BOOL v0; // edi
  const char *v1; // esi
  unsigned __int8 v2; // al

  v0 = 0;
  if ( !unk_2022F94 )
    __initmbctable();
  v1 = dword_2022F84;
  if ( !dword_2022F84 )
    v1 = byte_6392E5;
  while ( 1 )
  {
    v2 = *v1;
    if ( *v1 <= 0x20u )
    {
      if ( !v2 )
        return v1;
      if ( !v0 )
        break;
    }
    if ( v2 == 34 )
      v0 = !v0;
    if ( _ismbblead(v2) )
      ++v1;
    ++v1;
  }
  while ( *v1 && *v1 <= 0x20u )
    ++v1;
  return v1;
}

