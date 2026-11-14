// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BA050 ??_U@YAPAXI@Z_0
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): MSVC operator new[] adapter: cdecl byte size forwarded unchanged to scalar operator new, returned pointer forwarded. No array cookie, element construction, multiplication or length check inside this wrapper. Standard decorated name retained.
void *__cdecl operator new[](size_t Size)
{
  return operator new(Size);
}

