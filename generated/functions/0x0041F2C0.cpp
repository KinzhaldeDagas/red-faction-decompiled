// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041F2C0 rf_corpse_runtime_construct_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Thiscall corpse, no stack args. Common-object member constructor then empty RFString676/680, invalid timestamp684=-1, NO-WRITE color728 constructor and NO-WRITE embedded vector/matrix constructor732. Returns receiver. Effective writes are common string24/28,physics array header388/392/396,state string676/680,timestamp684. Does not initialize pose,shadow packet,color,flags668,creation660/fade664,model712,item716,effect720 or voice724; factories/restorers must provide represented fields. No outer allocation or whole-object zeroing.
int __thiscall rf_corpse_runtime_construct_members(int this)
{
  rf_common_object_construct_members((char *)this);
  rf_string_construct_empty((_DWORD *)(this + 676));
  rf_timestamp4_construct_invalid((int *)(this + 684));
  rf_rgba8_default_construct_noop((void *)(this + 728));
  rf_embedded_vector12_matrix24_construct_noop((char *)(this + 732));
  return this;
}

