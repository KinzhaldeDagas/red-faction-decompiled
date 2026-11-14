// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00587260 rf_character_instance_find_or_add_action_record
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Returns index of existing12-byte action record with exact animation index, else if count+4816<16 increments count and initializes new index/time/weight at+4820/+4824/+4828. Resolves clip via base+3932+4*animationIndex; if no raw buffer, attempts raw-file load then rechecks. Successful buffer acquires reference+116 through5BA400. NULL clip/load failure returns-1 WITHOUT rolling back the appended count/record, so later lookup can return that failed record. Full capacity returns-1; no animation index/base-pointer validation.
// UNREALRED VERIFIED [original-goto-idle-20261112]: Direct writes in this allocator are confined to the receiver model action-record count/index/time/weight. The record is appended before clip/raw-buffer validation, and load failure returns-1 without removing it. Raw-file loading and reference helpers are called; this is not a claim that every transitive IO helper lacks callbacks or other global effects.
int __thiscall rf_character_instance_find_or_add_action_record(float *this, int a2)
{
  char *v4; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]
  int j; // [esp+8h] [ebp-4h]
  int v7; // [esp+8h] [ebp-4h]

  for ( i = 0; i < *((_DWORD *)this + 1204); ++i )
  {
    if ( *((_DWORD *)this + 3 * i + 1205) == a2 )
      return i;
  }
  if ( *((int *)this + 1204) < 16 )
  {
    v7 = *((_DWORD *)this + 1204);
    *((_DWORD *)this + 1204) = v7 + 1;
    *((_DWORD *)this + 3 * v7 + 1205) = a2;
    *(this + 3 * v7 + 1207) = 0.0;
    *(this + 3 * v7 + 1206) = 0.0;
    v4 = *(char **)(*((_DWORD *)this + 1876) + 4 * a2 + 3932);
    if ( v4 )
    {
      if ( rf_animation_clip_has_raw_buffer(v4)
        || (rf_rfa_load_raw_file(v4, nullptr), rf_animation_clip_has_raw_buffer(v4)) )
      {
        rf_animation_clip_add_instance_reference(*(_DWORD *)(*((_DWORD *)this + 1876) + 4 * a2 + 3932));
        return v7;
      }
      else
      {
        return -1;
      }
    }
    else
    {
      return -1;
    }
  }
  else
  {
    for ( j = 0; j < *((_DWORD *)this + 1204); ++j )
      ;
    return -1;
  }
}

