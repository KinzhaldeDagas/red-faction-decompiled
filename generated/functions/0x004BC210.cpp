// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BC210 rf_object_set_room_and_cache_position
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, object room/attachment ownership, shape-based ground lighting, native dispatcher table and resolver/view distinctions): Thiscall common receiver plus one room-pointer DWORD,RET4. First copies common position+60 into cached position+4, then writes room pointer DWORD0 and returns supplied room bits. Does not resolve geometry, test liquid/audio environment, publish physics position or alter dirty flags. No null/room validity guard.
// [UnrealRed combat room owner 2026-11-12; verified original-byte ASM] This is the ctor/explicit room setter: copies current3C to cached4 even when supplied roomNULL, then storesroom0; no lookup/dirty/audio. Do not invent initialNULL for a born native body: common4B7E00 obtains/respects its room before this call, SP type0 missing lookup aborts creation.
int __thiscall rf_object_set_room_and_cache_position(float *this, int a2)
{
  float copy_result[3]; // [esp+4h] [ebp-Ch] BYREF

  rf_vector_copy(this + 1, copy_result, this + 15);
  *(_DWORD *)this = a2;
  return a2;
}

