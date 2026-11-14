// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040B6D0 sub_40B6D0
// UNREALRED VERIFIED [combat-reaction-20261111]: Literal selected-weapon predicate: primary AI+4!=-1 OR secondary AI+8!=-1 immediately returns1, without ammo, ownership, dead, or model tests. Otherwise40D380 gates a first-association435170 entity-resolution/recursive40B6D0 attempt; the entire gate/first-child/resolve/recursive attempt is repeated a second time. Preserve call ordering and short circuits; missing host association providers are not native false.
char __cdecl sub_40B6D0(int *a1)
{
  int v2; // [esp+0h] [ebp-10h]
  int v3; // [esp+4h] [ebp-Ch]
  int v4; // [esp+8h] [ebp-8h]
  int v5; // [esp+Ch] [ebp-4h]

  if ( a1[1] != -1 || a1[2] != -1 )
    return 1;
  if ( sub_40D380(*a1) )
  {
    v4 = sub_435170(*a1);
    v5 = rf_entity_resolve_handle(v4);
    if ( v5 )
    {
      if ( sub_40B6D0((_DWORD *)(v5 + 672)) == 1 )
        return 1;
    }
  }
  if ( sub_40D380(*a1) )
  {
    v2 = sub_435170(*a1);
    v3 = rf_entity_resolve_handle(v2);
    if ( v3 )
    {
      if ( sub_40B6D0((_DWORD *)(v3 + 672)) == 1 )
        return 1;
    }
  }
  return 0;
}

