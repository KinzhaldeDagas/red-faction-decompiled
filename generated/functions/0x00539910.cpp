// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539910 rf_uv_scroll_descriptor_construct_invalid
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Thiscall24-byte UV-scroll descriptor. Initializes DWORD-array header(count,capacity,backing) at+12 with initial capacity0,sets float velocities+4/+8=0,and INTEGER key DWORD0=FFFFFFFF using MOV at539937. Old float* receiver rendered this marker as NaN;prototype corrected to opaque pointer to preserve integer interpretation. Returns receiver. No face list allocation or whole-object float initialization.
void *__thiscall rf_uv_scroll_descriptor_construct_invalid(void *this)
{
  rf_dword_array_construct_capacity((char *)this + 12, 0);
  *((float *)this + 1) = 0.0;
  *((float *)this + 2) = 0.0;
  *(_DWORD *)this = -1;
  return this;
}

