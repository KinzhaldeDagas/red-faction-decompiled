// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044AEF0 rf_persona_history_append
// UNREALRED VERIFIED [persona-lifecycle-20260923]: Appends persona message history before the caller checks player visibility. Only source strings shorter than 250 bytes enter this path. Selects (newest_index + 1) % 80, quotes/wraps text into an entry with stride 0x108, stores signed 16-bit persona index at +0x104 and signed 16-bit layout height at +0x106. At count 80 subtracts the overwritten height before adding the new height; updates newest index and saturates count at 80. Sole observed caller ignores return value; inherited char return declaration is not a verified success/failure contract.
char __cdecl rf_persona_history_append(const char *a1, __int16 a2)
{
  int v2; // eax
  double v3; // st7
  int total_height; // eax
  int v5; // eax
  int v6; // eax
  int v8; // [esp-4h] [ebp-28Ch]
  const char *v10; // [esp+34h] [ebp-254h]
  __int16 height_select_current; // [esp+38h] [ebp-250h]
  int v12; // [esp+3Ch] [ebp-24Ch]
  char v13[260]; // [esp+40h] [ebp-248h] BYREF
  size_t Count[6]; // [esp+144h] [ebp-144h] BYREF
  char *Source; // [esp+15Ch] [ebp-12Ch]
  int line_offsets[6]; // [esp+160h] [ebp-128h] BYREF
  int index; // [esp+178h] [ebp-110h]
  int i; // [esp+17Ch] [ebp-10Ch]
  char Destination[260]; // [esp+180h] [ebp-108h] BYREF

  v10 = a1;
  do
    LOBYTE(v2) = *v10;
  while ( *v10++ );
  if ( (unsigned int)(v10 - (a1 + 1)) < 0xFA )
  {
    index = (rf_persona_history_get_newest_index() + 1) % 80;
    Source = (char *)rf_persona_history_entry_at(index);
    sprintf(Source, "\"%s\"", a1);
    v8 = dword_663048;
    v3 = (double)(240 * rf_renderer_get_viewport_width()) / 640.0;
    v12 = rf_text_wrap_into_offset_length_arrays((int *)Count, line_offsets, Source, (int)v3, 6, 0, v8);
    strncpy(Destination, Source, 0x100u);
    Destination[255] = 0;
    v13[255] = 0;
    *Source = 0;
    for ( i = 0; i < v12; ++i )
    {
      strncpy(v13, &Destination[line_offsets[i]], Count[i]);
      v13[Count[i]] = 10;
      v13[Count[i] + 1] = 0;
      qmemcpy(&Source[strlen(Source)], v13, &v13[strlen(v13) + 1] - v13);
    }
    height_select_current = rf_font_get_height_select_current(-1);
    if ( rf_persona_history_get_count() == 80 )
    {
      total_height = rf_persona_history_get_total_height();
      rf_persona_history_set_total_height(total_height - *((__int16 *)Source + 131));
    }
    *((_WORD *)Source + 130) = a2;
    *((_WORD *)Source + 131) = height_select_current * (v12 + 1);
    v5 = rf_persona_history_get_total_height();
    rf_persona_history_set_total_height(*((__int16 *)Source + 131) + v5);
    rf_persona_history_set_newest_index(index);
    v6 = rf_persona_history_get_count();
    rf_persona_history_set_count(v6 + 1);
    v2 = rf_persona_history_get_count();
    if ( v2 > 80 )
      LOBYTE(v2) = rf_persona_history_set_count(80);
  }
  return v2;
}

