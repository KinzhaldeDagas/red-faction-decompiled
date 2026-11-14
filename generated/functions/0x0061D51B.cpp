// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D51B crt_clear_dword_02021e1c
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Eight native bytes AND DWORD2021E1C,0; RET. Always zeroes exactly that global DWORD, modifies arithmetic flags and does not explicitly assign EAX. No
// argument read, helper/callback invocation, old-value return or surrounding-state reset.
void crt_clear_dword_02021e1c()
{
  unk_2021E1C = 0;
}

