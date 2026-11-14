// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006119BE __unlock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl signed/raw lock index. Read pointer at critical-section table +index*8,call LeaveCriticalSection(pointer) via stdcall. No
// range/sign/initialization/NULL/owner check or wrapper lock allocation. Native index arithmetic32-bit, one pointer loaded from each8-byte table record; result unspecified, no
// success status.
void __cdecl _unlock(int a1)
{
  LeaveCriticalSection(*(&lpCriticalSection + 2 * a1));
}

