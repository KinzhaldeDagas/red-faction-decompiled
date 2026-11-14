// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605DDF __CreateFrameInfo
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(two-DWORD caller record*,raw exceptionObject
// pointer), return original record address. Write record[0]=object, call getptd, copy DWORD PTD+98h into record[1], call getptd AGAIN, write second PTD+98h=record. Thread-owned
// singly linked frame-info push, no allocation/copy of exception object, reference count, lock or NULL validation. Two provider fetches are genuinely separate; do not assume cached
// PTD identity. Preserve ESI. CallCatchBlock passes address of its local record and exceptionRecord+18h object pointer; return becomes later unlink argument.
_DWORD *__cdecl _CreateFrameInfo(_DWORD *a1, int a2)
{
  *a1 = a2;
  a1[1] = _getptd()[38];
  _getptd()[38] = (DWORD)a1;
  return a1;
}

