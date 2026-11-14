// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A280 rf_level_runtime_state_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Thiscall global runtime-state constructor; static initializer62BED0 passes receiver6FC310, destructor registered at62EF40 uses same address. Constructs RFStrings at4,12,20,28,156;
// six initially empty DWORD vectors at168,180,192,204,216,228; managed particle-effect circular sentinel at240. That delegate initializes32-byte sentinel, not all storage through
// next member292. Calls no-op RGBA48/52, matrix80/116/304 and vector292 constructors. Returns receiver. Other scalar/pointer fields and gaps are not zeroed by this body. Exception
// cleanup destroys successfully constructed owned members.
char *__thiscall rf_level_runtime_state_construct(char *this)
{
  rf_string_construct_empty((_DWORD *)this + 1);
  rf_string_construct_empty((_DWORD *)this + 3);
  rf_string_construct_empty((_DWORD *)this + 5);
  rf_string_construct_empty((_DWORD *)this + 7);
  rf_rgba8_default_construct_noop(this + 48);
  rf_rgba8_default_construct_noop(this + 52);
  rf_matrix3_construct(this + 80);
  rf_matrix3_construct(this + 116);
  rf_string_construct_empty((_DWORD *)this + 39);
  rf_dword_array_construct_capacity(this + 168, 0);
  rf_dword_array_construct_capacity(this + 180, 0);
  rf_dword_array_construct_capacity(this + 192, 0);
  rf_dword_array_construct_capacity(this + 204, 0);
  rf_dword_array_construct_capacity(this + 216, 0);
  rf_dword_array_construct_capacity(this + 228, 0);
  rf_managed_particle_effect_list_construct((_DWORD *)this + 60);
  rf_vector3_default_construct_noop(this + 292);
  rf_matrix3_construct(this + 304);
  return this;
}

