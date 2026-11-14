// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006178ED crt_store_dword_02021ca0
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one raw DWORD, plain RET. Load caller argument to EAX, store it verbatim at fixed global02021CA0, return SAME NEW value. Does not read/return old
// global, encode/decode pointer, validate enum/flag, lock or invoke a callback. Generic address-based name avoids assigning a policy or callback type without consumer evidence; no
// extra parameters consumed.
int __cdecl crt_store_dword_02021ca0(int a1)
{
  unk_2021CA0 = a1;
  return a1;
}

