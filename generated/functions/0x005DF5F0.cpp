// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DF5F0 rf_renderer_flush_immediate_buffers
// UNREALRED VERIFIED [extended-clip-20261028]: Operates only if immediateactive0x1E014E5 and worldbatching0x1E014E6 clear. Clears active byte before unlocking VBO0x1DAEDB0 and IBO0x1DAEDB4 via vtable+48. Adds local index count0x1E014EC to global indexcursor0x18CCFC0. If differs from captured baseindex0x1E014F4,submits device vtable+284 indexed draw with primitive type0x1E014C8,basevertex0x1E014F0,vertexcount=currentvertexcursor-basevertex,startindex=baseindex,primitivecount=(currentindexcursor-baseindex)/divisor0x1E014D8. Vertex cursor was advanced by append routines,not here. No divisor0 or unlock/draw failure checks. Does not clear local counts/reset cursors afterward. Return active flag,unlock or draw result depending path,not primitive count.
int rf_renderer_flush_immediate_buffers()
{
  int result; // eax

  result = unk_1E014E5;
  if ( unk_1E014E5 && !unk_1E014E6 )
  {
    unk_1E014E5 = 0;
    (*(void (__thiscall **)(_DWORD *, _DWORD *))(*dword_1DAEDB0 + 48))(dword_1DAEDB0, dword_1DAEDB0);
    result = (*(int (__stdcall **)(_DWORD *))(*dword_1DAEDB4 + 48))(dword_1DAEDB4);
    unk_18CCFC0 += unk_1E014EC;
    if ( unk_18CCFC0 != unk_1E014F4 )
      return (*(int (__stdcall **)(int, _DWORD, _DWORD, int, _DWORD, int))(*(_DWORD *)dword_1DAEDC4 + 284))(
               dword_1DAEDC4,
               unk_1E014C8,
               unk_1E014F0,
               dword_18CCFBC - unk_1E014F0,
               unk_1E014F4,
               (unk_18CCFC0 - unk_1E014F4) / unk_1E014D8);
  }
  return result;
}

