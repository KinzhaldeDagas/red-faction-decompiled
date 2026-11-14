// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00521210 rf_pointer_array_count_matches
// UNREALRED VERIFIED [decal-face-links-20261028]: Scans dynamic dword pointer array (count+0,backing+8,stride4), counts ALL exact matches of supplied value and returns count. Does not stop at first or alter contents; no pointee comparison.
// UNREALRED VERIFIED [combat-native-followup-20261104]: Array exact-pointer membership helper returns the COUNT of matching entries, not a visibility predicate or first index.52D560 calls with affectedRoom+108 and detail-room pointer; nonzero skips duplicate dynamic append. Existing serialized duplicate entries therefore remain observable.
int __thiscall rf_pointer_array_count_matches(_DWORD *this, int a2)
{
  int i; // [esp+4h] [ebp-8h]
  int v4; // [esp+8h] [ebp-4h]

  v4 = 0;
  for ( i = 0; i < *this; ++i )
  {
    if ( *(_DWORD *)(*(this + 2) + 4 * i) == a2 )
      ++v4;
  }
  return v4;
}

