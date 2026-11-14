// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00515AB0 rf_room460_construct_register
// UNREALRED VERIFIED [trigger-airlock-20261022] Room construction separates outside byte+66, authored airlock byte+67, and runtime pressure byte+68. Portal adjacency is list+48, separate from room visibility links. Pressure initialization follows level setup.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Thiscall room,solid,boundsMin3f,boundsMax3f,RET12;returns room. Caller supplies460-byte allocation. Initializes no-op vectors8/20,2-DWORD list40/44,capacity0 arrays48/108,no-op vector-prefix124,count-only embedded member156,no-op RGBA70/396,capacity32 array444. Releases array storage48/108,clears count156 again. Copies bounds to8/20. Stores BYTES0/1/2/64/65/66/69/74/106/388=0;BYTE68=1,BYTE152=1,BYTE428=1. BYTE67 authored-airlock field is NOT initialized here;RGBA70..73 also left untouched by no-op constructor. DWORD36 receives global663AF4 then counter decrements.
// DWORD140/144/404/408=-1;FLOAT148=-1,FLOAT392=0,FLOAT400=128,FLOAT420=floatpi;DWORD384=1,DWORD412/416=32,DWORD424=60(written twice),DWORD432=0. RGBA396 set90,95,152,255. IndexDWORD32=current count of solid room array144;appends room pointer to solid arrays144 AND156. Final DWORD60(tree root),456 and4=0. Does not initialize whole record,all flags/padding or other defaults;does not create face tree or attach faces itself. No room/solid/bounds/array success or counter-range validation. Corrected source bounds arguments and returned/receiver pointers while preserving ECX plus3 stack DWORD ABI. Existing airlock/outside/pressure note retained.
// [UnrealRed combat room owner 2026-11-12; verified original-byte ASM] Room constructor appends to solid144(all authored) AND156(ordinary), initializes detailBYTE0 and runtimeBYTE64 to0, but does NOT initialize352/353/356/clip364..376. Initial352 cannot be assumed zero from this ctor; a first clear/render or allocator/init writer must be established. Serialized outside flag targets66, not64.
void *__thiscall rf_room460_construct_register(
        void *room,
        void *solid,
        const float *bounds_min,
        const float *bounds_max)
{
  _BYTE v6[4]; // [esp+8h] [ebp-28h] BYREF
  float v7[3]; // [esp+Ch] [ebp-24h] BYREF
  float copy_result[6]; // [esp+18h] [ebp-18h] BYREF

  rf_vector3_default_construct_noop((char *)room + 8);
  rf_vector3_default_construct_noop((char *)room + 20);
  rf_two_dword_construct_zero_413790((_DWORD *)room + 10);
  rf_dword_array_construct_capacity((char *)room + 48, 0);
  LODWORD(copy_result[5]) = 3;
  rf_rgba8_default_construct_noop((char *)room + 70);
  rf_dword_array_construct_capacity((char *)room + 108, 0);
  rf_vector_prefix_construct_noop((char *)room + 124);
  rf_embedded_array_construct_count_only_51ebe0((_DWORD *)room + 39);
  rf_rgba8_default_construct_noop((char *)room + 396);
  rf_dword_array_construct_capacity((char *)room + 444, 32);
  rf_pointer_array_release_storage((void **)room + 12);
  rf_pointer_array_clear_count_keep_storage((_DWORD *)room + 39);
  rf_pointer_array_release_storage((void **)room + 27);
  rf_vector_copy((float *)room + 2, copy_result, bounds_min);
  rf_vector_copy((float *)room + 5, v7, bounds_max);
  *((_BYTE *)room + 1) = 0;
  *((_BYTE *)room + 64) = 0;
  *((_BYTE *)room + 388) = 0;
  *((_DWORD *)room + 106) = 60;
  *((_BYTE *)room + 65) = 0;
  *((_BYTE *)room + 66) = 0;
  *((_BYTE *)room + 68) = 1;
  *((_DWORD *)room + 9) = dword_663AF4--;
  *((_DWORD *)room + 35) = -1;
  *((_DWORD *)room + 36) = -1;
  *(_BYTE *)room = 0;
  *((_BYTE *)room + 106) = 0;
  *((_BYTE *)room + 69) = 0;
  *((float *)room + 37) = -1.0;
  *((_BYTE *)room + 152) = 1;
  *((_BYTE *)room + 2) = 0;
  *((_BYTE *)room + 74) = 0;
  *((_DWORD *)room + 106) = 60;
  *((float *)room + 105) = 3.1415927;
  *((_DWORD *)room + 99) = *(_DWORD *)rf_rgba8_construct_components_return_self(v6, 90, 95, 152, 255);
  *((float *)room + 98) = 0.0;
  *((_BYTE *)room + 428) = 1;
  *((_DWORD *)room + 103) = 32;
  *((_DWORD *)room + 104) = 32;
  *((_DWORD *)room + 101) = -1;
  *((_DWORD *)room + 96) = 1;
  *((float *)room + 100) = 128.0;
  *((_DWORD *)room + 108) = 0;
  *((_DWORD *)room + 102) = -1;
  *((_DWORD *)room + 8) = rf_receiver_get_first_dword((char *)solid + 144);
  rf_pointer_array_append_dword((_DWORD *)solid + 36, (int)room);
  rf_pointer_array_append_dword((_DWORD *)solid + 39, (int)room);
  *((_DWORD *)room + 15) = 0;
  *((_DWORD *)room + 114) = 0;
  *((_DWORD *)room + 1) = 0;
  return room;
}

