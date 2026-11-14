// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00483C80 rf_cutscene_sequence2144_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL region-version layouts, cutscene stream ABI and count bounds, constructor/destructor ownership and debris descriptor bits): 
// Thiscall2144-byte sequence constructor, returns receiver. Constructs64 embedded32-byte segments starting8 with segment ctor483D30 and string-destructor callback. Initializes three
// timestamp DWORDs+2064,+2068,+2072 to-1. Calls no-op vector2084 and matrix2096 constructors. Does not initialize sequence id0,count4,other segment scalar fields, runtime
// gaps2056..2063/2076..2083,byte2137,FOV2140 or other runtime state. Loader explicitly assigns id/count/versioned flags/FOV. Constructor unwind destroys64 segment strings; no
// whole-buffer zeroing.
char *__thiscall rf_cutscene_sequence2144_construct(char *this)
{
  `eh vector constructor iterator'(
    this + 8,
    0x20u,
    64,
    (void (__thiscall *)(void *))rf_cutscene_segment32_construct_string,
    (void (__thiscall *)(void *))rf_cutscene_segment_destroy_string);
  rf_timestamp4_construct_invalid((int *)this + 516);
  rf_timestamp4_construct_invalid((int *)this + 517);
  rf_timestamp4_construct_invalid((int *)this + 518);
  rf_vector3_default_construct_noop(this + 2084);
  rf_matrix3_construct(this + 2096);
  return this;
}

