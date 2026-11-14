// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DF4A0 rf_renderer_begin_immediate_buffers
// UNREALRED VERIFIED [extended-clip-20261028]: No-op when world-batching byte0x1E014E6 nonzero. Otherwise flushes prior active immediate batch0x5DF5F0,stores primitive type argument1 at0x1E014C8 and indices-per-primitive divisor argument2 at0x1E014D8. If vertexcursor0x18CCFBC+640>6000 OR indexcursor0x18CCFC0+960>10000,resets both cursors0. Captures basevertex0x1E014F0 and baseindex0x1E014F4. Locks remaining40-byte VBO and16-bit IBO ranges via vtable+44,with flag0x1DAEE08 for nonzero vertexcursor else0x1DAEE04. Output mapped pointers0x1DAEDB8/BC. Clears local vertex/index cursors0x1E014E8/EC,sets immediateactive0x1E014E5=1 even if lock failed. Fixed headroom640vertices/960indices,not caller-specific reservation. No divisor or lock-result validation. Return either batching flag or index-lock result,not reliable success/count.
int __cdecl rf_renderer_begin_immediate_buffers(int a1, int a2)
{
  int result; // eax
  int v3; // [esp+0h] [ebp-Ch]

  result = unk_1E014E6;
  if ( !unk_1E014E6 )
  {
    if ( unk_1E014E5 )
      rf_renderer_flush_immediate_buffers();
    unk_1E014C8 = a1;
    unk_1E014D8 = a2;
    if ( dword_18CCFBC + 640 > 6000 || unk_18CCFC0 + 960 > 10000 )
    {
      dword_18CCFBC = 0;
      unk_18CCFC0 = 0;
    }
    unk_1E014F0 = dword_18CCFBC;
    unk_1E014F4 = unk_18CCFC0;
    if ( dword_18CCFBC )
      v3 = unk_1DAEE08;
    else
      v3 = unk_1DAEE04;
    (*(void (__stdcall **)(_DWORD *, int, int, void *, int))(*dword_1DAEDB0 + 44))(
      dword_1DAEDB0,
      40 * dword_18CCFBC,
      40 * (6000 - dword_18CCFBC),
      &unk_1DAEDB8,
      v3);
    result = (*(int (__stdcall **)(_DWORD *, int, int, void *, int))(*dword_1DAEDB4 + 44))(
               dword_1DAEDB4,
               2 * unk_18CCFC0,
               2 * (10000 - unk_18CCFC0),
               &unk_1DAEDBC,
               v3);
    unk_1E014E8 = 0;
    unk_1E014EC = 0;
    unk_1E014E5 = 1;
  }
  return result;
}

