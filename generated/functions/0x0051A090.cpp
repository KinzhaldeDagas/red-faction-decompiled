// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051A090 rf_solid_face_remove_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Thiscall solid,face,low BYTE flag,RET8. ONLY when flag0:if selected-vertex array204 count>0,walks face corners and removes first matching vertex pointer from that SELECTION array;then removes first matching face pointer from selected-face array216. Any nonzero flag skips both selection cleanups. Unconditionally unlinks face from solid face list112 and calls530650 pooled face/corner cleanup. No direct removal from solid vertex array120 or vertex destruction in this wrapper. Reused sphere-ring vertices remain available to side faces. Does not finalize bounds,UVs,room tree or validate pointers/cycles. EAX is destructor-helper result,not success status. Earlier
// repeatable solid/spatial-index wording corrected to exact selection-array operations.
int __thiscall rf_solid_face_remove_destroy(int *this, _DWORD *a2, char a3)
{
  int *v4; // [esp+0h] [ebp-10h]
  int *i; // [esp+8h] [ebp-8h]
  int index; // [esp+Ch] [ebp-4h]
  int v8; // [esp+Ch] [ebp-4h]

  if ( !a3 )
  {
    if ( rf_receiver_get_first_dword(this + 51) > 0 )
    {
      for ( i = (int *)a2[16]; i; i = v4 )
      {
        index = rf_pointer_array_find_index(this + 51, *i);
        if ( index >= 0 )
          rf_pointer_array_erase_index_unchecked(this + 51, index);
        if ( i[5] == a2[16] )
          v4 = nullptr;
        else
          v4 = (int *)i[5];
      }
    }
    v8 = rf_pointer_array_find_index(this + 54, (int)a2);
    if ( v8 >= 0 )
      rf_pointer_array_erase_index_unchecked(this + 54, v8);
  }
  rf_solid_face_list_remove(this + 28, (int)a2);
  return rf_geomod_face_destroy(a2);
}

