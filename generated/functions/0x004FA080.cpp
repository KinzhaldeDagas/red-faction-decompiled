// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA080 rf_event_create_explode_record
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Create event10 Explode. Store raw byte+0x2B8, copy named effect string+0x2BC, resolve it with0x507610 into dword+0x2C4, and store supplied floats+0x2CC/+0x2C8 in observed argument order. No effect-id validation or explosion/GeoMod admission at creation.
int __cdecl rf_event_create_explode_record(float *a1, char a2, float a3, float a4, char *String2)
{
  int v6; // [esp+0h] [ebp-4h]

  v6 = rf_mission_event_create_at_position(a1, 0xAu);
  if ( v6 )
  {
    *(float *)(v6 + 716) = a3;
    *(_BYTE *)(v6 + 696) = a2;
    rf_string_assign_from_cstr((_DWORD *)(v6 + 700), String2);
    *(_DWORD *)(v6 + 708) = sub_507610(String2);
    *(float *)(v6 + 712) = a4;
  }
  return v6;
}

