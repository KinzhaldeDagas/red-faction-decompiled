// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006221F6 acmStreamOpen
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete6-byte import thunk: FF25 DWORD absolute indirect TAIL JMP through IAT slot0x00630250. Original RF.exe import directory independently binds slot to
// MSACM32.dll!acmStreamOpen; IDA loader-resolved display name acmStreamOpen retained, ordinal identities not inferred from names. No PUSH/CALL/RET, register/flag assignment, local
// frame, argument read/rewrite, NULL guard, byte-order/network/audio/unwind work in thunk. Existing caller return address/arguments and all live register state transfer directly to
// CURRENT runtime IAT target; imported function owns stack cleanup/results/side effects. Does not cache resolved address locally or call a fixed implementation. Native opcode/operand
// and original PE import lookup/descriptor/IAT membership verified.
// attributes: thunk
MMRESULT __stdcall acmStreamOpen(
        LPHACMSTREAM phas,
        HACMDRIVER had,
        LPWAVEFORMATEX pwfxSrc,
        LPWAVEFORMATEX pwfxDst,
        LPWAVEFILTER pwfltr,
        DWORD_PTR dwCallback,
        DWORD_PTR dwInstance,
        DWORD fdwOpen)
{
  return __imp_acmStreamOpen(phas, had, pwfxSrc, pwfxDst, pwfltr, dwCallback, dwInstance, fdwOpen);
}

