// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052A9D0 rf_renderer_set_category_light_allow_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl lowBYTE argument. Store raw byte toglobal663B10,return sameAL unchanged (notnormalizedbool). Zero forces active-list builders includeCategory parameter0; any nonzero permits caller choice. Does not enable masterlighting or include category automatically, invalidate active/candidate lists, incrementserial or change record category.
char __cdecl rf_renderer_set_category_light_allow_byte(char a1)
{
  byte_663B10 = a1;
  return a1;
}

