// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004150A0 rf_clutter_render_model_with_shield_view_gate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): Cdecl clutter pointer. Model128NULL returnsobjectbits without rendering. Riot-shield class664==global666B64 is suppressed ONLY when ownerUID48 resolves entity,that entity5168 equals globalplayer-pointer87C640,and DWORD8 of its viewwrapper(globalplayer196) is0. Any failed match permits rendering;no own globalplayer/viewwrapper NULL guard. Constructs80-byte render options (colors left uninitialized by defaults). If globalplayer BYTE4016==1,ORsoptionsflags2 andsetscolor12RGBAbytes(0,32,0,255). Nonzero objectDWORD636 overrides optionsDWORD28;zero leaves constructor default0. Always ORsoptionsflags0x100,then renders primary model128 using commonposition60/commonmatrix72. Does not use
// physics252/predictedpose,draw secondary696 or recheck classflag visibility. Return final render-helperEAX or object/suppression-path incidental value;not uniform success.
_DWORD *__cdecl rf_clutter_render_model_with_shield_view_gate(_DWORD *a1)
{
  _DWORD *result; // eax
  int v2; // [esp+0h] [ebp-54h]
  char v3[12]; // [esp+4h] [ebp-50h] BYREF
  _BYTE v4[16]; // [esp+10h] [ebp-44h] BYREF
  int v5; // [esp+20h] [ebp-34h]

  result = a1;
  if ( a1[32] )
  {
    if ( a1[166] != unk_666B64
      || (v2 = rf_entity_resolve_handle(a1[12])) == 0
      || *(_DWORD *)(v2 + 5168) != unk_87C640
      || (result = (_DWORD *)rf_view_wrapper_get_dword8(*(_DWORD *)(unk_87C640 + 196))) != nullptr )
    {
      rf_model_render_options_construct(v3);
      if ( *(_BYTE *)(unk_87C640 + 4016) == 1 )
      {
        *(_DWORD *)v3 |= 2u;
        rf_color4_set_bytes_return_destination(v4, 0, 32, 0, 255);
      }
      if ( a1[159] )
        v5 = a1[159];
      *(_DWORD *)v3 |= 0x100u;
      return (_DWORD *)rf_model_handle_render_all_adapter(a1[32], (int)(a1 + 15), (int)(a1 + 18), (int)v3);
    }
  }
  return result;
}

