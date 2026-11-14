// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486BE0 rf_material_custom_sound_set_scalar_delete
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Thiscall scalar deleting destructor, stack flags RET4. Invokes set destructor486C10; if flags bit0 set raw operator delete(receiver); returns original receiver even when freed.
// Other flag bits ignored. No registry unlinking, sound-resource release or per-handle deletion.
_DWORD *__thiscall rf_material_custom_sound_set_scalar_delete(_DWORD *this, char a2)
{
  rf_material_custom_sound_set_destroy(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

