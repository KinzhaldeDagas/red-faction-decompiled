// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00553020 rf_solid_toggle_or_replace_selection204
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Recovered thiscall solid,pointer,toggleByte;identical policy to552F70 on member array+204. Toggle flips first matching membership;replace clears others ONLY when requested pointer absent. Already-present pointer leaves whole selection unchanged. No pointee-field validation/free;raw EAX mixed index/erase-result,not uniform status. Original collection element role unproven.
unsigned int __thiscall rf_solid_toggle_or_replace_selection204(void *this, void *a2, unsigned __int8 a3)
{
  unsigned int result; // eax
  int index; // [esp+4h] [ebp-4h]

  if ( a3 )
  {
    index = rf_pointer_array_find_index((_DWORD *)this + 51, (int)a2);
    if ( index < 0 )
      return rf_pointer_array_append_dword((_DWORD *)this + 51, (int)a2);
    else
      return (unsigned int)rf_pointer_array_erase_index_unchecked((_DWORD *)this + 51, index);
  }
  else
  {
    result = rf_pointer_array_find_index((_DWORD *)this + 51, (int)a2);
    if ( (result & 0x80000000) != 0 )
    {
      rf_solid_clear_selection204_count(this);
      return rf_pointer_array_append_dword((_DWORD *)this + 51, (int)a2);
    }
  }
  return result;
}

