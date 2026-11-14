// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00519240 rf_solid888_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Thiscall constructor used with888-byte allocations;returns receiver. Calls no-op vector defaults72,84,100,848. Clears2-DWORD face-list112/116. Constructs dynamic DWORD-array headers at120,132,144,156,168,180,192,204,216,228 with capacity0;756 capacity0;768 via zero-capacity wrapper51E910;864 with capacity32. At240 calls51EBE0,count-only initializer,not whole embedded region clear. Then release-storage helpers144,168,156,132,180;writes DWORD884=0,BYTE4=0,DWORD68=0,resets face-list112/116, DWORD880=0,float844=0,DWORD0=0,DWORD860=0,DWORD876=0. No vtable install or whole888-byte memset;remaining bytes depend on member constructors/prior storage. Bounds vectors72/84 and
// center100 stay uninitialized because defaults no-op. Allocation belongs to caller,no common NULL recovery.
void **__thiscall rf_solid888_construct(void **this)
{
  rf_vector3_default_construct_noop(this + 18);
  rf_vector3_default_construct_noop(this + 21);
  rf_vector3_default_construct_noop(this + 25);
  rf_two_dword_construct_zero_413790(this + 28);
  rf_dword_array_construct_capacity(this + 30, 0);
  rf_dword_array_construct_capacity(this + 33, 0);
  rf_dword_array_construct_capacity(this + 36, 0);
  rf_dword_array_construct_capacity(this + 39, 0);
  rf_dword_array_construct_capacity(this + 42, 0);
  rf_dword_array_construct_capacity(this + 45, 0);
  rf_dword_array_construct_capacity(this + 48, 0);
  rf_dword_array_construct_capacity(this + 51, 0);
  rf_dword_array_construct_capacity(this + 54, 0);
  rf_dword_array_construct_capacity(this + 57, 0);
  rf_embedded_array_construct_count_only_51ebe0(this + 60);
  rf_dword_array_construct_capacity(this + 189, 0);
  rf_dword_array_construct_zero_capacity_51e910(this + 192);
  rf_vector3_default_construct_noop(this + 212);
  rf_dword_array_construct_capacity(this + 216, 32);
  rf_pointer_array_release_storage(this + 36);
  rf_pointer_array_release_storage(this + 42);
  rf_pointer_array_release_storage(this + 39);
  *(this + 221) = nullptr;
  *((_BYTE *)this + 4) = 0;
  *(this + 17) = nullptr;
  rf_intrusive_list_reset_head_tail(this + 28);
  *(this + 220) = nullptr;
  rf_pointer_array_release_storage(this + 33);
  rf_pointer_array_release_storage(this + 45);
  *((float *)this + 211) = 0.0;
  *this = nullptr;
  *(this + 215) = nullptr;
  *(this + 219) = nullptr;
  return this;
}

