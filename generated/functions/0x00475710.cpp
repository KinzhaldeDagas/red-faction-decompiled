// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475710 rf_ambient_sounds_destroy_all
// UNREALRED VERIFIED [ambient-audio]: Walks the persistent ambient intrusive list safely and destroys every 0x3C-byte record.
void __cdecl rf_ambient_sounds_destroy_all()
{
  _DWORD *i; // [esp+0h] [ebp-8h]
  _DWORD *v1; // [esp+4h] [ebp-4h]

  for ( i = (_DWORD *)rf_ambient_sound_list_head; i != &rf_ambient_sound_list_head; i = v1 )
  {
    v1 = (_DWORD *)*i;
    rf_ambient_sound_destroy((int)i);
  }
}

