// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486C10 rf_material_custom_sound_set_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Thiscall212-byte set destructor. Assigns empty original C string0x6392E5 to RFString at+204, then destroys that string buffer. Unwind path also destroys the string. Does not
// reset/delete embedded40 sound ids at0..159, ten counts160..199, all-mode BYTE200, padding201..203, or containing allocation. No backend sound unload; scalar deleting wrapper
// performs optional raw free separately.
void __thiscall rf_material_custom_sound_set_destroy(_DWORD *this)
{
  rf_string_assign_from_cstr(this + 51, (char *)byte_6392E5);
  rf_string_destroy_buffer(this + 51);
}

