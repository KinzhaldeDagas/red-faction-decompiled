// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061AB6E __unlock_fhandle
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl rawfiledescriptor. Compute table index ARITHMETIC(fd>>5),load block pointer2021E40[index],add ((fd&31)<<6)+12,call LeaveCriticalSection.
// Signed-negative values are not rejected and may index beforetable; no range/blockNULL/ownership test. No lock-file structure allocation or fd normalization; raw shift/address
// arithmetic preserved.
void __cdecl _unlock_fhandle(int a1)
{
  LeaveCriticalSection((LPCRITICAL_SECTION)(unk_2021E40[a1 >> 5] + ((a1 & 0x1F) << 6) + 12));
}

