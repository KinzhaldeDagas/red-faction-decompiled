// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CED90 rf_scene_vector_key40_construct_from_global_affine
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): No-argument wrapper calls5CEDB0(receiver,0,address17F10BC) and forwards receiver pointer bits. The referenced global is treated as12-float affine template;actual dynamic contents not inferred. No zeroing/allocation inside wrapper.
int __thiscall rf_scene_vector_key40_construct_from_global_affine(void *this)
{
  return rf_scene_vector_key40_construct_from_affine((int)this, 0, (int)&unk_17F10BC);
}

