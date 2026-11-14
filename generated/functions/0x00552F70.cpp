// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00552F70 rf_solid_toggle_or_replace_selected_face
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Recovered thiscall solid,facePointer,toggleByte. Uses pointer-array+216. Nonzero toggle:find first matching index,erase it if present,append if absent. Zero toggle:if absent,clear selection count then append face;IF ALREADY PRESENT,DOES NOTHING and leaves any other selected faces intact. No geometry/ownership changes,face validation or duplicates cleanup. Raw EAX varies index/append-index/erase-helper pointer,not consistent boolean.
unsigned int __thiscall rf_solid_toggle_or_replace_selected_face(void *this, void *a2, unsigned __int8 a3)
{
  unsigned int result; // eax
  int index; // [esp+4h] [ebp-4h]

  if ( a3 )
  {
    index = rf_pointer_array_find_index((_DWORD *)this + 54, (int)a2);
    if ( index < 0 )
      return rf_pointer_array_append_dword((_DWORD *)this + 54, (int)a2);
    else
      return (unsigned int)rf_pointer_array_erase_index_unchecked((_DWORD *)this + 54, index);
  }
  else
  {
    result = rf_pointer_array_find_index((_DWORD *)this + 54, (int)a2);
    if ( (result & 0x80000000) != 0 )
    {
      rf_solid_clear_selected_face_count(this);
      return rf_pointer_array_append_dword((_DWORD *)this + 54, (int)a2);
    }
  }
  return result;
}

