// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536740 rf_lightmap_descriptor124_construct_register
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): Thiscall descriptor,solid/world receiver. Initializes record16-array header at+32 with capacity0;calls NO-OP vector defaults at52,64,76,84 and vector-prefix108. Writes cached handleDWORD4=FFFFFFFF,flagsBYTE8=0,indexDWORD0=current count of receiver array+192,then appends receiver pointer to that array. Returns descriptor;used with124-byte allocations. Does NOT initialize tile origin/dimensions,page pointer,mapping,density,room index or bytes9/10;configuration fills them later. Registration happens before configuration;indexDWORD may exceed later faceWORD range,unchecked.
int *__thiscall rf_lightmap_descriptor124_construct_register(int *this, int a2)
{
  rf_record16_array_construct_capacity(this + 8, 0);
  rf_vector3_default_construct_noop(this + 13);
  rf_vector3_default_construct_noop(this + 16);
  rf_vector3_default_construct_noop(this + 19);
  rf_vector3_default_construct_noop(this + 21);
  rf_vector_prefix_construct_noop(this + 27);
  *(this + 1) = -1;
  *((_BYTE *)this + 8) = 0;
  *this = rf_receiver_get_first_dword((void *)(a2 + 192));
  rf_pointer_array_append_dword((_DWORD *)(a2 + 192), (int)this);
  return this;
}

