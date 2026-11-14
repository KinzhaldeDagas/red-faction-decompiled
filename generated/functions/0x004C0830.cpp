// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C0830 rf_bolt_emitter_construct_from_descriptor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, four-slot emitter lifecycle, allocation and constructor layouts, native ordered lifetime gates, attachment transforms and paused rendering): 
// Thiscall emitter,attachmentHandle,savedGateIdentifier,descriptor,activeBYTE; RET16 returns receiver. Initializes four68B slot subobjects at112 via4C14D0 and timestamp384=-1; vector
// defaults16/28/40/52 and RGBA104 are NOOP constructors, later authored copies supply their values. Stores attachment handle4, saved ID8, descriptor DWORD0 into emitter0, and second
// attachment12=-1. Copies descriptor vec3 at4/16/28/40 to emitter16/28/40/52. Caches F32 lengths of emitter28 and52 at388/392. Copies descriptor floats52/56/60/64/68/72 to
// emitter64/68/72/76/80/84, DWORDs80/84/88/92 to emitter92/96/100/104, active BYTE to88, room108=NULL. Padding89..91 not explicitly initialized.
// Allocates four curve/point sets4C0630 using descriptor signed count76. If flags92&1, calls try-spawn4C0340 immediately regardless active BYTE; global/saved-ID rejection can leave
// timestamp invalid. Otherwise arms timestamp384 from trunc(random[emitter68,72]*1000) even if inactive. Descriptor requires at least96B; no null, range, attachment-resolution, room
// refresh or allocation-success checks. Slots initially life0; immediate spawn does not fill interior curve controls/point arrays. Cleanup on constructor exception destroys embedded
// slot arrays; no normal outer allocation/free here.
char *__thiscall rf_bolt_emitter_construct_from_descriptor(char *this, int a2, int a3, int a4, char a5)
{
  double v5; // st7
  float v8[3]; // [esp+10h] [ebp-3Ch] BYREF
  float v9[3]; // [esp+1Ch] [ebp-30h] BYREF
  float v10[3]; // [esp+28h] [ebp-24h] BYREF
  float copy_result[6]; // [esp+34h] [ebp-18h] BYREF

  rf_vector3_default_construct_noop(this + 16);
  rf_vector3_default_construct_noop(this + 28);
  rf_vector3_default_construct_noop(this + 40);
  rf_vector3_default_construct_noop(this + 52);
  rf_rgba8_default_construct_noop(this + 104);
  `eh vector constructor iterator'(
    this + 112,
    0x44u,
    4,
    (void (__thiscall *)(void *))rf_bolt_emitter_slot_construct,
    (void (__thiscall *)(void *))rf_bolt_emitter_slot_destroy_array);
  copy_result[5] = 0.0;
  rf_timestamp4_construct_invalid((int *)this + 96);
  *((_DWORD *)this + 1) = a2;
  *((_DWORD *)this + 2) = a3;
  *(_DWORD *)this = *(_DWORD *)a4;
  rf_vector_copy((float *)this + 4, copy_result, (const float *)(a4 + 4));
  rf_vector_copy((float *)this + 7, v10, (const float *)(a4 + 16));
  *((float *)this + 97) = rf_vector3_length((float *)this + 7);
  rf_vector_copy((float *)this + 10, v9, (const float *)(a4 + 28));
  rf_vector_copy((float *)this + 13, v8, (const float *)(a4 + 40));
  *((float *)this + 98) = rf_vector3_length((float *)this + 13);
  *((float *)this + 16) = *(float *)(a4 + 52);
  *((float *)this + 17) = *(float *)(a4 + 56);
  *((float *)this + 18) = *(float *)(a4 + 60);
  *((float *)this + 19) = *(float *)(a4 + 64);
  *((float *)this + 20) = *(float *)(a4 + 68);
  *((float *)this + 21) = *(float *)(a4 + 72);
  *((_DWORD *)this + 23) = *(_DWORD *)(a4 + 80);
  *((_DWORD *)this + 24) = *(_DWORD *)(a4 + 84);
  *((_DWORD *)this + 25) = *(_DWORD *)(a4 + 88);
  *((_DWORD *)this + 26) = *(_DWORD *)(a4 + 92);
  *(this + 88) = a5;
  *((_DWORD *)this + 27) = 0;
  *((_DWORD *)this + 3) = -1;
  rf_bolt_emitter_allocate_four_slot_geometry((float *)this, *(_DWORD *)(a4 + 76));
  if ( (*((_DWORD *)this + 23) & 1) != 0 )
  {
    rf_bolt_emitter_try_spawn_and_rearm((int)this);
  }
  else
  {
    v5 = rf_random_float_range(*((float *)this + 17), *((float *)this + 18)) * 1000.0;
    rf_replicator_arm_milliseconds((int *)this + 96, (int)v5);
  }
  return this;
}

