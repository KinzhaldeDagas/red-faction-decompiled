// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050FAB0 rf_object_bind_v3d_or_vfx_model_or_mark_delete
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Copies filename into temporary RFString. Compares complete suffix after LAST dot case-insensitively to literal v3d: match calls4BC000 bind mode1; all other filenames call mode3. Never selects character mode2. If object model DWORD+128 is zero afterward, marks deferred deletion; destroys temporary string. No NULL filename/object guard or directory separator treatment.
void __cdecl rf_object_bind_v3d_or_vfx_model_or_mark_delete(int a1, char *Str)
{
  char *v2; // eax
  char *v3; // eax
  _DWORD v4[2]; // [esp+4h] [ebp-18h] BYREF
  char *last_char_wrapper; // [esp+Ch] [ebp-10h]
  int v6; // [esp+18h] [ebp-4h]

  rf_string_construct_from_cstr(v4, Str);
  v6 = 0;
  last_char_wrapper = rf_cstring_find_last_char_wrapper(Str, 46);
  if ( last_char_wrapper && !_stricmp(last_char_wrapper + 1, off_63F6A0) )
  {
    v2 = (char *)rf_string_object_c_str_or_empty(v4);
    rf_object_bind_model_filename_by_kind(a1, v2, 1);
  }
  else
  {
    v3 = (char *)rf_string_object_c_str_or_empty(v4);
    rf_object_bind_model_filename_by_kind(a1, v3, 3);
  }
  if ( !*(_DWORD *)(a1 + 128) )
    rf_object_mark_for_deferred_delete(a1);
  v6 = -1;
  rf_string_destroy_buffer(v4);
}

