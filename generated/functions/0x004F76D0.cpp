// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F76D0 rf_mission_event_find_by_uid
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Layout clarification: common-object resolver returns embedded object C; require common runtime type[C+0x24]==6, then return enclosing event E=C-4. Hence event common-object pointer is E+4, stable saved identifier is E+0x24(common+0x20), runtime identifier is E+0x30(common+0x2C), and runtime type is E+0x28. Event serializers match stable saved id at E+0x24; do not mislabel it runtime type.
// UNREALRED VERIFIED [combat-native-pickup-source-20261111] Despite historical find_by_uid naming, argument is a full runtime generation-bearing handle:40CE70 rejects-1/low16>=1024/mismatched full common+0x2C handle. Require common type+0x24==6 and return enclosingEvent=common-4. Do not replace with stable-UID lookup or suppress pending-delete objects.4485C0 performs successful authored UID→runtime conversion separately.
int __cdecl rf_mission_event_find_by_uid(int a1)
{
  int v3; // [esp+4h] [ebp-4h]

  v3 = rf_object_resolve_handle(a1);
  if ( !v3 )
    return 0;
  if ( *(_DWORD *)(v3 + 36) != 6 )
    return 0;
  if ( v3 )
    return v3 - 4;
  else
    return 0;
}

