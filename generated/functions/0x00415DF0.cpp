// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00415DF0 rf_clutter_apply_named_skin
// UNREALRED VERIFIED [switch-clutter-reset] Finds a class skin name case-insensitively, applies its loaded skin handle to matching render instances, applies positional texture names to the live model, and returns the ordered skin index or -1.
int __cdecl rf_clutter_apply_named_skin(_DWORD *a1, char *String2)
{
  int v2; // eax
  int *v3; // eax
  int v4; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1[165] + 200)); ++i )
  {
    v2 = rf_clutter_skin_record_at_index((_DWORD *)(a1[165] + 200), i);
    if ( rf_string_equals_case_insensitive(v2, String2) )
    {
      if ( *(int *)sub_552200((_DWORD *)(a1[165] + 212), i) > -1 )
      {
        v3 = (int *)sub_552200((_DWORD *)(a1[165] + 212), i);
        rf_render_instances_set_skin_handle_for_uid(a1[11], *v3);
      }
      break;
    }
  }
  if ( i >= rf_receiver_get_first_dword((void *)(a1[165] + 200)) )
    return -1;
  v4 = rf_clutter_skin_record_at_index((_DWORD *)(a1[165] + 200), i);
  rf_model_apply_skin_texture_names(a1[32], v4);
  return i;
}

