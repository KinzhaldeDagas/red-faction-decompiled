// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00519FF0 rf_solid_face_allocate_link
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Actual THISCALL ECX solid,one stack pointer to6-DWORD face metadata,RET4. Calls standalone96-byte face allocator with metadata,then appends returned face to receiver list+112,returns face pointer in EAX. Previous stored stdcall(int)->int omitted ECX and hid solid ownership in callers;corrected thiscall/pointer prototype exposes it. No face/allocation NULL check,room attachment,geometry finalization,UV generation or material setup beyond metadata copy.
unsigned int *__thiscall rf_solid_face_allocate_link(void *solid, const unsigned int *metadata)
{
  unsigned int *v4; // [esp+4h] [ebp-4h]

  v4 = rf_geomod_face_allocate(metadata);
  rf_solid_face_list_append((int *)solid + 28, (int)v4);
  return v4;
}

