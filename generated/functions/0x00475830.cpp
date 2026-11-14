// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475830 rf_ambient_sound_create
// UNREALRED VERIFIED [world-uid-ownership]: Resolves the authored sound, allocates and links a 0x3C-byte ambient-sound record, stores UID at +0x08, position at +0x14, and the authored runtime scalar at +0x2C.
// UNREALRED VERIFIED [ambient-audio]: Registers the sound resource, then allocates and links one 0x3C-byte persistent record: links +0/+4, UID +8, resource handle +12, frontend slot +16, position +20, filename +32, minimum distance +40, authored volume +44, rolloff +48, startup delay milliseconds +52, and timer/replicator +56.
int __cdecl rf_ambient_sound_create(int a1, char *Source, float *source, float a4, float a5, float a6, int a7)
{
  _DWORD *v8; // [esp+10h] [ebp-2Ch]
  float copy_result[3]; // [esp+14h] [ebp-28h] BYREF
  void *v10; // [esp+20h] [ebp-1Ch]
  _DWORD *v11; // [esp+24h] [ebp-18h]
  int v12; // [esp+28h] [ebp-14h]
  float *v13; // [esp+2Ch] [ebp-10h]
  int v14; // [esp+38h] [ebp-4h]

  v12 = rf_ambient_sound_resource_register((int)Source, a4, a5, a6);
  if ( v12 < 0 )
    return -1;
  v10 = operator new(0x3Cu);
  v14 = 0;
  if ( v10 )
    v8 = rf_ambient_sound_record_construct(v10);
  else
    v8 = nullptr;
  v11 = v8;
  v14 = -1;
  v13 = (float *)v8;
  v8[2] = a1;
  *((_DWORD *)v13 + 3) = v12;
  rf_vector_copy(v13 + 5, copy_result, source);
  v13[4] = NAN;
  rf_string_assign_from_cstr((_DWORD *)v13 + 8, Source);
  v13[10] = a4;
  v13[11] = a5;
  v13[12] = a6;
  *((_DWORD *)v13 + 13) = a7;
  rf_replicator_reset((_DWORD *)v13 + 14);
  *((_DWORD *)v13 + 1) = rf_ambient_sound_list_tail;
  *(_DWORD *)v13 = &rf_ambient_sound_list_head;
  *rf_ambient_sound_list_tail = v13;
  rf_ambient_sound_list_tail = v13;
  ++rf_ambient_sound_record_count;
  return *((_DWORD *)v13 + 2);
}

