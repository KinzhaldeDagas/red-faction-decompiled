// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054CC10 rf_world_packet_face28_assign
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, complete world packet pass, room packet builder, BSP collection, draw order, buffer limits and original PE bytes): Thiscall destination28-byte face record,source. Copies countWORD0,DWORD indexPointer4,plane4floats8..23,tailDWORD24 twice (duplicate identical store in original). Bytes2..3 padding untouched;no deep copy,allocation,normalization or index rewrite. Returns destination.
void *__thiscall rf_world_packet_face28_assign(void *this, int a2)
{
  *(_WORD *)this = *(_WORD *)a2;
  *((_DWORD *)this + 1) = *(_DWORD *)(a2 + 4);
  rf_plane_copy((float *)this + 2, (float *)(a2 + 8));
  *((_DWORD *)this + 6) = *(_DWORD *)(a2 + 24);
  *((_DWORD *)this + 6) = *(_DWORD *)(a2 + 24);
  return this;
}

