// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048BEB0 rf_mover_construct_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Thiscall mover member constructor, returns receiver. Calls common_object_construct_members, constructs invalid timestampDWORD664=-1, empty DWORD arrays668,680,692,704,716 with
// capacity0, invalid timestampDWORD784=-1. Unwind destroys successfully constructed array backing and common members. Does not initialize next652/prev656,sequence
// byte660,flags792,key indices760/764,motion/audio scalar fields or contained key payloads here; creation path fills these separately. Also invoked statically at62C258 with
// receiver704610 for mover sentinel.
char *__thiscall rf_mover_construct_members(char *this)
{
  rf_common_object_construct_members(this);
  rf_timestamp4_construct_invalid((int *)this + 166);
  rf_dword_array_construct_capacity(this + 668, 0);
  rf_dword_array_construct_capacity(this + 680, 0);
  rf_dword_array_construct_capacity(this + 692, 0);
  rf_dword_array_construct_capacity(this + 704, 0);
  rf_dword_array_construct_capacity(this + 716, 0);
  rf_timestamp4_construct_invalid((int *)this + 196);
  return this;
}

