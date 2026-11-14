// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C92E0 rf_scene_material_index_context24_construct_zero
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VSFX header/version gates, pool ownership/cursors, FourCC dispatch, normal error cleanup and model postprocessing): Thiscall24-byte read context. Sets six DWORDs0..20 to0 and returns receiver. VSFX loader wires three pairs(shared-counter pointer,pool pointer) for DWORD index pools at scene148/156/164 and passes it to MATL material reader. No allocation, ownership, bounds or vtable; local destructor5C9330 is no-op.
_DWORD *__thiscall rf_scene_material_index_context24_construct_zero(_DWORD *this)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  return this;
}

