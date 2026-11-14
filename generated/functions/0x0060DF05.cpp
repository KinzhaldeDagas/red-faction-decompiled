// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DF05 __load_CW
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Internal CW helper reads DWORD at entryESP+4 (caller-owned saved-CW/scratch slot). EDX=(slot&0x300)|0x7F, store derivedDX into HIGH WORD of SAME slot at
// entryESP+6, FLDCW that word, RET. Preserves original low16 savedCW, does not read a pointer or restore CW. EDX scratch changes, EAX unchanged. Original math callers push a
// scratchDWORD then FNSTCW lowWORD before call; no stack-argument purge. No incoming fpstat/numeric argument.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Native clobber refinement: only EDX GPR modified;
// EAX/ECX/EBX/ESI/EDI and restored ESP untouched. Explicit spoils<edx> prevents fictitious destruction of pow's saved exponent classifier ECX and inverse-trig exponent EAX. Same
// caller-owned CW DWORD read/write and no stack purge; no floating input/output.
void __cdecl __spoils<edx> _load_CW(unsigned int a1)
{
  ;
}

