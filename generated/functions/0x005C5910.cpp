// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C5910 _abs
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one32-bit integer. CDQ sign-extends EAX into EDX then XOR EAX,EDX and SUB EAX,EDX, returning branchless two-complement absolute-value bits. INT_MIN
// remains80000000 after native wrap; no overflow check or errno write. Used by RF D3D8 viewport/client-rectangle code; instruction body is generic integer abs and retains the correct
// CRT name/library classification.
int __cdecl abs(int Number)
{
  return abs32(Number);
}

