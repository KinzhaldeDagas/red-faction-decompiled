// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00622178 htonl
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete6-byte import thunk: FF25 DWORD absolute indirect TAIL JMP through IAT slot0x00630364. Original RF.exe import directory independently binds slot to
// WSOCK32.dll!ordinal:8; IDA loader-resolved display name htonl retained, ordinal identities not inferred from names. No PUSH/CALL/RET, register/flag assignment, local frame,
// argument read/rewrite, NULL guard, byte-order/network/audio/unwind work in thunk. Existing caller return address/arguments and all live register state transfer directly to CURRENT
// runtime IAT target; imported function owns stack cleanup/results/side effects. Does not cache resolved address locally or call a fixed implementation. Native opcode/operand and
// original PE import lookup/descriptor/IAT membership verified.
// attributes: thunk
u_long __stdcall htonl(u_long hostlong)
{
  return __imp_htonl(hostlong);
}

