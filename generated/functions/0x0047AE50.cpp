// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047AE50 rf_rfl_light_serialize_mode
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL header and prelude control flow, legacy light layouts, native ECX/stack arguments, environment initialization and multiplayer room tracking): 
// Thiscall light record, one stack stream pointer, RET4. Invokes int32 serializer with ECX=stream, address receiver+60, minimum version0 and default0. Delegates read/write policy; no
// UID/color/position serialization or renderer update. Returns delegate EAX. Native caller4799B7 traverses light registry6FC3D0 and invokes this for each record.
int __thiscall rf_rfl_light_serialize_mode(char *this, _DWORD *a2)
{
  return rf_binary_stream_serialize_int32(a2, (int *)this + 15, 0, 0);
}

