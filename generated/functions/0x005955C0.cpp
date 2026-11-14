// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005955C0 rf_scene_record36_construct_flag1
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, input remapping,text wrapping,Bink playback/default records,archive metadata,projection/aperture/classification and glass submission): Thiscall constructor used by VSFX pool vector allocation at5CCA3B with stride36. Calls no-op vector default on receiver,then ORs DWORD32 with1,preserving other bits. No other bytes initialized; does NOT zero vector,flags or remaining fields. Existing void type retained; no owning allocation/destruction. Raw caller5CCA47 pushes24h stride.
void __thiscall rf_scene_record36_construct_flag1(void *this)
{
  rf_vector3_default_construct_noop(this);
  *((_DWORD *)this + 8) |= 1u;
}

