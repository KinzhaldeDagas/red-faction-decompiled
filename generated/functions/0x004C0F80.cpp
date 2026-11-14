// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C0F80 rf_bolt_emitter_set_authored_control_offsets
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, four-slot emitter lifecycle, allocation and constructor layouts, native ordered lifetime gates, attachment transforms and paused rendering): 
// Recovered original93B code body4C0F80..4C0FDD. Thiscall receiver,two const vec3 pointers RET8. Copies first source into emitter28, computes its length and stores binary32 at388,
// then copies second source into emitter52 and caches length392. Sequential copy order matters if sources alias destination storage; no snapshot of both inputs. No normalization,
// flags/slot drift/control/point mutation, timer rearm, immediate respawn, attachment/room update or pointer/finite validation. Existing slots use their existing offsets; later spawn
// uses new authored vectors/lengths. No direct code xrefs currently present; recovered code/prototype is not a claim of runtime use.
void __thiscall rf_bolt_emitter_set_authored_control_offsets(void *this, const float *a, const float *b)
{
  float v4[3]; // [esp+4h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-Ch] BYREF

  rf_vector_copy((float *)this + 7, copy_result, a);
  *((float *)this + 97) = rf_vector3_length((float *)this + 7);
  rf_vector_copy((float *)this + 13, v4, b);
  *((float *)this + 98) = rf_vector3_length((float *)this + 13);
}

