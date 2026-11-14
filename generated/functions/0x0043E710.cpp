// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043E710 rf_record_transform_color_default_construct_noop
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Thiscall ECX receiver, no stack args, fullEAX=original receiver. Calls no-op vector ctor at+20, no-write
// three-row matrix ctor at+32, then no-op RGBA8 ctor at+72. Therefore writes NO object bytes, including position/orientation/color and surrounding fields. No allocation, NULL/content
// validation, identity/zero initialization, ownership registration or resource creation. Pointer arithmetic and receiver return alone do not prove record contents or live state.
char *__thiscall rf_record_transform_color_default_construct_noop(char *this)
{
  rf_vector3_default_construct_noop(this + 20);
  rf_matrix3_construct(this + 32);
  rf_rgba8_default_construct_noop(this + 72);
  return this;
}

