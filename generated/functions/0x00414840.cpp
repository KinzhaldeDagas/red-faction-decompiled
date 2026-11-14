// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00414840 rf_glass_drop_callback_once_per_category_mask
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): Cdecl SIX stackslots(positionVector,unusedDWORD1..4,categoryDWORDpointer),plainRET. Corrects saved sixth argument from BYTEpointer to DWORDpointer: native reads FULL DWORD[category] at4148E9,then adds16 and SHL1 byCL (countmaskedmod32),so highbits do not affect mask but4 readable bytes are required. Hex-Rays can still optimize the expression to a byte load despite the saved DWORD-pointer prototype;native instruction extent is authoritative. Lazy global6807DC bit1 constructs RFString6807D4="Glass Drop" and registers exit destructor;bit2 caches sound-set lookup in6807D0,including lookup failure. Guard bits set before initialization;native unwind clears corresponding bit if
// constructor/lookup throws. Then checks shared mask666B7C. If categorybit alreadyset,returns that mask/incidentalEAX without sound;otherwise ORsbit BEFORE random-foley choice and positional play(position,volume1,shared17F10B0 vector,flags0). Does not test/play result or clear throttle after failure. No own per-frame reset,category range,position/categoryNULL or sound-set validity guard;normalreturn combines mask or voice/resultEAX,not boolean.
int __cdecl rf_glass_drop_callback_once_per_category_mask(
        float *position,
        int unused1,
        int unused2,
        int unused3,
        int unused4,
        const _DWORD *category)
{
  char *v6; // eax
  int result; // eax
  int v8; // eax

  if ( (dword_6807DC & 1) == 0 )
  {
    dword_6807DC |= 1u;
    rf_string_construct_from_cstr(dword_6807D4, "Glass Drop");
    atexit(rf_static_cleanup_006807d4);
  }
  if ( (dword_6807DC & 2) == 0 )
  {
    dword_6807DC |= 2u;
    v6 = (char *)rf_string_object_c_str_or_empty(dword_6807D4);
    dword_6807D0 = rf_foley_definition_find_name(v6);
  }
  result = 1 << (*(_BYTE *)category + 16);
  if ( (result & unk_666B7C) == 0 )
  {
    unk_666B7C |= result;
    v8 = rf_foley_choose_random_sound(dword_6807D0);
    return rf_gamesound_play_positional_event(v8, position, 1.0, (int)&unk_17F10B0, 0);
  }
  return result;
}

