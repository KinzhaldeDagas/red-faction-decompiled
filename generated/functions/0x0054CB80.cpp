// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054CB80 rf_world_packet_face28_copy_54cb80
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Thiscall destination,source pointer,RET4;returns destination. Copies source WORD0,float4,plane4-floats8..23 via plane copy helper,then scalar float24 TWICE. Padding bytes2..3 untouched;no write beyond27. Packet-group reorder caller indexes28-byte records,confirming record stride. Does not copy padding or normalize plane;duplicate scalar store is present in original code. Corrected integer source to pointer and result/receiver to generic record pointers;physical stack/ECX ABI unchanged.
void *__thiscall rf_world_packet_face28_copy_54cb80(void *destination, const void *source)
{
  *(_WORD *)destination = *(_WORD *)source;
  *((_DWORD *)destination + 1) = *((_DWORD *)source + 1);
  rf_plane4_copy_normal_scalar((float *)destination + 2, (float *)source + 2);
  *((_DWORD *)destination + 6) = *((_DWORD *)source + 6);
  *((_DWORD *)destination + 6) = *((_DWORD *)source + 6);
  return destination;
}

