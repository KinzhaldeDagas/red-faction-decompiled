// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539990 rf_uv_scroll_descriptor_step_cached_faces
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Multiplies descriptor velocityU/V by caller delta,reads cached member array count once,then for each stored face pointer calls539A10 to translate PRIMARY corner UVs and rebase face-average domain. Returns initial cached count at loop exit;no status aggregation,key lookup,time accumulation or list refresh. Does not invalidate room render packets or apply modulo per corner itself.
int __thiscall rf_uv_scroll_descriptor_step_cached_faces(float *this, float a2)
{
  int result; // eax
  _DWORD **v3; // eax
  int first_dword; // [esp+Ch] [ebp-10h]
  float v6; // [esp+10h] [ebp-Ch]
  float v7; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  v6 = *(this + 1) * a2;
  v7 = *(this + 2) * a2;
  first_dword = rf_receiver_get_first_dword(this + 3);
  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= first_dword )
      break;
    v3 = (_DWORD **)sub_552200((_DWORD *)this + 3, i);
    rf_face_translate_primary_uv_and_rebase(*v3, v6, v7);
  }
  return result;
}

